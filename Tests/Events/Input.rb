# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Event subsystem.

path = 'Events/Input.rb'

send_test :found_at => path, :within => :update? do
  count  = 0
  limit  = 8
  status = false

  simulate_main_loop do
    Input.update

    status = Input.quit?.nil?               &&
             Input.press?(:button_s).nil?   &&
             Input.trigger?(:button_s).nil?

    count += 1
    break if count >= limit
  end

  status
end
