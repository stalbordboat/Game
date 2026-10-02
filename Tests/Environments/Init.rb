# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Entry Point

if Env['GAME_PHYSFS_ARCHIVE'].eql? 'Test.zip'
  mrb_load 'Test.rb'
  mrb_load 'PhysfsFile.rb'
  mrb_load 'PhysfsFileUtils.rb'
  mrb_load 'PhysfsFileUtilsStat.rb'
else
  mrb_load '../../Test.rb'
  mrb_load 'SDLFile.rb'
  mrb_load 'SDLFileUtils.rb'
  mrb_load 'SDLFileUtilsStat.rb'
end

mrb_load 'NoWindow.rb'
mrb_load 'NoEvents.rb'
mrb_load 'NoAudio.rb'

native_load 'Test.so'

found_at = 'Environments/Init.rb'

# The native_test? method should be defined in Test.so.
value_a = native_test?
value_b = false
assert_true "#{found_at}: native_test?", value_a, value_b
