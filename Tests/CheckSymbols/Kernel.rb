# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Kernel.rb:'

%w(
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
).const_defined_tests found_at, Kernel

%w(assert_true absolute_path open_url).response_tests found_at, Kernel
