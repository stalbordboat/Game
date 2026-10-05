# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

PATH = 'General/Array.rb'

# Instance Methods

send_test :found_at => PATH, :within_block => :instance_methods_defined? do
  ary = []

  methods = %w(limit)

  methods.methods_defined? :within => ary
end

send_test :found_at => PATH, :within_block => :limit? do
  ary = [1, 2, 3]

  limit = ary.limit
  size  = ary.size

  limit.eql?(size - 1)
end

