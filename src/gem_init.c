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

static mrb_debug_context *_debug_context = NULL;

static mrb_debug_context*
mrr_mrb_debug_context_new(mrb_state *mrb)
{
  mrb_debug_context *dbg = (mrb_debug_context*)mrb_malloc(mrb, sizeof(mrb_debug_context));

  memset(dbg, 0, sizeof(mrb_debug_context));

  dbg->xm = DBG_INIT;
  dbg->xphase = DBG_PHASE_BEFORE_RUN;
  dbg->next_bpno = 1;

  return dbg;
}

mrb_debug_context*
mrr_mrb_debug_context_get(mrb_state *mrb)
{
  if (!_debug_context) {
    _debug_context = mrr_mrb_debug_context_new(mrb);
  }
  return _debug_context;
}

void
mrr_mrb_debug_context_set(mrb_debug_context *dbg)
{
  _debug_context = dbg;
}

void
mrr_mrb_debug_context_free(mrb_state *mrb)
{
  if (_debug_context) {
    mrb_debug_delete_break_all(mrb, _debug_context);
    mrb_free(mrb, _debug_context);
    _debug_context = NULL;
  }
}

static void
mrr_rr_hook(mrb_state *mrb, mrb_irep *irep, const mrb_code *pc, mrb_value *regs, mrb_debug_context * dbg )
{
	NULL;
}

static void
mrr_code_fetch_hook(mrb_state *mrb, mrb_irep *irep, const mrb_code *pc, mrb_value *regs) 
{
  const char *file;
  int32_t line;
  mrb_debug_context *dbg = mrr_mrb_debug_context_get(mrb);

  mrb_assert(dbg);
  dbg->irep = irep;
  dbg->pc   = pc;
  dbg->regs = regs;
  file = mrb_debug_get_filename(mrb, irep, pc - irep->iseq);
  line = mrb_debug_get_line(mrb, irep, pc - irep->iseq);
  if (file == NULL || line < 0) return;
  mrr_rr_hook(mrb, irep, pc, regs, dbg);
  dbg->prvfile = file;
  dbg->prvline = line;
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

