# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path = 'Environments/NoWindow.rb'

send_test :found_at => path, :within_block => :env_no_window? do
  !Env['GAME_NO_WINDOW'].nil?
end

send_test :found_at => path, :within_block => :no_window? do
  recover? { Window.show }
end
