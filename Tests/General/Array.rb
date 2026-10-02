# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Array.rb'

# Instance Methods

send_test :found_at => path, :within => :limit? do
  ary = [1, 2, 3]

  limit = ary.limit
  size  = ary.size

  limit.eql?(size - 1)
end

