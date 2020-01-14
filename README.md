# mruby-rr: Time Traveling Debugger For mruby Using rr

mruby-rr is a Time Traveling Debugger for mruby that based on Mozilla's rr. `mruby-rr` supports record and replay of mruby program execution. We can record the tough bug using mruby-rr for just once. Afterwards we can playback the execution as many times as we want. `mruby-rr` can also do time traveling operations like `reverse-next` and evaluating expressions.

# Install

- install rr https://rr-project.org
- mruby compiled with `enable_debug`, put $mruby/bin into `$PATH`
- clone this project

# Usage

`./mruby-rr record program.rb` to record the execution of the mruby program. Current implementation requires typing mrdb command `run` and `Control-d` to leave the mrdb in mruby-rr.

`./mruby-rr replay` to replay the recorded session. Current implementation require to do a `mrb-break` and `mrb-continue` before others commands can work. `Control + d` leaves the current debug session.

## Commands

`mrb-break "filename" line` : break at the line of the specified file. For example, 'mrb-break "hello.rb" 3'. notice the double quote around the filename.

`mrb-continue`: continue execution until reaching the next breakpoint.

`mrb-next`: continue execution until reaching the next line in the same file.

`mrb-reverse-continue`: continue execution in reverse order until reaching the previous breakpoint.

`mrb-reverse-next`: continue execution in reverse order until reaching the previous line in the same file.

`mrb-print "mruby expression"`: execute the mruby expression in current context. All the side effects like variable mutation will be discarded after execution continues. For example, `mrb-print "p a"` prints the value of `a`.

`mrb-info-local`: list the local variables in scope.

`mrb-list`: show the file content around current line.
