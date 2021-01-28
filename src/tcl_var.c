#include <string.h>
#include <stdlib.h>

#include "tcl_config.h"
#include "tcl_types.h"

#include "tcl_env.h"
#include "tcl_value.h"



tcl_value_t *tcl_var(tcl_interp_t *tcl, tcl_value_t *name, tcl_value_t *v) {
  tcl_var_t *var;
  for (var = tcl->env->vars; var != NULL; var = var->next) {
    if (strcmp(var->name, tcl_string(name)) == 0) {
      break;
    }
  }
  if (var == NULL) {
    var = tcl_env_var(tcl->env, name);
  }
  if (v != NULL) {
    tcl_free(var->value);
    var->value = tcl_dup(v);
    tcl_free(v);
  }
  return var->value;
}

