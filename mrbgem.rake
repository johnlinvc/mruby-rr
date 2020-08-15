MRuby::Gem::Specification.new('mruby-rr') do |spec|
  spec.license = 'APACHE2'
  spec.author  = 'John Lin'
  spec.summary = 'mruby-rr helper'
  spec.cc.include_paths << "#{build.root}/src"
  spec.cc.flags << '-g'

  spec.add_dependency('mruby-bin-debugger')
end
