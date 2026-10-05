# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path = 'Environments/NoAudio.rb'

send_test :found_at => path, :within_block => :env_no_audio? do
  !Env['GAME_NO_AUDIO'].nil?
end

send_test :found_at => path, :within_block => :no_audio? do
  recover? { AudioRecorder.open 0 }
end
