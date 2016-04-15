#ifndef VDBE_U_H__
#define VDBE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */

#include "sqliteInt.h"

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3_log_ocall, (int errCode, char* formattedString));
void SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3SystemError_ocall, (sqlite3* db, int rc));

sgx_status_t dummy_root_ecall(sgx_enclave_id_t eid);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
