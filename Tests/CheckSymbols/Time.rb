# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Time.rb:'

%w(
MAX
MIN
DATE_FORMAT_YYYYMMDD
DATE_FORMAT_DDMMYYYY
DATE_FORMAT_MMDDYYYY
FORMAT_24HR
FORMAT_12HR
).const_defined_tests found_at, Time

%w(
now
date_format
format
to_seconds
to_nanoseconds
).response_tests found_at, Time
