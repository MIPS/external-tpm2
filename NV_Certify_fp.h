// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// THIS CODE IS GENERATED - DO NOT MODIFY!

#ifndef TPM2_NV_CERTIFY_FP_H
#define TPM2_NV_CERTIFY_FP_H

#include "tpm_generated.h"

typedef struct {
  TPMI_DH_OBJECT signHandle;
  TPMI_RH_NV_AUTH authHandle;
  TPMI_RH_NV_INDEX nvIndex;
  TPM2B_DATA qualifyingData;
  TPMT_SIG_SCHEME inScheme;
  UINT16 size;
  UINT16 offset;
} NV_Certify_In;

typedef struct {
  TPM2B_ATTEST certifyInfo;
  TPMT_SIGNATURE signature;
} NV_Certify_Out;

// Executes NV_Certify with request handles and parameters from
// |in| and computes response handles and parameters to |out|.
TPM_RC TPM2_NV_Certify(NV_Certify_In* in, NV_Certify_Out* out);

// Initializes handle fields in |target| from |req_handles|. Unmarshals
// parameter fields in |target| from |buffer|.
TPM_RC NV_Certify_In_Unmarshal(NV_Certify_In* target,
                               TPM_HANDLE req_handles[],
                               BYTE** buffer,
                               INT32* size);

// Marshals response handles and parameters from |source| to |buffer|. Computes
// and marshals the size of the parameter area (parameter_size) if |tag| ==
// TPM_ST_SESSIONS. Returns size of (parameter area + handle area) in bytes.
// Does not include parameter_size field.
UINT16 NV_Certify_Out_Marshal(NV_Certify_Out* source,
                              TPMI_ST_COMMAND_TAG tag,
                              BYTE** buffer,
                              INT32* size);

// Unmarshals any request parameters starting at |req_parameter_buffer|.
// Executes command. Marshals any response handles and parameters to the
// global response buffer and computes |*res_handle_buffer_size| and
// |*res_parameter_buffer_size|. If |tag| == TPM_ST_SESSIONS, marshals
// parameter_size indicating the size of the parameter area. parameter_size
// field is located between the handle area and parameter area.
TPM_RC Exec_NV_Certify(TPMI_ST_COMMAND_TAG tag,
                       BYTE** req_parameter_buffer,
                       INT32* req_parameter_buffer_size,
                       TPM_HANDLE req_handles[],
                       UINT32* res_handle_buffer_size,
                       UINT32* res_parameter_buffer_size);

#endif  // TPM2_NV_CERTIFY_FP_H
