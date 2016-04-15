#include "vdbe_u.h"
#include "sqliteInt.h"

void log_ocall(int errCode, char* formattedString) {
  if( sqlite3GlobalConfig.xLog ){
    sqlite3GlobalConfig.xLog(sqlite3GlobalConfig.pLogArg, errCode,
                           formattedString);
  }
}