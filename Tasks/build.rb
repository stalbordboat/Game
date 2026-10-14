# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: 
require_relative 'write_platform.rb'

class Executable
  attr_accessor :optimizations
  attr_accessor :warnings
  attr_accessor :include
  attr_accessor :defines
  attr_accessor :sources
  attr_accessor :pkgs
  attr_reader   :executable
  attr_reader   :compiler

  def initialize(executable, compiler)
    @compiler   = compiler
    @executable = executable
  end

  def build
    cflags  = %W(#{@optimizations} #{@warnings} #{@include} #{@defines}).join(' ')
    objects = sources.ext('.o')

    compile cflags
    link    cflags, objects
    write_platform
  end

  private

  def pkg_config(opt)
    `pkg-config --#{opt} #{PKGS}`
  end

  def compile(cflags)
    rule '.o' => '.c' do |file_task|
      src      = file_task.source
      obj      = "#{File.basename src, '.c'}.o"
      dirname  = src.split('/').first
      obj_path = "#{dirname}/#{obj}"

      # Compile individual object files.
      sh "#{@compiler} #{cflags} -c #{src} -o #{obj_path} #{ pkg_config('cflags') }"
    end
  end

  def link(cflags, objects)
    desc 'Builds all source files'
    task :build => objects do
      # Link object files into the binary executable.
      sh "#{@compiler} #{cflags} #{objects} -o #{@executable} #{ pkg_config('libs') }"
    end
  end
end

def build(this_executable: nil, with_this_compiler: nil)
  raise 'The build spec needs an executbale to build with, example: build this_executable: "game"' if this_executable.nil?
  raise 'The build spec needs a compiler to build with, example: build with_this_compiler: "cc"'   if with_this_compiler.nil?
  executable = Executable.new(this_executable, with_this_compiler)

  yield(executable)

  executable.build
end
