
//
// last.c
//
// Copyright (c) 2014 Stephen Mathieson
// MIT licensed
//

#include <stdio.h>
#include <string.h>
#include <sophia/sp.h>
#include "last.h"

char *
sphia_last(void *db) {
  if (NULL == db) return NULL;

  char *key = NULL;
  void *cursor = sp_cursor(db, SPLTE, NULL, 0);
  if (NULL == cursor) return NULL;

  if (sp_fetch(cursor)) {
    key = (char *) sp_key(cursor);
    size_t l = sp_keysize(cursor);
    if ('\0' != key[l]) key[l] = '\0';
  }

  sp_destroy(cursor);

  return key
    ? strdup(key)
    : NULL;
}
