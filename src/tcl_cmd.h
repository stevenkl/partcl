#pragma once
#ifndef TCL_CMD_H
#define TCL_CMD_H


#include "tcl_config.h"
#include "tcl_types.h"



extern int tcl_cmd_flow( tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_if(   tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_math( tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_proc( tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_puts( tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_set(  tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_subst(tcl_interp_t * tcl, tcl_value_t * args, void * arg);
extern int tcl_cmd_while(tcl_interp_t * tcl, tcl_value_t * args, void * arg);


#endif