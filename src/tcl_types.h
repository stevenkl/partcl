#pragma once
#ifndef TCL_TYPES_H
#define TCL_TYPES_H


typedef char   tcl_value_t;

typedef int (*tcl_cmd_fn_t)(void *, void *, void *);


typedef struct tcl_var_t {
  tcl_value_t *name;
  tcl_value_t *value;
  struct tcl_var_t *next;
} tcl_var_t;


typedef struct tcl_env_t {
  tcl_var_t *vars;
  struct tcl_env_t *parent;
} tcl_env_t;


typedef struct tcl_cmd_t {
  tcl_value_t *name;
  int arity;
  tcl_cmd_fn_t fn;
  void *arg;
  struct tcl_cmd_t *next;
} tcl_cmd_t;


typedef struct tcl_interp_t {
  tcl_env_t *env;
  tcl_cmd_t *cmds;
  tcl_value_t *result;
} tcl_interp_t;





typedef struct tcl_parser_t {
  const char *from;
  const char *to;
  const char *start;
  const char *end;
  int q;
  int token;
} tcl_parser_t;




#endif