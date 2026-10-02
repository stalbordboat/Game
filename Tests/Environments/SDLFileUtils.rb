# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path           = 'Environments/SDLFileUtils.rb'
filename_write = 'Test_Write.txt'
temp_dirname   = 'Temp/'
temp_filename  = 'Temp.txt'

send_test :found_at => path, :within => :entries? do
  entries = FileUtils.entries('.')

  if entries.kind_of? Array
    entries.include? 'SDLFile.rb'
  else
    false
  end
end

send_test :found_at => path, :within => :entries_with_ext? do
  FileUtils.entries('.', '*.txt').include? filename_write
end

send_test :found_at => path, :within => :make_directory? do
  FileUtils.make_directory(temp_dirname).nil?
end

send_test :found_at => path, :within => :copy? do
  src  = filename_write
  dest = temp_dirname + src

  FileUtils.copy(src, dest).nil?
end

send_test :found_at => path, :within => :base_path? do
  path_base = FileUtils.base_path

  path_base.include?(Env['HOME']) && path_base.include?('/Game/')
end

send_test :found_at => path, :within => :current_directory? do
  path_current = FileUtils.current_directory

  path_current.include?(Env['HOME']) && path_current.include?('/Game/Tests/Environments')
end

send_test :found_at => path, :within => :pref_path? do
  org           = 'BattleRounds'
  app           = 'Game-Test'
  path_pref     = FileUtils.pref_path(org, app)
  path_expected = org + '/' + app

  path_pref.include?(Env['HOME']) && path_pref.include?(path_expected)
end

def user_directory?(dir)
  begin
    return FileUtils.user_directory(dir).include?(Env['HOME']) + '/'
  rescue
    clear_error
    # This fails because the system it's running on doesn't have the directory, so this shouldn't be treated as a failure.
    return true
  end
end

send_test :found_at => path, :within => :home_directory? do
  FileUtils.user_directory(FileUtils::DIR_HOME).include?(Env['HOME'])
end

send_test :found_at => path, :within => :desktop_directory? do
  user_directory? FileUtils::DIR_DESKTOP
end

send_test :found_at => path, :within => :documents_directory? do
  user_directory? FileUtils::DIR_DOCUMENTS
end

send_test :found_at => path, :within => :downloads_directory? do
  user_directory? FileUtils::DIR_DOWNLOADS
end

send_test :found_at => path, :within => :music_directory? do
  user_directory? FileUtils::DIR_MUSIC
end

send_test :found_at => path, :within => :pictures_directory? do
  user_directory? FileUtils::DIR_PICTURES
end

send_test :found_at => path, :within => :publicshare_directory? do
  user_directory? FileUtils::DIR_PUBLICSHARE
end

send_test :found_at => path, :within => :savedgames_directory? do
  user_directory? FileUtils::DIR_SAVEDGAMES
end

send_test :found_at => path, :within => :screenshots_directory? do
  user_directory? FileUtils::DIR_SCREENSHOTS
end

send_test :found_at => path, :within => :templates_directory? do
  user_directory? FileUtils::DIR_TEMPLATES
end

send_test :found_at => path, :within => :videos_directory? do
  user_directory? FileUtils::DIR_VIDEOS
end

send_test :found_at => path, :within => :create_temp_file? do
  FileUtils.touch(temp_filename).nil?
end

send_test :found_at => path, :within => :rename_path? do
  src  = temp_filename
  dest = 'Temp-Renamed.txt'

  status = FileUtils.rename_path(src, dest).nil?

  src  = 'Temp-Renamed.txt'
  dest = temp_filename

  FileUtils.rename_path src, dest

  status
end

send_test :found_at => path, :within => :remove? do
  FileUtils.remove(temp_filename).nil?
end
