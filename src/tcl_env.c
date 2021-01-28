#include <stdlib.h>

#include "tcl_config.h"
#include "tcl_types.h"

#include "tcl_interp.h"
#include "tcl_value.h"


extern tcl_env_t *tcl_env_alloc(tcl_env_t *parent) {
  tcl_env_t *env = malloc(sizeof(env));
  env->vars = NULL;
  env->parent = parent;
  return env;
}


extern tcl_env_t *tcl_env_free(tcl_env_t *env) {
  tcl_env_t *parent = env->parent;
  while (env->vars) {
    tcl_var_t *var = env->vars;
    env->vars = env->vars->next;
    tcl_free(var->name);
    tcl_free(var->value);
    free(var);
  }
  free(env);
  return parent;
}


extern tcl_var_t *tcl_env_var(tcl_env_t *env, tcl_value_t *name) {
  tcl_var_t *var = malloc(sizeof(tcl_var_t));
  var->name = tcl_dup(name);
  var->next = env->vars;
  var->value = tcl_alloc("", 0);
  env->vars = var;
  return var;
}