#include "vdbe_u.h"


static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_vdbe = {
	0,
	{ NULL },
};

sgx_status_t dummy_root_ecall(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 0, &ocall_table_vdbe, NULL);
	return status;
}

