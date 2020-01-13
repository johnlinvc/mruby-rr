define mrb-info-local 
p dbgcmd_info_local(mrb,mrdb_state_get(dbg))
end
define mrb-list
p dbgcmd_list(mrb,mrdb_state_get(dbg))
end
define mrb-break
break mrdb.c:575 if $_streq(file, $arg0) == 1 && line == $arg1
end
