#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"



static int tcl_cmd_flow(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  int r = FERROR;
  tcl_value_t *flowval = tcl_list_at(args, 0);
  const char *flow = tcl_string(flowval);
  if (strcmp(flow, "break") == 0) {
    r = FBREAK;
  } else if (strcmp(flow, "continue") == 0) {
    r = FAGAIN;
  } else if (strcmp(flow, "return") == 0) {
    r = tcl_result(tcl, FRETURN, tcl_list_at(args, 1));
  }
  tcl_free(flowval);
  return r;
}