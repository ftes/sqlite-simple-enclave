#include "vdbe_u.h"
#include "sqliteInt.h"

void sqlite3_log_ocall(int errCode, char* formattedString) {
  if( sqlite3GlobalConfig.xLog ){
    sqlite3GlobalConfig.xLog(sqlite3GlobalConfig.pLogArg, errCode,
                           formattedString);
  }
}

void sqlite3SystemError_ocall(sqlite3 *db, int rc) {
  sqlite3SystemError(db, rc);
}