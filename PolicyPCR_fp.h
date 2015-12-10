// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// THIS CODE IS GENERATED - DO NOT MODIFY!

#ifndef TPM2_POLICYPCR_FP_H
#define TPM2_POLICYPCR_FP_H

#include "tpm_generated.h"

typedef struct {
  TPMI_SH_POLICY policySession;
  TPM2B_DIGEST pcrDigest;
  TPML_PCR_SELECTION pcrs;
} PolicyPCR_In;

// Executes PolicyPCR with request handles and parameters from |in|.
TPM_RC TPM2_PolicyPCR(PolicyPCR_In* in);

// Initializes handle fields in |target| from |req_handles|. Unmarshals
// parameter fields in |target| from |buffer|.
TPM_RC PolicyPCR_In_Unmarshal(PolicyPCR_In* target,
                              TPM_HANDLE req_handles[],
                              BYTE** buffer,
                              INT32* size);

// Unmarshals any request parameters starting at |req_parameter_buffer|.
// Executes command. Marshals any response handles and parameters to the
// global response buffer and computes |*res_handle_buffer_size| and
// |*res_parameter_buffer_size|. If |tag| == TPM_ST_SESSIONS, marshals
// parameter_size indicating the size of the parameter area. parameter_size
// field is located between the handle area and parameter area.
TPM_RC Exec_PolicyPCR(TPMI_ST_COMMAND_TAG tag,
                      BYTE** req_parameter_buffer,
                      INT32* req_parameter_buffer_size,
                      TPM_HANDLE req_handles[],
                      UINT32* res_handle_buffer_size,
                      UINT32* res_parameter_buffer_size);

#endif  // TPM2_POLICYPCR_FP_H
