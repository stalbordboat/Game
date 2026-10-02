# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path = 'Environments/NoEvents.rb'

send_test :found_at => path, :within => :env_no_events do
  !Env['GAME_NO_EVENTS'].nil?
end

send_test :found_at => path, :within => :no_events do
  recover? { Event.fetching? }
end
