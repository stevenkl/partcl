#pragma once
#ifndef TCL_CMD_H
#define TCL_CMD_H


#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"


typedef struct tcl_cmd_t tcl_cmd_t;



static int tcl_cmd_flow(tcl_interp_t, tcl_value_t, void);
static int tcl_cmd_if(tcl_interp_t, tcl_value_t, void*);
static int tcl_cmd_math(tcl_interp_t, tcl_value_t, void*);
static int tcl_cmd_proc(tcl_interp_t, tcl_value_t, void*);
static int tcl_cmd_puts(tcl_interp_t, tcl_value_t, void*);
static int tcl_cmd_set(tcl_interp_t, tcl_value_t, void*);
static int tcl_cmd_subst(tcl_interp_t, tcl_value_t, void*);
static int tcl_cmd_while(tcl_interp_t, tcl_value_t, void*);


#endif