# General Documentation:    https://ruby.github.io/rake/
# Domain-Specific Language: https://ruby.github.io/rake/Rake/DSL.html

require 'rake/clean'

# =============
# Command Names
# =============

CC    = ENV['CC'] || 'cc'
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

task :default => :all

SOURCES = FileList["#{SRC_DIRNAME}/*.c"]
OBJECTS = SOURCES.ext '.o'
CFLAGS  = %W(#{OPTIMIZATION_FLAGS} #{WARNING_FLAGS} #{INCLUDE_FLAGS} #{DEFINE_FLAGS}).join ' '

def pkg_config(opt)
  `pkg-config --#{opt} #{PKGS}`
end

desc 'Builds all source files'
task :all => OBJECTS do
  # Link object files into the binary executable.
  sh "#{CC} #{CFLAGS} #{OBJECTS} -o #{BIN} #{ pkg_config 'libs' }"
end

rule '.o' => '.c' do |file_task|
  src      = file_task.source
  obj      = "#{File.basename src, '.c'}.o"
  dirname  = src.split('/').first
  obj_path = "#{dirname}/#{obj}"

  # Compile individual object files.
  sh "#{CC} #{CFLAGS} -c #{src} -o #{obj_path} #{ pkg_config 'cflags' }"
end

desc 'Compile a Ruby file'
task :mrbc, [:filename] do |task, args|
  filename = args[:filename]
  basename = File.basename(filename, '.rb')
  path     = "#{MRBLIB_DIRNAME}/#{filename}"

  sh "#{MRBC} -B #{basename}_symbol #{path}"

  src  = "#{MRBLIB_DIRNAME}/#{basename}.c"
  dest = "#{INCLUDE_DIRNAME}/#{basename}.c"

  FileUtils.mv src, dest, verbose: true
end

desc 'Moves install files to the install path'
task :install do |task|
  verbose = !task.application.options.silent

  FileUtils.install BIN, BIN_PREFIX, verbose: verbose

  FileUtils.cp_r NATIVE_PATH, INC_PREFIX, verbose: verbose
end

desc 'Removes install files from the install path'
task :uninstall do |task|
  verbose = !task.application.options.silent

  FileUtils.cd BIN_PREFIX, verbose: verbose do
    FileUtils.rm_f BIN, verbose: verbose
  end

  FileUtils.cd INC_PREFIX, verbose: verbose do
    FileUtils.rm_rf NATIVE_DIRNAME, verbose: verbose
  end
end

CLEAN.include("#{SRC_DIRNAME}/*.o", BIN)
