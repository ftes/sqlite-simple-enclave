# Added files (copy)
## Source files
- `vdbe.c`
- `vdbeapi.c`
- `vdbeaux.c`
- `vdbeblob.c`
- `vdbemem.c`
- `vdbesort.c`
- **not** `vdbetrace.c` (trace disabled)

## Header files
- `vdbe.h`
- `vdbeInt.h`


# Copy individual functions
- `sqlite3_initialize()` from `main.c` and additional `#include "mutex.h"`
	- initializes memory -> has to be done again in VDBE enclave
- most of `malloc.c`


# Project config
- additional include directory: `../sqlite`
- set preprocessor macros as stated in `../sqlite/README.md`