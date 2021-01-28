#pragma once
#ifndef TCL_INTERP_H
#define TCL_INTERP_H

#include "tcl_config.h"
#include "tcl_types.h"




int tcl_eval(tcl_interp_t *tcl, const char *s, size_t len);
void tcl_init(tcl_interp_t *tcl);
void tcl_destroy(tcl_interp_t *tcl);
int tcl_result(tcl_interp_t *tcl, flow_t flow, tcl_value_t *result);
int tcl_subst(tcl_interp_t *tcl, const char *s, size_t len);
void tcl_register(tcl_interp_t *tcl, const char *name, tcl_cmd_fn_t fn, int arity, void *arg);


#endif