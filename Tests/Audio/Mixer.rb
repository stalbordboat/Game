# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the audio subsystem.

path = 'Audio/Mixer.rb:'

# A successful run of :reopen should return nil.
# A failure would raise and exception.
send_test :found_at => path, :within => :reopen do
  Mixer.reopen.nil?
end
