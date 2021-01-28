#include <stdlib.h>
#include <string.h>
#include "tcl_cmd.h"
#include "tcl_config.h"
#include "tcl_env.h"
#include "tcl_interp.h"
#include "tcl_parser.h"



struct tcl_interp_t {
  tcl_env_t *env;
  tcl_cmd_t *cmds;
  tcl_value_t *result;

};




void tcl_register(tcl_interp_t *tcl, const char *name, tcl_cmd_fn_t fn, int arity, void *arg) {
  tcl_cmd_t *cmd = malloc(sizeof(tcl_cmd_t));
  cmd->name = tcl_alloc(name, strlen(name));
  cmd->fn = fn;
  cmd->arg = arg;
  cmd->arity = arity;
  cmd->next = tcl->cmds;
  tcl->cmds = cmd;
}


void tcl_init(tcl_interp_t *tcl) {
  tcl->env = tcl_env_alloc(NULL);
  tcl->result = tcl_alloc("", 0);
  tcl->cmds = NULL;
  tcl_register(tcl, "set", tcl_cmd_set, 0, NULL);
  tcl_register(tcl, "subst", tcl_cmd_subst, 2, NULL);
#ifndef TCL_DISABLE_PUTS
  tcl_register(tcl, "puts", tcl_cmd_puts, 2, NULL);
#endif
  tcl_register(tcl, "proc", tcl_cmd_proc, 4, NULL);
  tcl_register(tcl, "if", tcl_cmd_if, 0, NULL);
  tcl_register(tcl, "while", tcl_cmd_while, 3, NULL);
  tcl_register(tcl, "return", tcl_cmd_flow, 0, NULL);
  tcl_register(tcl, "break", tcl_cmd_flow, 1, NULL);
  tcl_register(tcl, "continue", tcl_cmd_flow, 1, NULL);
#ifndef TCL_DISABLE_MATH
  char *math[] = {"+", "-", "*", "/", ">", ">=", "<", "<=", "==", "!="};
  for (unsigned int i = 0; i < (sizeof(math) / sizeof(math[0])); i++) {
    tcl_register(tcl, math[i], tcl_cmd_math, 3, NULL);
  }
#endif
}


void tcl_destroy(struct tcl_interp_t *tcl) {
  while (tcl->env) {
    tcl->env = tcl_env_free(tcl->env);
  }
  while (tcl->cmds) {
    struct tcl_cmd_t *cmd = tcl->cmds;
    tcl->cmds = tcl->cmds->next;
    tcl_free(cmd->name);
    free(cmd->arg);
    free(cmd);
  }
  tcl_free(tcl->result);
}



int tcl_result(struct tcl_interp_t *tcl, flow_t flow, tcl_value_t *result) {
  DBG("tcl_result %.*s, flow=%d\n", tcl_length(result), tcl_string(result),
      flow);
  tcl_free(tcl->result);
  tcl->result = result;
  return flow;
}


int tcl_subst(tcl_interp_t *tcl, const char *s, size_t len) {
  DBG("subst(%.*s)\n", (int)len, s);
  if (len == 0) {
    return tcl_result(tcl, FNORMAL, tcl_alloc("", 0));
  }
  switch (s[0]) {
  case '{':
    if (len <= 1) {
      return tcl_result(tcl, FERROR, tcl_alloc("", 0));
    }
    return tcl_result(tcl, FNORMAL, tcl_alloc(s + 1, len - 2));
  case '$': {
    if (len >= MAX_VAR_LENGTH) {
      return tcl_result(tcl, FERROR, tcl_alloc("", 0));
    }
    char buf[5 + MAX_VAR_LENGTH] = "set ";
    strncat(buf, s + 1, len - 1);
    return tcl_eval(tcl, buf, strlen(buf) + 1);
  }
  case '[': {
    tcl_value_t *expr = tcl_alloc(s + 1, len - 2);
    int r = tcl_eval(tcl, tcl_string(expr), tcl_length(expr) + 1);
    tcl_free(expr);
    return r;
  }
  default:
    return tcl_result(tcl, FNORMAL, tcl_alloc(s, len));
  }
}


int tcl_eval(tcl_interp_t *tcl, const char *s, size_t len) {
  DBG("eval(%.*s)->\n", (int)len, s);
  tcl_value_t *list = tcl_list_alloc();
  tcl_value_t *cur = NULL;
  tcl_each(s, len, 1) {
    DBG("tcl_next %d %.*s\n", p.token, (int)(p.to - p.from), p.from);
    switch (p.token) {
    case TERROR:
      DBG("eval: FERROR, lexer error\n");
      return tcl_result(tcl, FERROR, tcl_alloc("", 0));
    case TWORD:
      DBG("token %.*s, length=%d, cur=%p (3.1.1)\n", (int)(p.to - p.from),
          p.from, (int)(p.to - p.from), cur);
      if (cur != NULL) {
        tcl_subst(tcl, p.from, p.to - p.from);
        tcl_value_t *part = tcl_dup(tcl->result);
        cur = tcl_append(cur, part);
      } else {
        tcl_subst(tcl, p.from, p.to - p.from);
        cur = tcl_dup(tcl->result);
      }
      list = tcl_list_append(list, cur);
      tcl_free(cur);
      cur = NULL;
      break;
    case TPART:
      tcl_subst(tcl, p.from, p.to - p.from);
      tcl_value_t *part = tcl_dup(tcl->result);
      cur = tcl_append(cur, part);
      break;
    case TCMD:
      if (tcl_list_length(list) == 0) {
        tcl_result(tcl, FNORMAL, tcl_alloc("", 0));
      } else {
        tcl_value_t *cmdname = tcl_list_at(list, 0);
        struct tcl_cmd_t *cmd = NULL;
        int r = FERROR;
        for (cmd = tcl->cmds; cmd != NULL; cmd = cmd->next) {
          if (strcmp(tcl_string(cmdname), tcl_string(cmd->name)) == 0) {
            if (cmd->arity == 0 || cmd->arity == tcl_list_length(list)) {
              r = cmd->fn(tcl, list, cmd->arg);
              break;
            }
          }
        }
        tcl_free(cmdname);
        if (cmd == NULL || r != FNORMAL) {
          tcl_list_free(list);
          return r;
        }
      }
      tcl_list_free(list);
      list = tcl_list_alloc();
      break;
    }
  }
  tcl_list_free(list);
  return FNORMAL;
}