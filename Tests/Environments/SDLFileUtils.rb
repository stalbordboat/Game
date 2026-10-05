# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

PATH           = 'Environments/SDLFileUtils.rb'
FILENAME_WRITE = 'Test_Write.txt'
TEMP_DIRNAME   = 'Temp/'
TEMP_FILENAME  = 'Temp.txt'

send_test :found_at => PATH, :within_block => :constants_defined? do
  constants = %w(
                  DIR_HOME
                  DIR_DESKTOP
                  DIR_DOCUMENTS
                  DIR_DOWNLOADS
                  DIR_MUSIC
                  DIR_PICTURES
                  DIR_PUBLICSHARE
                  DIR_SAVEDGAMES
                  DIR_SCREENSHOTS
                  DIR_TEMPLATES
                  DIR_VIDEOS
                  Stat
                )

  constants.constants_defined? :within => FileUtils
end

send_test :found_at => PATH, :within_block => :functions_defined? do
  functions = %w(
                  entries
                  copy
                  make_directory
                  base_path
                  current_directory
                  pref_path
                  user_directory
                  remove
                  rename_path
                  move
                  touch
                )

  functions.methods_defined? :within => FileUtils
end

send_test :found_at => PATH, :within_block => :entries? do
  entries = FileUtils.entries('.')

  if entries.kind_of?(Array)
    entries.include?('SDLFile.rb')
  else
    false
  end
end

send_test :found_at => PATH, :within_block => :entries_with_ext? do
  FileUtils.entries('.', '*.txt').include?(FILENAME_WRITE)
end

send_test :found_at => PATH, :within_block => :make_directory? do
  FileUtils.make_directory(TEMP_DIRNAME).nil?
end

send_test :found_at => PATH, :within_block => :copy? do
  src  = FILENAME_WRITE
  dest = TEMP_DIRNAME + src

  FileUtils.copy(src, dest).nil?
end

send_test :found_at => PATH, :within_block => :base_path? do
  path_base = FileUtils.base_path

  path_base.include?(Env['HOME']) && path_base.include?('/Game/')
end

send_test :found_at => PATH, :within_block => :current_directory? do
  path_current = FileUtils.current_directory

  path_current.include?(Env['HOME']) && path_current.include?('/Game/Tests/Environments')
end

send_test :found_at => PATH, :within_block => :pref_path? do
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

send_test :found_at => PATH, :within_block => :home_directory? do
  FileUtils.user_directory(FileUtils::DIR_HOME).include?(Env['HOME'])
end

send_test :found_at => PATH, :within_block => :desktop_directory? do
  user_directory?(FileUtils::DIR_DESKTOP)
end

send_test :found_at => PATH, :within_block => :documents_directory? do
  user_directory?(FileUtils::DIR_DOCUMENTS)
end

send_test :found_at => PATH, :within_block => :downloads_directory? do
  user_directory?(FileUtils::DIR_DOWNLOADS)
end

send_test :found_at => PATH, :within_block => :music_directory? do
  user_directory?(FileUtils::DIR_MUSIC)
end

send_test :found_at => PATH, :within_block => :pictures_directory? do
  user_directory?(FileUtils::DIR_PICTURES)
end

send_test :found_at => PATH, :within_block => :publicshare_directory? do
  user_directory?(FileUtils::DIR_PUBLICSHARE)
end

send_test :found_at => PATH, :within_block => :savedgames_directory? do
  user_directory?(FileUtils::DIR_SAVEDGAMES)
end

send_test :found_at => PATH, :within_block => :screenshots_directory? do
  user_directory?(FileUtils::DIR_SCREENSHOTS)
end

send_test :found_at => PATH, :within_block => :templates_directory? do
  user_directory?(FileUtils::DIR_TEMPLATES)
end

send_test :found_at => PATH, :within_block => :videos_directory? do
  user_directory?(FileUtils::DIR_VIDEOS)
end

send_test :found_at => PATH, :within_block => :create_temp_file? do
  FileUtils.touch(TEMP_FILENAME).nil?
end

send_test :found_at => PATH, :within_block => :rename_path? do
  src  = TEMP_FILENAME
  dest = 'Temp-Renamed.txt'

  status = FileUtils.rename_path(src, dest).nil?

  src  = 'Temp-Renamed.txt'
  dest = TEMP_FILENAME

  FileUtils.rename_path(src, dest)

  status
end

send_test :found_at => PATH, :within_block => :remove? do
  FileUtils.remove(TEMP_FILENAME).nil?
end
