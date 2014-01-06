
//
// main.c
//
// Copyright (c) 2014 Stephen Mathieson
// MIT licensed
//

#include <stdio.h>
#include <sophia/sophia.h>
#include <sophia/sp.h>
#include "commander/commander.h"
#include "sphia-macro/sphia-macro.h"
#include "last.h"

#define SPHIA_LAST_VERSION "0.0.0"

static char path[256];

static void
set_path(command_t *self) {
  strcpy(path, self->arg);
}

int
main(int argc, char *argv[]) {
  char *err = NULL;
  int rc = 0;
  command_t program;

  command_init(&program
    , "sphia-last"
    , SPHIA_LAST_VERSION);
  command_option(&program
    , "-p"
    , "--path <path>"
    , "path to database"
    , set_path);
  command_parse(&program, argc, argv);

  if (0 != program.argc % 2) {
    fprintf(stderr, "Invalid number of key/value paris\n");
    command_free(&program);
    return 1;
  }

  if (0 == strlen(path)) {
    char *default_path = getenv("SPHIA_PATH");
    if (NULL != default_path) {
      strcpy(path, default_path);
    } else {
      strcpy(path, ".");
    }
  }

  SPHIA_DB_OPEN(env, db, path, SPO_RDWR);
  SPHIA_CATCH(err, env) goto fail;

  char *last = sphia_last(db);
  if (NULL == last) goto cleanup;

  printf("%s\n", last);
  free(last);

cleanup:
  SPHIA_DESTROY(env);
  SPHIA_CATCH(err, env) goto fail;

  SPHIA_DESTROY(db);
  SPHIA_CATCH(err, db) goto fail;

  if (0 == rc) return 0;

fail:
  if (NULL == err) err = sp_error(db);
  SPHIA_FERROR(err);
  return 1;
}
