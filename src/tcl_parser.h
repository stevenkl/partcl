#pragma once
#ifndef TCL_PARSER_H
#define TCL_PARSER_H

#include <stddef.h>
#include <stdlib.h>




/* A helper parser struct and macro (requires C99) */
typedef struct tcl_parser_t {
  const char *from;
  const char *to;
  const char *start;
  const char *end;
  int q;
  int token;
}tcl_parser_t;


int tcl_next(const char *s, size_t n, const char **from, const char **to, int *q);

#endif