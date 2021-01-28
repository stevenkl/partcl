#pragma once
#ifndef TCL_ENV_H
#define TCL_ENV_H

#include "tcl_config.h"
#include "tcl_types.h"


extern tcl_env_t *tcl_env_alloc(tcl_env_t *parent);
extern tcl_env_t *tcl_env_free(tcl_env_t *env);
extern tcl_var_t *tcl_env_var(tcl_env_t *env, tcl_value_t *name);


#endif