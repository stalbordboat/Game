# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Kernel.rb'

# Constants

send_test :found_at => path, :within => :constant_types? do
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

send_test :found_at => path, :within => :constant_values? do
  EXECUTABLE_NAME.eql?('../../game')                             &&
  ARGV.join(' ').eql?('-foo -bar')                               &&
  MAJOR.eql?('0')                                                &&
  MINOR.eql?('5')                                                &&
  PATCH.eql?('1')                                                &&
  RELEASE_TYPE.eql?('')                                          &&
  COPYRIGHT.eql?('MIT LICENSE - Copyright (c) 2026 Ralph Desir') &&
  DEFAULT_WINDOW_WIDTH.eql?(1280)                                &&
  DEFAULT_WINDOW_HEIGHT.eql?(720)                                &&
  NATIVE_LOAD_COUNT_MAX.eql?(50)
end

send_test :found_at => path, :within => :constant_platform_values? do
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

send_test :found_at => path, :within => :method_types? do
  absolute_path('.').string? &&
  open_url('.').nil?         &&
  clear_error.nil?
end

send_test :found_at => path, :within => :method_values? do
  absolute_path = Env['PWD'] + '/' + 'Tests/General'

  absolute_path('.').eql?(absolute_path) &&
  open_url('.').nil?                     &&
  clear_error.nil?
end
