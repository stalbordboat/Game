# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Math.rb'

# Constants

send_test :found_at => path, :within => :constants_types? do
  Math::PI.float?    &&
  Math::E.float?     &&
  Math::INT_MAX.int? &&
  Math::INT_MIN.int?
end

send_test :found_at => path, :within => :constants_values? do
  Math::PI.eql?(3.14159265358979323846264338327950288) &&
  Math::E.eql?(2.718281828459045)
  # NOTE: Ruby gives and integer overflow error when testing INT_MAX, and INT_MIN. I don't know how to directly test this...
end

# Methods

send_test :found_at => path, :within => :methods_types? do
  Math.acos(-1.0).float?        &&
  Math.asin(-1.0).float?        &&
  Math.atan(-1.0).float?        &&
  Math.atan2(0, 1).float?       &&
  Math.ceil(0.0).float?         &&
  Math.cos(Math::PI / 4).float? &&
  Math.exp(-2.0).float?         &&
  Math.fabs(0.0).float?         &&
  Math.floor(0.1).float?        &&
  Math.trunc(0.1).float?        &&
  Math.fmod(5.3, 2.0).float?    &&
  Math.log(0.5).float?          &&
  Math.log10(0.5).float?        &&
  Math.pow(2.0, 2.0).float?     &&
  Math.round(0.4).float?        &&
  Math.lround(0.4).int?         &&
  Math.sin(0.523599).float?     &&
  Math.sqrt(4.0).float?         &&
  Math.tan(Math::PI / 4).float? &&
  Math.abs(0.0).int?
end

send_test :found_at => path, :within => :trig_methods_values? do
  Math.sin(0).approx?(0)                          &&
  Math.sin(0.523599).approx?(0.5)                 &&
  Math.sin(0.785398).approx?(0.707107)            &&
  Math.sin(1.570796).approx?(1.0)                 &&
  Math.sin(3.141593).approx?(0.0)                 &&
  Math.sin(4.712389).approx?(-1.0)                &&
  Math.sin(4.712389).approx?(-1.0)                &&
  Math.sin(6.283185).approx?(0.0)                 &&
  Math.asin(-1.0).approx?(-Math::PI / 2)          &&
  Math.asin(-0.5).approx?(-Math::PI / 6)          &&
  Math.asin(0.0).approx?(0.0)                     &&
  Math.asin(0.0).approx?(0.0)                     &&
  Math.asin(0.5).approx?(Math::PI / 6)            &&
  Math.asin(1.0).approx?(Math::PI / 2)            &&
  Math.cos(0).approx?(1.0)                        &&
  Math.cos(Math::PI / 6).approx?(0.866025)        &&
  Math.cos(Math::PI/4).approx?(0.707107)          &&
  Math.cos(Math::PI / 2).approx?(0.0)             &&
  Math.cos(Math::PI).approx?(-1.0)                &&
  Math.cos((3 * Math::PI) / 2).approx?(0.0)       &&
  Math.cos(2 * Math::PI).approx?(1.0)             &&
  Math.acos(-1.0).approx?(Math::PI)               &&
  Math.acos(-0.5).approx?((2 * Math::PI) / 3)     &&
  Math.acos(0.0).approx?(Math::PI / 2)            &&
  Math.acos(0.5).approx?(Math::PI / 3)            &&
  Math.acos(1.0).approx?(0.0)                     &&
  Math.tan(0).approx?(0.0)                        &&
  Math.tan(Math::PI / 6).approx?(0.577350)        &&
  Math.tan(Math::PI / 4).approx?(1.0)             &&
  Math.tan(Math::PI).approx?(0.0)                 &&
  Math.tan((3 * Math::PI)/4).approx?(-1.0)        &&
  Math.atan(-1.0).approx?(-Math::PI / 4)          &&
  Math.atan(0.0).approx?(0.0)                     &&
  Math.atan(1.0).approx?(Math::PI / 4)            &&
  Math.atan2(0, 1).approx?(0.0)                   &&
  Math.atan2(1, 0).approx?(Math::PI / 2)          &&
  Math.atan2(0, -1).approx?(Math::PI)             &&
  Math.atan2(-1, 0).approx?(-Math::PI / 2)        &&
  Math.atan2(1, 1).approx?(Math::PI / 4)          &&
  Math.atan2(1, -1).approx?(3 * Math::PI / 4)     &&
  Math.atan2(-1, -1).approx?((-3 * Math::PI) / 4) &&
  Math.atan2(-1, 1).approx?((-Math::PI) / 4)
end

send_test :found_at => path, :within => :expos_and_logs_methods_values? do
  Math.exp(-2.0).approx?(0.135335)   &&
  Math.exp(-1.0).approx?(0.367879)   &&
  Math.exp(0.0).approx?(1.0)         &&
  Math.exp(1.0).approx?(2.718282)    &&
  Math.exp(2.0).approx?(7.389056)    &&
  Math.log(0.1).approx?(-2.302585)   &&
  Math.log(0.5).approx?(-0.693147)   &&
  Math.log(1.0).approx?(0.0)         &&
  Math.log(Math::E).approx?(1.0)     &&
  Math.log(10.0).approx?(2.302585)   &&
  Math.log10(0.1).approx?(-1.0)      &&
  Math.log10(0.5).approx?(-0.301030) &&
  Math.log10(1.0).approx?(0.0)       &&
  Math.log10(10.0).approx?(1.0)      &&
  Math.log10(100.0).approx?(2.0)     &&
  Math.pow(2.0, 2.0).approx?(4.0)    &&
  Math.pow(2.0, 3.0).approx?(8.0)    &&
  Math.pow(4.0, 0.5).approx?(2.0)    &&
  Math.pow(9.0, 0.5).approx?(3.0)    &&
  Math.pow(2.0, -1.0).approx?(0.5)   &&
  Math.pow(10.0, 0.0).approx?(1.0)   &&
  Math.sqrt(0.0).approx?(0.0)        &&
  Math.sqrt(1.0).approx?(1.0)        &&
  Math.sqrt(4.0).approx?(2.0)        &&
  Math.sqrt(9.0).approx?(3.0)        &&
  Math.sqrt(2.0).approx?(1.414214)   &&
  Math.sqrt(0.25).approx?(0.5)
end

send_test :found_at => path, :within => :rounding_and_trunc_methods_values? do
  Math.ceil(0.0).approx?(0.0)    &&
  Math.ceil(0.1).approx?(1.0)    &&
  Math.ceil(1.9).approx?(2.0)    &&
  Math.ceil(-0.1).approx?(0.0)   &&
  Math.ceil(-1.9).approx?(-1.0)  &&
  Math.ceil(2.0).approx?(2.0)    &&
  Math.floor(0.0).approx?(0.0)   &&
  Math.floor(0.1).approx?(0.0)   &&
  Math.floor(1.9).approx?(1.0)   &&
  Math.floor(-0.1).approx?(-1.0) &&
  Math.floor(-1.9).approx?(-2.0) &&
  Math.floor(2.0).approx?(2.0)   &&
  Math.trunc(0.0).approx?(0.0)   &&
  Math.trunc(0.1).approx?(0.0)   &&
  Math.trunc(1.9).approx?(1.0)   &&
  Math.trunc(-0.1).approx?(0.0)  &&
  Math.trunc(-1.9).approx?(-1.0) &&
  Math.trunc(2.0).approx?(2.0)   &&
  Math.round(0.0).approx?(0.0)   &&
  Math.round(0.4).approx?(0.0)   &&
  Math.round(0.5).approx?(1.0)   &&
  Math.round(1.5).approx?(2.0)   &&
  Math.round(2.3).approx?(2.0)   &&
  Math.round(-0.4).approx?(0.0)  &&
  Math.round(-0.5).approx?(-1.0) &&
  Math.round(-1.5).approx?(-2.0) &&
  Math.lround(0.4).eql?(0)       &&
  Math.lround(0.5).eql?(1)       &&
  Math.lround(-0.5).eql?(-1)     &&
  Math.lround(1.6).eql?(2)       &&
  Math.lround(-1.6).eql?(-2)     &&
  Math.lround(2.0).eql?(2)
end

send_test :found_at => path, :within => :abs_and_mod_methods_values? do
  Math.fabs(0.0).approx?(0.0)            &&
  Math.fabs(-0.0).approx?(0.0)           &&
  Math.fabs(1.5).approx?(1.5)            &&
  Math.fabs(-1.5).approx?(1.5)           &&
  Math.fabs(Math::PI).approx?(Math::PI)  &&
  Math.fabs(-2.718282).approx?(2.718282) &&
  Math.abs(0.0).eql?(0)                  &&
  Math.abs(1.0).eql?(1)                  &&
  Math.abs(-1.0).eql?(1)                 &&
  Math.abs(123).eql?(123)                &&
  Math.fmod(5.3, 2.0).approx?(1.3)       &&
  Math.fmod(5.0, 2.0).approx?(1.0)       &&
  Math.fmod(-5.0, 2.0).approx?(-1.0)     &&
  Math.fmod(5.0, -2.0).approx?(1.0)      &&
  Math.fmod(-5.0, -2.0).approx?(-1.0)
end
