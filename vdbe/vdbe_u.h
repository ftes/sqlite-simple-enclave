#ifndef VDBE_U_H__
#define VDBE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, log_ocall, (int errCode, char* formattedString));

sgx_status_t dummy_root_ecall(sgx_enclave_id_t eid);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
