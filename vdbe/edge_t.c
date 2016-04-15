#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vdbe_t.h"

/*
 * Use OCALL to log behaviour
 */
void sqlite3_log(int iErrCode, const char *zFormat, ...) {
  size_t size = strlen(zFormat);
  size_t needed;
  char *formatted;
  va_list args;
  va_start(args, zFormat);
  needed = vsnprintf(NULL, 0, zFormat, args);
  formatted = (char*) malloc(needed);
  vsnprintf(formatted, needed, zFormat, args);
  log_ocall(iErrCode, formatted);
  free(formatted);
  va_end(args);
}