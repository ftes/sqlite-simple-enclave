# About this project
The SQLite repository contains a complex build.

1. It first generates several C source files in `tsrc/`
2. Then an amalgation (all source files combined into one single file) is created in `sqlite3.c`

This hampers debugging and analyzing the code. Rather, the `tsrc/` contents are used in this project to provide a debugging environment.

# How this project was created
1. Build regular SQLite source
2. Copy all files from `tsrc/`
3. Remove the following (avoid unnecessary dependencies)
  a. `tclsqlite.c`
4. Add the following
  a. `ext/rtree/sqlite3rtree.h`
5. Set the following macros (`Properties->Preprocessor->PreProcessor Definitions`)
  a. `SQLITE_CORE`
  b. `SQLITE_THREADSAFE=0`
  c. `SQLITE_OMIT_LOAD_EXTENSION`
  d. `SQLITE_OMIT_SHARED_CACHE`
  e. `SQLITE_OMIT_PROGRESS_CALLBACK`
  f. possibly `SQLITE_TEMP_STORE=3` (no temp files, rather store in memory)
  g. `SQLITE_OMIT_DEPRECATED`