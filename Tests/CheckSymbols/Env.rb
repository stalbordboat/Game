# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Env.rb:'

%w(
[]
[]=
).response_tests found_at, Env
