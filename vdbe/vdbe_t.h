#ifndef VDBE_T_H__
#define VDBE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void dummy_root_ecall();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif