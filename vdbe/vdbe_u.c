#include "vdbe_u.h"


typedef struct ms_log_ocall_t {
	int ms_errCode;
	char* ms_formattedString;
} ms_log_ocall_t;

static sgx_status_t SGX_CDECL vdbe_log_ocall(void* pms)
{
	ms_log_ocall_t* ms = SGX_CAST(ms_log_ocall_t*, pms);
	log_ocall(ms->ms_errCode, ms->ms_formattedString);
	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_vdbe = {
	1,
	{
		(void*)(uintptr_t)vdbe_log_ocall,
	}
};

sgx_status_t dummy_root_ecall(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 0, &ocall_table_vdbe, NULL);
	return status;
}

