#pragma once
#ifndef TCL_ENV_H
#define TCL_ENV_H

#include "tcl_var.h"

typedef struct tcl_env_t tcl_env_t;
struct tcl_env_t {
  tcl_var_t *vars;
  tcl_env_t *parent;
};


static tcl_env_t *tcl_env_alloc(tcl_env_t *parent);
static tcl_env_t *tcl_env_free(tcl_env_t *env);
static tcl_var_t *tcl_env_var(tcl_env_t *env, tcl_value_t *name);


#endif