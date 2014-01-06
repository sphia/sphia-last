//
// sphia-macro.h
// copyright (c) 2013 joseph werle <joseph.werle@gmail.com>
//

#ifndef SPHIA_MACRO_H
#define SPHIA_MACRO_H 1

#define SPHIA_MACRO_VERSION "0.0.1"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sophia/sophia.h>

#define SPHIA_FERROR(e)                                   \
  fprintf(stderr, "%s\n", e);

#define SPHIA_CATCH(err, o)                               \
  else if (1 && (err = sp_error(o)))

#define SPHIA_ENV(env, path, mode)                        \
  void *env = sp_env();                                   \
  if (NULL != env &&                                      \
      0 == sp_ctl(env, SPDIR, mode, path))                \

#define SPHIA_DB_OPEN(env, db, path, mode)                \
  void *env = sp_env();                                   \
  void *db = NULL;                                        \
  if (NULL != env &&                                      \
      0 == sp_ctl(env, SPDIR, mode, path) &&              \
      (db = sp_open(env)))

#define SPHIA_DESTROY(o)                                  \
  if (0 == sp_destroy(o))

#define SPHIA_DB_FOREACH(_k, _v, _db)                      \
  char *_k = NULL, *_v = NULL;                             \
  void *_c = sp_cursor(_db, SPGT, NULL, 0);                \
  int _s = 0, _rc = 0;                                     \
  if (NULL == _c) { _s = 1; (_rc = sp_destroy(_c)); }      \
  while ((0 == _s && sp_fetch(_c) &&                       \
        (_k = (char *) sp_key(_c)) &&                      \
        (_v = (char *) sp_value(_c)))                      \
        || (_rc = sp_destroy(_c)))

#endif
