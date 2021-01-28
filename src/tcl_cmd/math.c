#include "tcl_config.h"
#include "tcl_interp.h"
#include "tcl_value.h"


#ifndef TCL_DISABLE_MATH
static int tcl_cmd_math(tcl_interp_t *tcl, tcl_value_t *args, void *arg) {
  (void)arg;
  char buf[64];
  tcl_value_t *opval = tcl_list_at(args, 0);
  tcl_value_t *aval = tcl_list_at(args, 1);
  tcl_value_t *bval = tcl_list_at(args, 2);
  const char *op = tcl_string(opval);
  int a = tcl_int(aval);
  int b = tcl_int(bval);
  int c = 0;
  if (op[0] == '+') {
    c = a + b;
  } else if (op[0] == '-') {
    c = a - b;
  } else if (op[0] == '*') {
    c = a * b;
  } else if (op[0] == '/') {
    c = a / b;
  } else if (op[0] == '>' && op[1] == '\0') {
    c = a > b;
  } else if (op[0] == '>' && op[1] == '=') {
    c = a >= b;
  } else if (op[0] == '<' && op[1] == '\0') {
    c = a < b;
  } else if (op[0] == '<' && op[1] == '=') {
    c = a <= b;
  } else if (op[0] == '=' && op[1] == '=') {
    c = a == b;
  } else if (op[0] == '!' && op[1] == '=') {
    c = a != b;
  }

  char *p = buf + sizeof(buf) - 1;
  char neg = (c < 0);
  *p-- = 0;
  if (neg) {
    c = -c;
  }
  do {
    *p-- = '0' + (c % 10);
    c = c / 10;
  } while (c > 0);
  if (neg) {
    *p-- = '-';
  }
  p++;

  tcl_free(opval);
  tcl_free(aval);
  tcl_free(bval);
  return tcl_result(tcl, FNORMAL, tcl_alloc(p, strlen(p)));
}
#endif