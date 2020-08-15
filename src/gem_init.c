#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <mruby.h>
#include <mruby/dump.h>
#include <mruby/debug.h>
#include <mruby/class.h>
#include <mruby/opcode.h>
#include <mruby/variable.h>

#include "mrdb.h"
#include "apibreak.h"
#include "apilist.h"
#include "apiprint.h"

static void
mrr_rr_hook(mrb_state *mrb, mrb_irep *irep, const mrb_code *pc, mrb_value *regs, const char *file, const int32_t line)
{
	NULL;
}

static void
mrr_code_fetch_hook(mrb_state *mrb, mrb_irep *irep, const mrb_code *pc, mrb_value *regs) 
{
  const char *file;
  int32_t line;
  file = mrb_debug_get_filename(mrb, irep, pc - irep->iseq);
  line = mrb_debug_get_line(mrb, irep, pc - irep->iseq);
  if (file == NULL || line < 0) return;
  mrr_rr_hook(mrb, irep, pc, regs, file, line);
}

void
mrb_mruby_rr_gem_init(mrb_state* mrb) {
  //FIXME: raise error if debug is not enabled.
  mrb->code_fetch_hook = mrr_code_fetch_hook;
}

void
mrb_mruby_rr_gem_final(mrb_state* mrb) { }

void
mrr_dummy() {
  mrb_debug_eval(NULL, NULL, NULL, 0, NULL, 0);
}
