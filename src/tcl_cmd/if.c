#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"



static int tcl_cmd_if(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  int i = 1;
  int n = tcl_list_length(args);
  int r = FNORMAL;
  while (i < n) {
    tcl_value_t *cond = tcl_list_at(args, i);
    tcl_value_t *branch = NULL;
    if (i + 1 < n) {
      branch = tcl_list_at(args, i + 1);
    }
    r = tcl_eval(tcl, tcl_string(cond), tcl_length(cond) + 1);
    tcl_free(cond);
    if (r != FNORMAL) {
      tcl_free(branch);
      break;
    }
    if (tcl_int(tcl->result)) {
      r = tcl_eval(tcl, tcl_string(branch), tcl_length(branch) + 1);
      tcl_free(branch);
      break;
    }
    i = i + 2;
    tcl_free(branch);
  }
  return r;
}