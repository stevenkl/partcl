#pragma once
#ifndef TCL_VAR_H
#define TCL_VAR_H

#include "tcl_config.h"
#include "tcl_types.h"


tcl_value_t *tcl_var(tcl_interp_t *tcl, tcl_value_t *name, tcl_value_t *v);

#endif