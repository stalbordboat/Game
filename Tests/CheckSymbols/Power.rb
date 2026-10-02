# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Power.rb:'

%w(
unknown?
on_battery?
no_battery?
charging?
charged?
seconds
percent
).response_tests found_at, Power
