#pragma once
#ifndef TCL_PARSER_H
#define TCL_PARSER_H

#include <stddef.h>
#include <stdlib.h>
#include "tcl_config.h"
#include "tcl_types.h"


extern int tcl_is_special(char c, int q);
extern int tcl_is_space(char c);
extern int tcl_is_end(char c);
int tcl_next(const char *s, size_t n, const char **from, const char **to, int *q);

#endif