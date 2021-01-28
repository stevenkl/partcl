#include "tcl_config.h"
#include "tcl_types.h"

#include "tcl_interp.h"
#include "tcl_var.h"
#include "tcl_value.h"


extern int tcl_cmd_set(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  tcl_value_t *var = tcl_list_at(args, 1);
  tcl_value_t *val = tcl_list_at(args, 2);
  int r = tcl_result(tcl, FNORMAL, tcl_dup(tcl_var(tcl, var, val)));
  tcl_free(var);
  return r;
}
