#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"



static int tcl_cmd_subst(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  tcl_value_t *s = tcl_list_at(args, 1);
  int r = tcl_subst(tcl, tcl_string(s), tcl_length(s));
  tcl_free(s);
  return r;
}
