#!/usr/bin/python2

# Copyright 2014 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""A code generator for TPM 2.0 commands.

The command generator takes as input a commands file as emitted by the
extract_commands.sh script. It outputs valid C code to marshal command input and
output structures, and also generates functions ParseHandleBuffer and
CommandDispatcher defined by the TCG TPM2.0 Library Specification.

The input grammar is documented in the extract_commands script.
Sample input for commands looks like this:
_BEGIN
_INPUT_START TPM2_Startup
_TYPE TPMI_ST_COMMAND_TAG
_NAME tag
_COMMENT TPM_ST_NO_SESSIONS
_TYPE UINT32
_NAME commandSize
_TYPE TPM_CC
_NAME commandCode
_COMMENT TPM_CC_Startup {NV}
_TYPE TPM_SU
_NAME startupType
_COMMENT TPM_SU_CLEAR or TPM_SU_STATE
_OUTPUT_START TPM2_Startup
_TYPE TPM_ST
_NAME tag
_COMMENT see clause 8
_TYPE UINT32
_NAME responseSize
_TYPE TPM_RC
_NAME responseCode
_END
"""

from __future__ import print_function

import re
from subprocess import call


_COPYRIGHT_HEADER = (
    '// Copyright 2015 The Chromium OS Authors. All rights reserved.\n'
    '// Use of this source code is governed by a BSD-style license that can '
    'be\n'
    '// found in the LICENSE file.\n'
    '\n'
    '// THIS CODE IS GENERATED - DO NOT MODIFY!\n')
_HEADER_FILE_GUARD_HEADER = """
#ifndef TPM2_%(name)s_FP_H_
#define TPM2_%(name)s_FP_H_
"""
_HEADER_FILE_GUARD_FOOTER = """
#endif  // TPM2_%(name)s_FP_H
"""
_HEADER_FILE_INCLUDES = """
#include "tpm_generated.h"
"""
_IMPLEMENTATION_FILE_INCLUDES = """
#include "MemoryLib_fp.h"
#include "%(command_name)s_fp.h"
"""
_COMMAND_DISPATCHER_INCLUDES = '#include "%(command_name)s_fp.h"\n'
_COMMAND_DISPATCHER_START = """
#include "Implementation.h"
#include "CommandDispatcher_fp.h"

TPM_RC CommandDispatcher(
    TPMI_ST_COMMAND_TAG tag,
    TPM_CC command_code,
    INT32 *request_parameter_buffer_size,
    BYTE *request_parameter_buffer_start,
    TPM_HANDLE request_handles[],
    UINT32 *response_handle_buffer_size,
    UINT32 *response_parameter_buffer_size) {
  BYTE *request_parameter_buffer = request_parameter_buffer_start;
  switch(command_code) {"""
_COMMAND_DISPATCHER_CASE = """
#ifdef %(command_code)s
    case %(command_code)s:
      return Exec_%(command_name)s(tag, &request_parameter_buffer,
          request_parameter_buffer_size, request_handles,
          response_handle_buffer_size, response_parameter_buffer_size);
#endif"""
_COMMAND_DISPATCHER_END = """
    default:
      return TPM_RC_COMMAND_CODE;
  }
}"""
_HANDLE_PROCESS_START = """
#include "tpm_generated.h"
#include "HandleProcess_fp.h"
#include "Implementation.h"
#include "TPM_Types.h"

TPM_RC ParseHandleBuffer(
    TPM_CC command_code,
    BYTE **request_handle_buffer_start,
    INT32 *request_buffer_remaining_size,
    TPM_HANDLE request_handles[],
    UINT32 *num_request_handles) {
  TPM_RC result = TPM_RC_SUCCESS;
  *num_request_handles = 0;
  switch(command_code) {
"""
_HANDLE_PROCESS_CASE_START = """
#ifdef %(command_code)s
    case %(command_code)s:"""
_HANDLE_PROCESS_CASE_UNMARSHAL = """
      result = %(handle_type)s_Unmarshal(
          (%(handle_type)s*)&request_handles[*num_request_handles],
          request_handle_buffer_start,
          request_buffer_remaining_size);"""
_HANDLE_PROCESS_CASE_UNMARSHAL_FLAG = """
      result = %(handle_type)s_Unmarshal(
          (%(handle_type)s*)&request_handles[*num_request_handles],
          request_handle_buffer_start,
          request_buffer_remaining_size,
          %(flag_val)s);"""
_HANDLE_PROCESS_CASE_CHECK = """
      if (result != TPM_RC_SUCCESS) {
        return result;
      }
      ++(*num_request_handles);"""
_HANDLE_PROCESS_CASE_END = """
      return TPM_RC_SUCCESS;
#endif"""
_HANDLE_PROCESS_END = """
    default:
      return TPM_RC_COMMAND_CODE;
  }
}"""
_GET_COMMAND_CODE_STRING_HEADER = """
#ifndef TPM2_GET_COMMAND_CODE_STRING_FP_H_
#define TPM2_GET_COMMAND_CODE_STRING_FP_H_

#include "TPM_Types.h"

const char* GetCommandCodeString(TPM_CC command_code);

#endif  // TPM2_GET_COMMAND_CODE_STRING_FP_H_"""
_GET_COMMAND_CODE_STRING_START = """
#include "GetCommandCodeString_fp.h"

const char* GetCommandCodeString(TPM_CC command_code) {
  switch(command_code) {"""
_GET_COMMAND_CODE_STRING_CASE = """
#ifdef TPM_CC_%(command_name)s
  case TPM_CC_%(command_name)s:
      return "%(command_name)s";
#endif"""
_GET_COMMAND_CODE_STRING_END = """
    default:
      return "Unknown command";
  }
}"""
class Command(object):
  """Represents a TPM command.

  Attributes:
    name: The command name (e.g. 'TPM2_Startup').
    command_code: The name of the command code constant (e.g. TPM2_CC_Startup).
    request_args: A list to hold command input arguments. Each element is a dict
        and has these keys:
            'type': The argument type.
            'name': The argument name.
            'command_code': The optional value of the command code constant.
            'description': Optional descriptive text for the argument.
            'has_conditional': String literal 'TRUE' or 'FALSE' indicating
                whether 'type' is allowed to have a conditional value.
    response_args: A list identical in form to request_args but to hold command
        output arguments.
  """

  _HANDLE_RE = re.compile(r'TPMI_.H_.*')
  _STRUCT_DECL_START = """
typedef struct {"""
  _STRUCT_DECL_FIELD = """
  %(type)s %(name)s;"""
  _STRUCT_DECL_END = """
} %(command_name)s_%(direction)s;
"""
  _FUNCTION_DECL_IN_OUT = """
// Executes %(command_name)s with request handles and parameters from
// |in| and computes response handles and parameters to |out|.
TPM_RC TPM2_%(command_name)s(
    %(command_name)s_In *in,
    %(command_name)s_Out *out);

// Initializes handle fields in |target| from |request_handles|. Unmarshals
// parameter fields in |target| from |buffer|.
TPM_RC %(command_name)s_In_Unmarshal(
    %(command_name)s_In *target,
    TPM_HANDLE request_handles[],
    BYTE **buffer,
    INT32 *size);

// Marshals response handles and parameters from |source| to |buffer|. Computes
// and marshals the size of the parameter area (parameter_size) if |tag| ==
// TPM_ST_SESSIONS. Returns size of (parameter area + handle area) in bytes.
// Return value does not include parameter_size field.
UINT16 %(command_name)s_Out_Marshal(
    %(command_name)s_Out *source,
    TPMI_ST_COMMAND_TAG tag,
    BYTE **buffer,
    INT32 *size);
"""
  _FUNCTION_DECL_IN = """
// Executes %(command_name)s with request handles and parameters from |in|.
TPM_RC TPM2_%(command_name)s(
    %(command_name)s_In *in);

// Initializes handle fields in |target| from |request_handles|. Unmarshals
// parameter fields in |target| from |buffer|.
TPM_RC %(command_name)s_In_Unmarshal(
    %(command_name)s_In *target,
    TPM_HANDLE request_handles[],
    BYTE **buffer,
    INT32 *size);
"""
  _FUNCTION_DECL_OUT = """
// Executes %(command_name)s and computes response handles and parameters
// to |out|.
TPM_RC TPM2_%(command_name)s(
    %(command_name)s_Out *out);

// Marshals response handles and parameters from |source| to |buffer|. Computes
// and marshals the size of the parameter area (parameter_size) if |tag| ==
// TPM_ST_SESSIONS. Returns size of (parameter area + handle area) in bytes.
// Does not include parameter_size field.
UINT16 %(command_name)s_Out_Marshal(
    %(command_name)s_Out *source,
    TPMI_ST_COMMAND_TAG tag,
    BYTE **buffer,
    INT32 *size);
"""
  _EXEC_DECL = """
// Unmarshals any request parameters starting at |request_parameter_buffer|.
// Executes command. Marshals any response handles and parameters to the
// global response buffer and computes |*response_handle_buffer_size| and
// |*response_parameter_buffer_size|. If |tag| == TPM_ST_SESSIONS, marshals
// parameter_size indicating the size of the parameter area. parameter_size
// field is located between the handle area and parameter area.
TPM_RC Exec_%(command_name)s(
    TPMI_ST_COMMAND_TAG tag,
    BYTE **request_parameter_buffer,
    INT32 *request_parameter_buffer_size,
    TPM_HANDLE request_handles[],
    UINT32 *response_handle_buffer_size,
    UINT32 *response_parameter_buffer_size);
"""
  _EXEC_COMMAND_IMPL_START = """
TPM_RC Exec_%(command_name)s(
    TPMI_ST_COMMAND_TAG tag,
    BYTE **request_parameter_buffer,
    INT32 *request_parameter_buffer_size,
    TPM_HANDLE request_handles[],
    UINT32 *response_handle_buffer_size,
    UINT32 *response_parameter_buffer_size) {
  TPM_RC result = TPM_RC_SUCCESS;"""
  _EXEC_COMMAND_IMPL_IN_OUT = """
  %(command_name)s_In in;
  %(command_name)s_Out out;
#ifdef %(command_code)s
  BYTE *response_buffer;
  INT32 response_buffer_size;
  UINT16 bytes_marshalled;
  UINT16 num_response_handles = %(num_response_handles)s;
#endif
  *response_handle_buffer_size = 0;
  *response_parameter_buffer_size = 0;
  // Unmarshal request parameters to input structure.
  result = %(command_name)s_In_Unmarshal(&in, request_handles,
      request_parameter_buffer, request_parameter_buffer_size);
  if (result != TPM_RC_SUCCESS) {
    return result;
  }
  // Execute command.
  result = TPM2_%(command_name)s(&in, &out);
  if (result != TPM_RC_SUCCESS) {
    return result;
  }
  // Marshal output structure to global response buffer.
#ifdef %(command_code)s
  response_buffer = MemoryGetResponseBuffer(%(command_code)s) + 10;
  response_buffer_size = MAX_RESPONSE_SIZE - 10;
  bytes_marshalled = %(command_name)s_Out_Marshal(
      &out, tag, &response_buffer, &response_buffer_size);
  *response_handle_buffer_size = num_response_handles*sizeof(TPM_HANDLE);
  *response_parameter_buffer_size =
      bytes_marshalled - *response_handle_buffer_size;
  return TPM_RC_SUCCESS;
#endif
  return TPM_RC_COMMAND_CODE;
}
"""
  _EXEC_COMMAND_IMPL_IN = """
  %(command_name)s_In in;
#ifdef %(command_code)s
  BYTE *response_buffer;
  INT32 response_buffer_size;
#endif
  *response_handle_buffer_size = 0;
  *response_parameter_buffer_size = 0;
  // Unmarshal request parameters to input structure.
  result = %(command_name)s_In_Unmarshal(&in, request_handles,
      request_parameter_buffer, request_parameter_buffer_size);
  if (result != TPM_RC_SUCCESS) {
    return result;
  }
  // Execute command.
  result = TPM2_%(command_name)s(&in);
  if (result != TPM_RC_SUCCESS) {
    return result;
  }
#ifdef %(command_code)s
  response_buffer = MemoryGetResponseBuffer(%(command_code)s) + 10;
  response_buffer_size = MAX_RESPONSE_SIZE - 10;
  // Add parameter_size field, always equal to 0 here.
  if (tag == TPM_ST_SESSIONS) {
    UINT32_Marshal(response_parameter_buffer_size, &response_buffer,
        &response_buffer_size);
  }
  return TPM_RC_SUCCESS;
#endif
  return TPM_RC_COMMAND_CODE;
}
"""
  _EXEC_COMMAND_IMPL_OUT = """
  %(command_name)s_Out out;
#ifdef %(command_code)s
  BYTE *response_buffer;
  INT32 response_buffer_size;
  UINT16 bytes_marshalled;
  UINT16 num_response_handles = %(num_response_handles)s;
#endif
  *response_handle_buffer_size = 0;
  *response_parameter_buffer_size = 0;
  // Execute command.
  result = TPM2_%(command_name)s(&out);
  if (result != TPM_RC_SUCCESS) {
    return result;
  }
  // Marshal output structure containing response handles and parameters to
  // response buffer.
#ifdef %(command_code)s
  response_buffer = MemoryGetResponseBuffer(%(command_code)s) + 10;
  response_buffer_size = MAX_RESPONSE_SIZE - 10;
  bytes_marshalled = %(command_name)s_Out_Marshal(
      &out, tag, &response_buffer, &response_buffer_size);
  *response_handle_buffer_size = num_response_handles*sizeof(TPM_HANDLE);
  *response_parameter_buffer_size =
      bytes_marshalled - *response_handle_buffer_size;
  return TPM_RC_SUCCESS;
#endif
  return TPM_RC_COMMAND_CODE;
}
"""
  _UNMARSHAL_COMMAND_START = """
TPM_RC %(command_name)s_In_Unmarshal(
    %(command_name)s_In *target,
    TPM_HANDLE request_handles[],
    BYTE **buffer,
    INT32 *size) {
  TPM_RC result = TPM_RC_SUCCESS;"""
  _MARSHAL_COMMAND_START = """
UINT16 %(command_name)s_Out_Marshal(
    %(command_name)s_Out *source,
    TPMI_ST_COMMAND_TAG tag,
    BYTE **buffer,
    INT32 *size) {
  UINT16 total_size = 0;
  UINT32 parameter_size = 0;
  BYTE *parameter_size_location;
  INT32 parameter_size_size = sizeof(UINT32);
  UINT32 num_response_handles = %(num_response_handles)s;"""
  _UNMARSHAL_END = """
  return result;
}
"""
  _MARSHAL_END = """
  // Compute actual parameter_size. Don't add result to total_size.
  if (tag == TPM_ST_SESSIONS) {
    parameter_size = total_size - num_response_handles*sizeof(TPM_HANDLE);
    UINT32_Marshal(
        &parameter_size, &parameter_size_location, &parameter_size_size);
  }
  return total_size;
}
"""
  _SET_COMMAND_HANDLE = """
  target->%(field_name)s = request_handles[%(num)s];"""
  _PARAMETERSIZE_CHECK = """
  // Add parameter_size=0 to indicate size of the parameter area. Will be
  // replaced later by computed parameter_size.
  if (tag == TPM_ST_SESSIONS) {
    parameter_size_location = *buffer;
    // Don't add to total_size, but increment *buffer and decrement *size.
    UINT32_Marshal(&parameter_size, buffer, size);
  }"""

  def __init__(self, name):
    """Initializes a Command instance.

    Initially the request_args and response_args attributes are not set.

    Args:
      name: The command name (e.g. 'TPM2_Startup').
    """
    self.name = name
    self.command_code = ''
    self.request_args = None
    self.response_args = None

  def OutputMarshalFunction(self, out_file, typemap):
    """Generates a marshal function for the command output structure.

    Args:
      out_file: File to be written to opened by the caller.
      typemap: A dict mapping type names to the corresponding object.
          Generated by structure_generator.
    """
    if len(self.response_args) == 0:
      return
    # Categorize arguments as either handles or parameters.
    handles, parameters = self._SplitArgs(self.response_args)
    out_file.write(self._MARSHAL_COMMAND_START % {
        'command_name': self.MethodName(),
        'num_response_handles': self.GetNumberOfResponseHandles()})
    if len(handles):
      out_file.write('\n  // Marshal response handles.')
    for handle in handles:
      typemap[handle['type']].OutputMarshalCall(
          out_file, handle['type'], handle['name'], handle['has_conditional'])
    out_file.write(self._PARAMETERSIZE_CHECK)
    if len(parameters):
      out_file.write('\n  // Marshal response parameters.')
    for parameter in parameters:
      typemap[parameter['type']].OutputMarshalCall(
          out_file,
          parameter['type'],
          parameter['name'],
          parameter['has_conditional'])
    out_file.write(self._MARSHAL_END)

  def OutputUnmarshalFunction(self, out_file, typemap):
    """Generates a unmarshal function for the command input structure.

    Args:
      out_file: File to be written to opened by the caller.
      typemap: A dict mapping type names to the corresponding object.
          Generated by structure_generator.
    """
    if len(self.request_args) == 0:
      return
    # Categorize arguments as either handles or parameters.
    handles, parameters = self._SplitArgs(self.request_args)
    out_file.write(self._UNMARSHAL_COMMAND_START % {
        'command_name': self.MethodName()})
    if len(handles) > 0:
      out_file.write('\n  // Get request handles from request_handles array.')
    for index, handle in enumerate(handles):
      out_file.write(self._SET_COMMAND_HANDLE % {'field_name': handle['name'],
                                                 'num': index})
    if len(parameters) > 0:
      out_file.write('\n  // Unmarshal request parameters.')
    for parameter in parameters:
      typemap[parameter['type']].OutputUnmarshalCall(
          out_file,
          parameter['type'],
          parameter['name'],
          parameter['has_conditional'])
    out_file.write(self._UNMARSHAL_END)

  def OutputExecFunction(self, out_file):
    """Generates an exec function for the command.

    Args:
      out_file: File to be written to opened by the caller.
      typemap: A dict mapping type names to the corresponding object.
          Generated by structure_generator.
    """
    out_file.write(
        self._EXEC_COMMAND_IMPL_START % {'command_name': self.MethodName()})
    if len(self.request_args) and len(self.response_args):
      out_file.write(self._EXEC_COMMAND_IMPL_IN_OUT % {
          'command_name': self.MethodName(),
          'command_code': self.command_code,
          'num_response_handles': self.GetNumberOfResponseHandles()})
    elif len(self.request_args):
      out_file.write(self._EXEC_COMMAND_IMPL_IN % {
          'command_name': self.MethodName(),
          'command_code': self.command_code})
    elif len(self.response_args):
      out_file.write(self._EXEC_COMMAND_IMPL_OUT % {
          'command_name': self.MethodName(),
          'command_code': self.command_code,
          'num_response_handles': self.GetNumberOfResponseHandles()})

  def OutputDecl(self, out_file):
    if len(self.request_args) > 0:
      out_file.write(self._STRUCT_DECL_START)
      for arg in self.request_args:
        out_file.write(self._STRUCT_DECL_FIELD % {'type': arg['type'],
                                                  'name': arg['name']})
      out_file.write(self._STRUCT_DECL_END % {'command_name': self.MethodName(),
                                              'direction': 'In'})
    if len(self.response_args) > 0:
      out_file.write(self._STRUCT_DECL_START)
      for arg in self.response_args:
        out_file.write(self._STRUCT_DECL_FIELD % {'type': arg['type'],
                                                  'name': arg['name']})
      out_file.write(self._STRUCT_DECL_END % {'command_name': self.MethodName(),
                                              'direction': 'Out'})
    if len(self.response_args) and len(self.request_args):
      out_file.write(
          self._FUNCTION_DECL_IN_OUT % {'command_name': self.MethodName()})
    elif len(self.response_args):
      out_file.write(
          self._FUNCTION_DECL_OUT % {'command_name': self.MethodName()})
    elif len(self.request_args):
      out_file.write(
          self._FUNCTION_DECL_IN % {'command_name': self.MethodName()})
    out_file.write(self._EXEC_DECL % {'command_name': self.MethodName()})

  def GetNumberOfRequestHandles(self):
    """Returns the number of input handles for this command."""
    return len(self._SplitArgs(self.request_args)[0])

  def GetNumberOfResponseHandles(self):
    """Returns the number of output handles for this command."""
    return len(self._SplitArgs(self.response_args)[0])

  def MethodName(self):
    """Creates an appropriate generated method name for the command.

    We use the command name without the TPM2_ prefix.

    Returns:
      The method name.
    """
    if not self.name.startswith('TPM2_'):
      return self.name
    return self.name[5:]

  def GetRequestHandles(self):
    """Returns a list of input handles for this command."""
    return self._SplitArgs(self.request_args)[0]

  def _SplitArgs(self, args):
    """Splits a list of args into handles and parameters."""
    handles = []
    parameters = []
    always_handle = set(['TPM_HANDLE'])
    # Handle types that appear as command parameters.
    always_parameter = set(['TPMI_RH_ENABLES', 'TPMI_DH_PERSISTENT'])
    if self.command_code == 'TPM_CC_FlushContext':
      always_parameter.add('TPMI_DH_CONTEXT')
    for arg in args:
      if (arg['type'] in always_handle or
          (self._HANDLE_RE.search(arg['type']) and
           arg['type'] not in always_parameter)):
        handles.append(arg)
      else:
        parameters.append(arg)
    return handles, parameters

class CommandParser(object):
  """Command definition parser.

  The input text file is extracted from the PDF file containing the TPM
  command specification from the Trusted Computing Group. The syntax
  of the text file is defined by extract_commands.sh.
  """

  # Regular expressions to pull relevant bits from annotated lines.
  _INPUT_START_RE = re.compile(r'^_INPUT_START\s+(\w+)$')
  _OUTPUT_START_RE = re.compile(r'^_OUTPUT_START\s+(\w+)$')
  _TYPE_RE = re.compile(r'^_TYPE\s+(\w+)$')
  _TYPE_PLUS_RE = re.compile(r'^_TYPE\s+(\w+)\+$')
  _NAME_RE = re.compile(r'^_NAME\s+(\w+)$')
  # Pull the command code from a comment like: _COMMENT TPM_CC_Startup {NV}.
  _COMMENT_CC_RE = re.compile(r'^_COMMENT\s+(TPM_CC_\w+).*$')
  _COMMENT_RE = re.compile(r'^_COMMENT\s+(.*)')
  # Args which are handled internally by the generated method.
  _INTERNAL_ARGS = ('tag', 'Tag', 'commandSize', 'commandCode', 'responseSize',
                    'responseCode')

  def __init__(self, in_file):
    """Initializes a CommandParser instance.

    Args:
      in_file: A file as returned by open() which has been opened for reading.
    """
    self._line = None
    self._in_file = in_file

  def _NextLine(self):
    """Gets the next input line.

    Returns:
      The next input line if another line is available, None otherwise.
    """
    try:
      self._line = self._in_file.next()
    except StopIteration:
      self._line = None

  def Parse(self):
    """Parses everything in a commands file.

    Returns:
      A list of extracted Command objects.
    """
    commands = []
    self._NextLine()
    if self._line != '_BEGIN\n':
      print('Invalid format for first line: %s\n' % self._line)
      return commands
    self._NextLine()

    while self._line != '_END\n':
      cmd = self._ParseCommand()
      if not cmd:
        break
      commands.append(cmd)
    return sorted(commands, cmp=lambda x, y: cmp(x.name, y.name))

  def _ParseCommand(self):
    """Parses inputs and outputs for a single TPM command.

    Returns:
      A single Command object.
    """
    match = self._INPUT_START_RE.search(self._line)
    if not match:
      print('Cannot match command input from line: %s\n' % self._line)
      return None
    name = match.group(1)
    cmd = Command(name)
    self._NextLine()
    cmd.request_args = self._ParseCommandArgs(cmd)
    match = self._OUTPUT_START_RE.search(self._line)
    if not match or match.group(1) != name:
      print('Cannot match command output from line: %s\n' % self._line)
      return None
    self._NextLine()
    cmd.response_args = self._ParseCommandArgs(cmd)
    request_var_names = set([arg['name'] for arg in cmd.request_args])
    for arg in cmd.response_args:
      if arg['name'] in request_var_names:
        arg['name'] += '_out'
    if not cmd.command_code:
      print('Command code not found for %s' % name)
      return None
    return cmd

  def _ParseCommandArgs(self, cmd):
    """Parses a set of arguments for a command.

    The arguments may be input or output arguments.

    Args:
      cmd: The current Command object. The command_code attribute will be set if
          such a constant is parsed.

    Returns:
      A list of arguments in the same form as the Command.request_args and
      Command.response_args attributes.
    """
    args = []
    type_match = self._TYPE_RE.search(self._line)
    type_plus_match = self._TYPE_PLUS_RE.search(self._line)
    while type_match or type_plus_match:
      arg_type = ''
      if type_match:
        arg_type = type_match.group(1)
      elif type_plus_match:
        arg_type = type_plus_match.group(1)
      self._NextLine()
      match = self._NAME_RE.search(self._line)
      if not match:
        print('Cannot match argument name from line: %s\n' % self._line)
        break
      arg_name = match.group(1)
      self._NextLine()
      match = self._COMMENT_CC_RE.search(self._line)
      if match:
        cmd.command_code = match.group(1)
      match = self._COMMENT_RE.search(self._line)
      if match:
        self._NextLine()
      if arg_name not in self._INTERNAL_ARGS and type_match:
        args.append({'type': arg_type,
                     'name': arg_name,
                     'has_conditional': "FALSE"})
      elif arg_name not in self._INTERNAL_ARGS and type_plus_match:
        args.append({'type': arg_type,
                     'name': arg_name,
                     'has_conditional': "TRUE"})
      type_match = self._TYPE_RE.search(self._line)
      type_plus_match = self._TYPE_PLUS_RE.search(self._line)
    return args

def OutputCommandDispatcher(commands):
  """Generates implementation file for CommandDispatcher function.

  Args:
    commands: A list of Command objects.
  """
  with open('CommandDispatcher.c', 'w') as out_file:
    out_file.write(_COPYRIGHT_HEADER)
    for command in commands:
      out_file.write(_COMMAND_DISPATCHER_INCLUDES %
                     {'command_name': command.MethodName()})
    out_file.write(_COMMAND_DISPATCHER_START)
    for command in commands:
      command_code = "TPM_CC_" + command.MethodName()
      out_file.write(_COMMAND_DISPATCHER_CASE %
                     {'command_code': command_code,
                      'command_name': command.MethodName()})
    out_file.write(_COMMAND_DISPATCHER_END)
  call(['clang-format', '-i', '-style=Chromium', 'CommandDispatcher.c'])

def OutputHandleProcess(commands, typemap):
  """Generates implementation file for ParseHandleBuffer function.

  Args:
    commands: A list of Command objects.
    typemap: A dict mapping type names to the corresponding object.
        Generated by structure_generator.
  """
  with open('HandleProcess.c', 'w') as out_file:
    out_file.write(_COPYRIGHT_HEADER)
    out_file.write(_HANDLE_PROCESS_START)
    for command in commands:
      command_code = "TPM_CC_" + command.MethodName()
      out_file.write(_HANDLE_PROCESS_CASE_START %
                     {'command_code': command_code})
      for handle in command.GetRequestHandles():
        if typemap[handle['type']].HasConditional():
          out_file.write(_HANDLE_PROCESS_CASE_UNMARSHAL_FLAG %
                         {'handle_type': handle['type'],
                          'flag_val': handle['has_conditional']})
        else:
          out_file.write(_HANDLE_PROCESS_CASE_UNMARSHAL %
                         {'handle_type': handle['type']})
        out_file.write(_HANDLE_PROCESS_CASE_CHECK)
      out_file.write(_HANDLE_PROCESS_CASE_END)
    out_file.write(_HANDLE_PROCESS_END)
  call(['clang-format', '-i', '-style=Chromium', 'HandleProcess.c'])

def OutputGetCommandCodeString(commands):
  """Generates header and implementation files for GetCommandCodeString.

  Args:
    commands: A list of Command objects.
  """
  with open('GetCommandCodeString_fp.h', 'w') as out_file:
    out_file.write(_COPYRIGHT_HEADER)
    out_file.write(_GET_COMMAND_CODE_STRING_HEADER)
  call(['clang-format', '-i', '-style=Chromium', 'GetCommandCodeString_fp.h'])
  with open('GetCommandCodeString.c', 'w') as out_file:
    out_file.write(_COPYRIGHT_HEADER)
    out_file.write(_GET_COMMAND_CODE_STRING_START)
    for command in commands:
      out_file.write(_GET_COMMAND_CODE_STRING_CASE %
                     {'command_name': command.MethodName()})
    out_file.write(_GET_COMMAND_CODE_STRING_END)
  call(['clang-format', '-i', '-style=Chromium', 'GetCommandCodeString.c'])

def GenerateHeader(commands):
  """Generates a header file with declarations for all given generator objects.

  Args:
    commands: A list of Command objects.
  """
  for command in commands:
    command_header_file = command.MethodName()+'_fp.h'
    with open(command_header_file, 'w') as out_file:
      out_file.write(_COPYRIGHT_HEADER)
      out_file.write(
          _HEADER_FILE_GUARD_HEADER % {'name': command.MethodName().upper()})
      out_file.write(_HEADER_FILE_INCLUDES)
      command.OutputDecl(out_file)
      out_file.write(
          _HEADER_FILE_GUARD_FOOTER % {'name': command.MethodName().upper()})
    call(['clang-format', '-i', '-style=Chromium', command_header_file])

def GenerateImplementation(commands, typemap):
  """Generates implementation code for each command.

  Args:
    commands: A list of Command objects.
    typemap: A dict mapping type names to the corresponding object.
        Generated by structure_generator.
  """
  for command in commands:
    marshal_command_file = 'Marshal_'+command.MethodName()+'.c'
    with open(marshal_command_file, 'w') as out_file:
      out_file.write(_COPYRIGHT_HEADER)
      out_file.write(_IMPLEMENTATION_FILE_INCLUDES %
                     {'command_name': command.MethodName()})
      command.OutputMarshalFunction(out_file, typemap)
      command.OutputUnmarshalFunction(out_file, typemap)
      command.OutputExecFunction(out_file)
    call(['clang-format', '-i', '-style=Chromium', marshal_command_file])
  OutputHandleProcess(commands, typemap)
  OutputCommandDispatcher(commands)
  OutputGetCommandCodeString(commands)
