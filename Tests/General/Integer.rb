# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Integer.rb'

# Instance Methods

send_test :found_at => path, :within => :backward? do
  4.backward(4).eql?(3) &&
  3.backward(4).eql?(2) &&
  2.backward(4).eql?(1) &&
  1.backward(4).eql?(0) &&
  0.backward(4).eql?(4)
end

send_test :found_at => path, :within => :forward? do
  0.forward(4).eql?(1) &&
  1.forward(4).eql?(2) &&
  2.forward(4).eql?(3) &&
  3.forward(4).eql?(4) &&
  4.forward(4).eql?(0)
end
