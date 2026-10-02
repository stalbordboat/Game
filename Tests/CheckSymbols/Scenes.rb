# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Scenes.rb:'

%w(update goto call return stack empty?).response_tests found_at, Scene
