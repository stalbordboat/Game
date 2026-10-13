# General Documentation:    https://ruby.github.io/rake/
# Domain-Specific Language: https://ruby.github.io/rake/Rake/DSL.html

require          'rake/clean'
require_relative 'Tasks/tasks.rb'

# =============
# Command Names
# =============

C_COMPILER    = ENV['CC'] || 'cc'
BIN   = ENV['BIN'] || 'game'
MRBC  = "#{BIN}-mrbc"

# =====
# Paths
# =====

SRC_DIRNAME     = 'Src'
INCLUDE_DIRNAME = 'Include'
NATIVE_DIRNAME  = 'Native'
MRBLIB_DIRNAME  = 'Mrblib'
NATIVE_PATH     = "#{INCLUDE_DIRNAME}/#{NATIVE_DIRNAME}"
PREFIX          = ENV['PREFIX'] || "#{ENV['HOME']}/.local"
BIN_PREFIX      = "#{PREFIX}/bin"
INC_PREFIX      = "#{PREFIX}/include/GameNDK"

# =====
# Flags
# =====

OPTIMIZATION_FLAGS  = %w(-O2).join ' '
WARNING_FLAGS       = %w(-Wall -Werror -Wextra).join ' '
INCLUDE_FLAGS       = %W(-I #{INCLUDE_DIRNAME}).join ' '
ASSERT_LEVEL        = ENV['ASSERT_LEVEL'] || '2'
DEFINE_FLAGS        = %W(-D _GNU_SOURCE -D SDL_ASSERT_LEVEL=#{ASSERT_LEVEL}).join ' '
PKGS                = %w(game-mruby sdl3 physfs sdl3-mixer).join ' '

# ==============
# Specifications
# ==============

SOURCES = FileList["#{SRC_DIRNAME}/*.c"]

build :this_executable => BIN, :with_this_compiler => C_COMPILER do |compiler|
  compiler.optimizations = OPTIMIZATION_FLAGS
  compiler.warnings      = WARNING_FLAGS
  compiler.include       = INCLUDE_FLAGS
  compiler.defines       = DEFINE_FLAGS
  compiler.sources       = SOURCES
  compiler.pkgs          = PKGS
end

compile :bytecode_c,
        :with_this_compiler => MRBC,
        :move_output_from   => MRBLIB_DIRNAME,
        :to                 => INCLUDE_DIRNAME

compile :bytecode_mrb,
        :with_this_compiler => MRBC,
        :move_output_from   => MRBLIB_DIRNAME

desc 'Moves install files to the install path'
task :install do |task|
  verbose = !task.application.options.silent

  FileUtils.install(BIN, BIN_PREFIX, verbose: verbose)

  FileUtils.cp_r(NATIVE_PATH, INC_PREFIX, verbose: verbose)
end

desc 'Removes install files from the install path'
task :uninstall do |task|
  verbose = !task.application.options.silent

  FileUtils.cd BIN_PREFIX, verbose: verbose do
    FileUtils.rm_f(BIN, verbose: verbose)
  end

  FileUtils.cd INC_PREFIX, verbose: verbose do
    FileUtils.rm_rf(NATIVE_DIRNAME, verbose: verbose)
  end
end

CLEAN.include("#{SRC_DIRNAME}/*.o", BIN)

Task::Test.new("../../#{BIN}") do |spec|
  spec.check_symbols = 'Tests/CheckSymbols'
  spec.environments  = 'Tests/Environments'
  spec.window        = 'Tests/Window'
  spec.audio         = 'Tests/Audio'
  spec.events        = 'Tests/Events'
  spec.general       = 'Tests/General'
end
