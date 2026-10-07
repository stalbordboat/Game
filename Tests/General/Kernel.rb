# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

PATH = 'General/Kernel.rb'

# Constants

send_test :found_at => PATH, :within_block => :constants_defined? do
  constants = %w(
                  EXECUTABLE_NAME
                  ARGV
                  MAJOR
                  MINOR
                  PATCH
                  RELEASE_TYPE
                  COPYRIGHT
                  PLATFORM
                  DEFAULT_WINDOW_WIDTH
                  DEFAULT_WINDOW_HEIGHT
                  NATIVE_LOAD_COUNT_MAX
                )

  constants.constants_defined? :within => Kernel
end

send_test :found_at => PATH, :within_block => :constant_types? do
  EXECUTABLE_NAME.string?    &&
  ARGV.array?                &&
  MAJOR.string?              &&
  MINOR.string?              &&
  PATCH.string?              &&
  RELEASE_TYPE.string?       &&
  COPYRIGHT.string?          &&
  PLATFORM.string?           &&
  DEFAULT_WINDOW_WIDTH.int?  &&
  DEFAULT_WINDOW_HEIGHT.int? &&
  NATIVE_LOAD_COUNT_MAX.int?
end

send_test :found_at => PATH, :within_block => :constant_values? do
  EXECUTABLE_NAME.eql?('../../game')                             &&
  ARGV.join(' ').eql?('-foo -bar')                               &&
  MAJOR.eql?('0')                                                &&
  MINOR.eql?('7')                                                &&
  PATCH.eql?('1')                                                &&
  RELEASE_TYPE.eql?('')                                          &&
  COPYRIGHT.eql?('MIT LICENSE - Copyright (c) 2026 Ralph Desir') &&
  DEFAULT_WINDOW_WIDTH.eql?(1280)                                &&
  DEFAULT_WINDOW_HEIGHT.eql?(720)                                &&
  NATIVE_LOAD_COUNT_MAX.eql?(50)
end

send_test :found_at => PATH, :within_block => :constant_platform_values? do
  PLATFORM.eql?('x86_64-linux')     ||
  PLATFORM.eql?('aarch64-linux')    ||
  PLATFORM.eql?('armv7l-linux')     ||
  PLATFORM.eql?('armv6l-linux')     ||
  PLATFORM.eql?('i686-linux')       ||
  PLATFORM.eql?('i386-linux')       ||
  PLATFORM.eql?('riscv64-linux')    ||
  PLATFORM.eql?('ppc64le-linux')    ||
  PLATFORM.eql?('ppc64-linux')      ||
  PLATFORM.eql?('s390x-linux')      ||
  PLATFORM.eql?('mips-linux')       ||
  PLATFORM.eql?('mips64-linux')     ||
  PLATFORM.eql?('x86_64-darwin')    ||
  PLATFORM.eql?('arm64-darwin')     ||
  PLATFORM.eql?('x86_64-netbsd')    ||
  PLATFORM.eql?('amd64-netbsd')     ||
  PLATFORM.eql?('i386-netbsd')      ||
  PLATFORM.eql?('aarch64-netbsd')   ||
  PLATFORM.eql?('armv7-netbsd')     ||
  PLATFORM.eql?('powerpc-netbsd')   ||
  PLATFORM.eql?('sparc64-netbsd')   ||
  PLATFORM.eql?('x86_64-msys_nt')   ||
  PLATFORM.eql?('x86_64-cygwin_nt')
end

# Methods

send_test :found_at => PATH, :within_block => :methods_defined? do
  methods = %w(assert_true absolute_path open_url)

  methods.methods_defined? :within => Kernel
end

# Just to avoid calling open_url twice.
status_nil = open_url('.').nil?

send_test :found_at => PATH, :within_block => :method_types? do
  absolute_path('.').string? &&
  status_nil                 &&
  clear_error.nil?
end

send_test :found_at => PATH, :within_block => :method_values? do
  absolute_path = Env['PWD'] + '/' + 'Tests/General'

  absolute_path('.').eql?(absolute_path) &&
  status_nil                             &&
  clear_error.nil?
end
