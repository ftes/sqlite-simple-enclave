#include "vdbe_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

/* sgx_ocfree() just restores the original outside stack pointer. */
#define OCALLOC(val, type, len) do {	\
	void* __tmp = sgx_ocalloc(len);	\
	if (__tmp == NULL) {	\
		sgx_ocfree();	\
		return SGX_ERROR_UNEXPECTED;\
	}			\
	(val) = (type)__tmp;	\
} while (0)



typedef struct ms_sqlite3_log_ocall_t {
	int ms_errCode;
	char* ms_formattedString;
} ms_sqlite3_log_ocall_t;

typedef struct ms_sqlite3SystemError_ocall_t {
	sqlite3* ms_db;
	int ms_rc;
} ms_sqlite3SystemError_ocall_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_dummy_root_ecall(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	dummy_root_ecall();
	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[1];
} g_ecall_table = {
	1,
	{
		{(void*)(uintptr_t)sgx_dummy_root_ecall, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[2][1];
} g_dyn_entry_table = {
	2,
	{
		{0, },
		{0, },
	}
};


sgx_status_t SGX_CDECL sqlite3_log_ocall(int errCode, char* formattedString)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_formattedString = formattedString ? strlen(formattedString) + 1 : 0;

	ms_sqlite3_log_ocall_t* ms;
	OCALLOC(ms, ms_sqlite3_log_ocall_t*, sizeof(*ms));

	ms->ms_errCode = errCode;
	if (formattedString != NULL && sgx_is_within_enclave(formattedString, _len_formattedString)) {
		OCALLOC(ms->ms_formattedString, char*, _len_formattedString);
		memcpy(ms->ms_formattedString, formattedString, _len_formattedString);
	} else if (formattedString == NULL) {
		ms->ms_formattedString = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3SystemError_ocall(sqlite3* db, int rc)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sqlite3SystemError_ocall_t* ms;
	OCALLOC(ms, ms_sqlite3SystemError_ocall_t*, sizeof(*ms));

	ms->ms_db = SGX_CAST(sqlite3*, db);
	ms->ms_rc = rc;
	status = sgx_ocall(1, ms);


	sgx_ocfree();
	return status;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
