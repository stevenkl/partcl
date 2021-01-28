#pragma once
#ifndef TCL_CONFIG_H
#define TCL_CONFIG_H

#include "tcl_parser.h"



#define MAX_VAR_LENGTH 256


#define CHUNK_SIZE 1024


typedef enum token_t {
  TCMD,
  TWORD,
  TPART,
  TERROR
} token_t;

typedef enum flow_t {
  FERROR,
  FNORMAL,
  FRETURN,
  FBREAK,
  FAGAIN
} flow_t;



#ifndef tcl_each
#define tcl_each(s, len, skiperr)                                              \
  for (struct tcl_parser_t p = {NULL, NULL, (s), (s) + (len), 0, TERROR};        \
       p.start < p.end &&                                                      \
       (((p.token = tcl_next(p.start, p.end - p.start, &p.from, &p.to,         \
                             &p.q)) != TERROR) ||                              \
        (skiperr));                                                            \
       p.start = p.to)
#endif



#endif