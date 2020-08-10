define mrb-info-local 
p dbgcmd_info_local(mrb,mrdb_state_get(dbg))
end

define mrb-list
p dbgcmd_list(mrb,mrdb_state_get(dbg))
end

define mrb-break
break mrr_rr_hook if $_streq(file, $arg0) == 1 && line == $arg1
end

define mrb-continue
continue
end

define mrb-reverse-continue
reverse-continue
end

define mrb-run
continue
end

define mrb-next
set $file = file
set $line = line+1
break mrr_rr_hook if $_streq(file, $file) == 1 && line == $line
continue
end

define mrb-reverse-next
set $file = file
set $line = line-1
break mrr_rr_hook if $_streq(file, $file) == 1 && line == $line
reverse-continue
end

define mrb-print
print mrb_debug_eval(mrb, dbg, $arg0, $_strlen($arg0), NULL, 0)
end

