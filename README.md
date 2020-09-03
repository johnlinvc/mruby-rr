# mruby-rr: Time Traveling Debugger For mruby Using rr (Experimental)

mruby-rr is an __exprimental__ Time Traveling Debugger for mruby that based on Mozilla's rr. `mruby-rr` supports record and replay of mruby program execution. We can record the tough bug using mruby-rr for just once. Afterwards we can playback the execution as many times as we want. `mruby-rr` can also do time traveling operations like `reverse-next` and evaluating expressions.

# Install

1. install rr https://rr-project.org
2. Compile mruby with following settings in `build_config.rb`
```
MRuby::Build.new do |conf|
...
  enable_debug # Enable debug symbols
  conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK) # Enable debug hook
  conf.gem :git => 'https://github.com/johnlinvc/mruby-rr.git' # Install mruby-rr tracepoint
...
end
```
3. clone this project

# Usage

`./mruby-rr record program.rb` to record the execution of the mruby program. Current implementation requires typing mrdb command `run` and `Control-d` to leave the mrdb in mruby-rr.

`./mruby-rr replay` to replay the last recorded session. Current implementation require to do a `break` and `continue` before others commands can work. Use `Control + d` to leave the current debug session.

## Commands

`break "filename" line` : Break at the line of the specified file. For example, 'mrb-break "hello.rb" 3'. notice the double quote around the filename.

`continue`: Continue execution until reaching the next breakpoint.

`next`: Continue execution until reaching the next line in the same file.

`reverse-continue`: Continue execution in reverse order until reaching the previous breakpoint.

`reverse-next`: Continue execution in reverse order until reaching the previous line in the same file.

`print "mruby expression"`: Execute the mruby expression in current context. All the side effects like variable mutation will be discarded after execution continues. For example, `mrb-print "p a"` prints the value of `a`.

`info break`: List current breakpoints

`list`: Show the file contents around current line.

`restart`: Replay the recorded session from the beginning.
