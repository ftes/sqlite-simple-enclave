#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vdbe_t.h"

/*
 * Use OCALL to log behaviour
 */
void sqlite3_log(int iErrCode, const char *zFormat, ...) {
  char *formatted;
  va_list args;
  va_start(args, zFormat);
  formatted = sqlite3_vmprintf(zFormat, args);
  va_end(args);
  sqlite3_log_ocall(iErrCode, formatted);
}