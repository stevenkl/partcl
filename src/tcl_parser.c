#include <stdlib.h>
#include "tcl_config.h"
#include "tcl_parser.h"





/* Token type and control flow constants */
// enum { TCMD, TWORD, TPART, TERROR };
// enum { FERROR, FNORMAL, FRETURN, FBREAK, FAGAIN };





static int tcl_is_special(char c, int q) {
  return (c == '$' || (!q && (c == '{' || c == '}' || c == ';' || c == '\r' ||
                              c == '\n')) ||
          c == '[' || c == ']' || c == '"' || c == '\0');
}


static int tcl_is_space(char c) { return (c == ' ' || c == '\t'); }


static int tcl_is_end(char c) {
  return (c == '\n' || c == '\r' || c == ';' || c == '\0');
}


int tcl_next(const char *s, size_t n, const char **from, const char **to, int *q) {
  unsigned int i = 0;
  int depth = 0;
  char open;
  char close;

  DBG("tcl_next(%.*s)+%d+%d|%d\n", n, s, *from - s, *to - s, *q);

  /* Skip leading spaces if not quoted */
  for (; !*q && n > 0 && tcl_is_space(*s); s++, n--) {
  }
  *from = s;
  /* Terminate command if not quoted */
  if (!*q && n > 0 && tcl_is_end(*s)) {
    *to = s + 1;
    return TCMD;
  }
  if (*s == '$') { /* Variable token, must not start with a space or quote */
    if (tcl_is_space(s[1]) || s[1] == '"') {
      return TERROR;
    }
    int mode = *q;
    *q = 0;
    int r = tcl_next(s + 1, n - 1, to, to, q);
    *q = mode;
    return ((r == TWORD && *q) ? TPART : r);
  }

  if (*s == '[' || (!*q && *s == '{')) {
    /* Interleaving pairs are not welcome, but it simplifies the code */
    open = *s;
    close = (open == '[' ? ']' : '}');
    for (i = 0, depth = 1; i < n && depth != 0; i++) {
      if (i > 0 && s[i] == open) {
        depth++;
      } else if (s[i] == close) {
        depth--;
      }
    }
  } else if (*s == '"') {
    *q = !*q;
    *from = *to = s + 1;
    if (*q) {
      return TPART;
    }
    if (n < 2 || (!tcl_is_space(s[1]) && !tcl_is_end(s[1]))) {
      return TERROR;
    }
    *from = *to = s + 1;
    return TWORD;
  } else {
    while (i < n && (*q || !tcl_is_space(s[i])) && !tcl_is_special(s[i], *q)) {
      i++;
    }
  }
  *to = s + i;
  if (i == n) {
    return TERROR;
  }
  if (*q) {
    return TPART;
  }
  return (tcl_is_space(s[i]) || tcl_is_end(s[i])) ? TWORD : TPART;
}

