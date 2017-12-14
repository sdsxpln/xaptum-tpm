/******************************************************************************
 *
 * Copyright 2017 Xaptum, Inc.
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License
 *
 *****************************************************************************/

#ifndef XAPTUM_TPM_TSS2_SYS_H
#define XAPTUM_TPM_TSS2_SYS_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <tss2/tss2_tpm2_types.h>
#include <tss2/tss2_common.h>
#include <tss2/tss2_tcti.h>

#include <stdint.h>
#include <stddef.h>

typedef struct _TSS2_SYS_OPAQUE_CONTEXT_BLOB TSS2_SYS_CONTEXT;

typedef struct {
    uint8_t cmdAuthsCount;
    TPMS_AUTH_COMMAND **cmdAuths;
} TSS2_SYS_CMD_AUTHS;

typedef struct {
    uint8_t rspAuthsCount;
    TPMS_AUTH_RESPONSE **rspAuths;
} TSS2_SYS_RSP_AUTHS;

//
// Command context allocation functions
//

size_t
Tss2_Sys_GetContextSize(size_t maxCommandResponseSize);

TSS2_RC
Tss2_Sys_Initialize(TSS2_SYS_CONTEXT *sysContext,
                    size_t contextSize,
                    TSS2_TCTI_CONTEXT *tctiContext,
                    TSS2_ABI_VERSION *abiVersion);

TSS2_RC
Tss2_Sys_Finalize(TSS2_SYS_CONTEXT *sysContext);

TSS2_RC
Tss2_Sys_GetTctiContext(TSS2_SYS_CONTEXT *sysContext,
                        TSS2_TCTI_CONTEXT **tctiContext);

//
// Part 3 Functions
//

TSS2_RC
Tss2_Sys_CreatePrimary(TSS2_SYS_CONTEXT *sysContext,
                       TPMI_RH_HIERARCHY primaryHandle,
                       TSS2_SYS_CMD_AUTHS const *cmdAuthsArray,
                       TPM2B_SENSITIVE_CREATE *inSensitive,
                       TPM2B_PUBLIC *inPublic,
                       TPM2B_DATA *outsideInfo,
                       TPML_PCR_SELECTION *creationPCR,
                       TPM_HANDLE *objectHandle,
                       TPM2B_PUBLIC *outPublic,
                       TPM2B_CREATION_DATA *creationData,
                       TPM2B_DIGEST *creationHash,
                       TPMT_TK_CREATION *creationTicket,
                       TPM2B_NAME *name,
                       TSS2_SYS_RSP_AUTHS *rspAuthsArray);

TSS2_RC
Tss2_Sys_Commit(TSS2_SYS_CONTEXT *sysContext,
                TPMI_DH_OBJECT signHandle,
                TSS2_SYS_CMD_AUTHS const *cmdAuthsArray,
                TPM2B_ECC_POINT *P1,
                TPM2B_SENSITIVE_DATA *s2,
                TPM2B_ECC_PARAMETER *y2,
                TPM2B_ECC_POINT *K,
                TPM2B_ECC_POINT *L,
                TPM2B_ECC_POINT *E,
                uint16_t *counter,
                TSS2_SYS_RSP_AUTHS *rspAuthsArray);

TSS2_RC
Tss2_Sys_Sign(TSS2_SYS_CONTEXT *sysContext,
              TPMI_DH_OBJECT keyHandle,
              TSS2_SYS_CMD_AUTHS const *cmdAuthsArray,
              TPM2B_DIGEST *digest,
              TPMT_SIG_SCHEME *inScheme,
              TPMT_TK_HASHCHECK *validation,
              TPMT_SIGNATURE *signature,
              TSS2_SYS_RSP_AUTHS *rspAuthsArray);

#ifdef __cplusplus
}
#endif

#endif
