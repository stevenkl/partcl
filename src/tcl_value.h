#pragma once
#ifndef TCL_VALUE_H
#define TCL_VALUE_H

#include "tcl_config.h"
#include "tcl_types.h"



const char *tcl_string(tcl_value_t *v);
int tcl_int(tcl_value_t *v);
int tcl_length(tcl_value_t *v);
void tcl_free(tcl_value_t *v);
tcl_value_t *tcl_append_string(tcl_value_t *v, const char *s, size_t len);
tcl_value_t *tcl_append(tcl_value_t *v, tcl_value_t *tail);
tcl_value_t *tcl_alloc(const char *s, size_t len);
tcl_value_t *tcl_dup(tcl_value_t *v);
tcl_value_t *tcl_list_alloc();
int tcl_list_length(tcl_value_t *v);
void tcl_list_free(tcl_value_t *v);
tcl_value_t *tcl_list_at(tcl_value_t *v, int index);
tcl_value_t *tcl_list_append(tcl_value_t *v, tcl_value_t *tail);


#endif