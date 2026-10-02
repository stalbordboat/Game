# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Testing Framework API
#
# This framework extends Enumerable so that all Enumerable objects(Array, Hash, etc.) can be used to test in batches.
#
# Example: Checking if the symbols that represent methods are actually defined. 
#
# found_at = 'CheckSymbols/Rect.rb:'
# rect     = Rect.new
#
# %w(x y w h width height).response_tests found_at, rect
#
# Enumerable
# Description: This is mixed-in so that other classes can use its batch testing methods(e.g. response_tests, etc.).
#
# Float
# Description: It checks whether two floating-point numbers are approximately equal within a small tolerance, called epsilon.
#
# Top Level
# Description: Most tests are tested in batches using Enumerable, the top-level method(s) operate on singular tests at a time.
#
# send_test, provides a testing block which evaluates the last expression in the block(value_a) against a true value(value_b).
# If an exception is raised then an error message is displayed in the description.
#
# recover?, rescues from an exception raised. This is useful for circumstances where the only
# way to test an expression is to see if it raises an exception, but we don't want to treat that exception as fail condition. 
# For instance, some classes can't be copied with the clone or dup methods, so they raise an exception when used.
# That's the type of expected behavior that we want to "recover" from. It return true effectively "recovering." It returns
# false if an exception was not raised.
#
# skip, this method logs a message and returns true, effectively skipping a test.
#
# simulate_main_loop, Runs a block of code between Graphics.update and Graphics.draw.

def send_test(found_at: '', within: nil)
  begin
    value_a = yield
  rescue => e
    error_message = e.message
  end
  desc    = "found_at => #{found_at} within => #{within} #{error_message}"
  value_b = true

  assert_true(desc, value_a, value_b)
end

def recover?
  begin
    yield
    status = false
  rescue
    status = true
  end

  clear_error

  status
end

def skip(message)
  Log.info('Skip:', message)

  true
end

def simulate_main_loop
  while true
    begin
      Graphics.update
    rescue
      break
    end

    yield

    begin
      Graphics.draw
    rescue
      break
    end
  end
end

module Enumerable
  def const_defined_tests(path, obj)
    self.each do |s|
      value_a = obj.const_defined?(s)
      value_b = true
      desc    = "#{path} #{obj}.const_defined? #{s.inspect}"

      assert_true(desc, value_a, value_b)
    end
  end

  def response_tests(path, obj)
    self.each do |s|
      value_a = obj.respond_to?(s.to_sym)
      value_b = true
      desc    = "#{path} #{obj}.respond_to? #{s.inspect}"

      assert_true(desc, value_a, value_b)
    end
  end
end

class Float
  def approx?(other, epsilon = 1e-6)
    (self - other).abs < epsilon
  end
end

# TODO: Document This!!!
class Object
  def bool?
    self.kind_of?(TrueClass) || self.kind_of?(FalseClass)
  end

  def int?
    self.kind_of? Integer
  end

  def float?
    self.kind_of? Float
  end

  def string?
    self.kind_of? String
  end

  def array?
    self.kind_of? Array
  end

  def hash?
    self.kind_of? Hash
  end
end

# TODO: Document This!!!
class Integer
  def greater_than?(value)
    self > value
  end

  def less_than?(value)
    self < value
  end
end
