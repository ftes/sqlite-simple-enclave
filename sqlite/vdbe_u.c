#include "vdbe_u.h"


typedef struct ms_sqlite3_log_ocall_t {
	int ms_errCode;
	char* ms_formattedString;
} ms_sqlite3_log_ocall_t;

typedef struct ms_sqlite3SystemError_ocall_t {
	sqlite3* ms_db;
	int ms_rc;
} ms_sqlite3SystemError_ocall_t;

static sgx_status_t SGX_CDECL vdbe_sqlite3_log_ocall(void* pms)
{
	ms_sqlite3_log_ocall_t* ms = SGX_CAST(ms_sqlite3_log_ocall_t*, pms);
	sqlite3_log_ocall(ms->ms_errCode, ms->ms_formattedString);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vdbe_sqlite3SystemError_ocall(void* pms)
{
	ms_sqlite3SystemError_ocall_t* ms = SGX_CAST(ms_sqlite3SystemError_ocall_t*, pms);
	sqlite3SystemError_ocall(ms->ms_db, ms->ms_rc);
	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * func_addr[2];
} ocall_table_vdbe = {
	2,
	{
		(void*)(uintptr_t)vdbe_sqlite3_log_ocall,
		(void*)(uintptr_t)vdbe_sqlite3SystemError_ocall,
	}
};

sgx_status_t dummy_root_ecall(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 0, &ocall_table_vdbe, NULL);
	return status;
}

