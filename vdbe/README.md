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


# Linked files (visual studio)
- `global.c`


# Copy individual functions
- `sqlite3_initialize()` from `main.c` and additional `#include "mutex.h"`
	- initializes memory -> has to be done again in VDBE enclave
- most of `malloc.c`


# Project config
- additional include directory: `../sqlite`
- set preprocessor macros as stated in `../sqlite/README.md`


# Design changes
- function pointers cannot be passed, rather the function name of user defined functions is specified