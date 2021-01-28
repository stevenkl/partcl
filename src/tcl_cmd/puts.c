#ifndef TCL_DISABLE_PUTS
#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"



static int tcl_cmd_puts(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  tcl_value_t *text = tcl_list_at(args, 1);
  puts(tcl_string(text));
  putchar('\n');
  return tcl_result(tcl, FNORMAL, text);
}
#endif