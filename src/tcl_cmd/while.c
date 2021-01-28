#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"



static int tcl_cmd_while(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  tcl_value_t *cond = tcl_list_at(args, 1);
  tcl_value_t *loop = tcl_list_at(args, 2);
  int r;
  for (;;) {
    r = tcl_eval(tcl, tcl_string(cond), tcl_length(cond) + 1);
    if (r != FNORMAL) {
      tcl_free(cond);
      tcl_free(loop);
      return r;
    }
    if (!tcl_int(tcl->result)) {
      tcl_free(cond);
      tcl_free(loop);
      return FNORMAL;
    }
    int r = tcl_eval(tcl, tcl_string(loop), tcl_length(loop) + 1);
    switch (r) {
    case FBREAK:
      tcl_free(cond);
      tcl_free(loop);
      return FNORMAL;
    case FRETURN:
      tcl_free(cond);
      tcl_free(loop);
      return FRETURN;
    case FAGAIN:
      continue;
    case FERROR:
      tcl_free(cond);
      tcl_free(loop);
      return FERROR;
    }
  }
}