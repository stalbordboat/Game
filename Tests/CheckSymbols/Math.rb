# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Math.rb:'

%w(PI E INT_MAX INT_MIN).const_defined_tests found_at, Math

%w(
acos
asin
atan
atan2
ceil
cos
exp
fabs
floor
trunc
fmod
log
log10
pow
round
lround
sin
sqrt
tan
abs
).response_tests found_at, Math
