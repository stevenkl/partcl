#pragma once
#ifndef TCL_INTERP_H
#define TCL_INTERP_H

#include <stdlib.h>
#include "tcl_config.h"
#include "tcl_cmd.h"
#include "tcl_env.h"
#include "tcl_value.h"


typedef struct tcl_interp_t tcl_interp_t;



typedef int (*tcl_cmd_fn_t)(tcl_interp_t *, tcl_value_t *, void *);



int tcl_eval(tcl_interp_t *tcl, const char *s, size_t len);
void tcl_init(tcl_interp_t *tcl);
void tcl_destroy(tcl_interp_t *tcl);
int tcl_result(tcl_interp_t *tcl, flow_t flow, tcl_value_t *result);
int tcl_subst(tcl_interp_t *tcl, const char *s, size_t len);
void tcl_register(tcl_interp_t *tcl, const char *name, tcl_cmd_fn_t fn, int arity, void *arg);


#endif