#pragma once
#ifndef TCL_VAR_H
#define TCL_VAR_H

#include "tcl_value.h"


typedef struct tcl_var_t tcl_var_t;
struct tcl_var_t {
  tcl_value_t *name;
  tcl_value_t *value;
  tcl_var_t *next;
};



#endif