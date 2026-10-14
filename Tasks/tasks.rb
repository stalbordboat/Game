# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: 
# Reference Documentation: https://ruby.github.io/rake/Rake/DSL.html
require 'rake/dsl_definition'
require 'rake/file_list'

include Rake::DSL

# Defined in build.rb.
task :default => :build

require_relative 'build.rb'
require_relative 'compile.rb'
require_relative 'install.rb'
require_relative 'test.rb'
