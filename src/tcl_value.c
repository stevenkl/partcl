/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
#include <stdlib.h>
#include "tcl_config.h"
#include "tcl_parser.h"
#include "tcl_value.h"



const char *tcl_string(tcl_value_t *v) { return v; }
int tcl_int(tcl_value_t *v) { return atoi(v); }
int tcl_length(tcl_value_t *v) { return v == NULL ? 0 : strlen(v); }

void tcl_free(tcl_value_t *v) { free(v); }

tcl_value_t *tcl_append_string(tcl_value_t *v, const char *s, size_t len) {
  size_t n = tcl_length(v);
  v = realloc(v, n + len + 1);
  memset((char *)tcl_string(v) + n, 0, len + 1);
  strncpy((char *)tcl_string(v) + n, s, len);
  return v;
}

tcl_value_t *tcl_append(tcl_value_t *v, tcl_value_t *tail) {
  v = tcl_append_string(v, tcl_string(tail), tcl_length(tail));
  tcl_free(tail);
  return v;
}

tcl_value_t *tcl_alloc(const char *s, size_t len) {
  return tcl_append_string(NULL, s, len);
}

tcl_value_t *tcl_dup(tcl_value_t *v) {
  return tcl_alloc(tcl_string(v), tcl_length(v));
}

tcl_value_t *tcl_list_alloc() { return tcl_alloc("", 0); }

int tcl_list_length(tcl_value_t *v) {
  int count = 0;
  tcl_each(tcl_string(v), tcl_length(v) + 1, 0) {
    if (p.token == TWORD) {
      count++;
    }
  }
  return count;
}

void tcl_list_free(tcl_value_t *v) { free(v); }


tcl_value_t *tcl_list_at(tcl_value_t *v, int index) {
  int i = 0;
  tcl_each(tcl_string(v), tcl_length(v) + 1, 0) {
    if (p.token == TWORD) {
      if (i == index) {
        if (p.from[0] == '{') {
          return tcl_alloc(p.from + 1, p.to - p.from - 2);
        }
        return tcl_alloc(p.from, p.to - p.from);
      }
      i++;
    }
  }
  return NULL;
}

tcl_value_t *tcl_list_append(tcl_value_t *v, tcl_value_t *tail) {
  if (tcl_length(v) > 0) {
    v = tcl_append(v, tcl_alloc(" ", 2));
  }
  if (tcl_length(tail) > 0) {
    int q = 0;
    const char *p;
    for (p = tcl_string(tail); *p; p++) {
      if (tcl_is_space(*p) || tcl_is_special(*p, 0)) {
        q = 1;
        break;
      }
    }
    if (q) {
      v = tcl_append(v, tcl_alloc("{", 1));
    }
    v = tcl_append(v, tcl_dup(tail));
    if (q) {
      v = tcl_append(v, tcl_alloc("}", 1));
    }
  } else {
    v = tcl_append(v, tcl_alloc("{}", 2));
  }
  return v;
}