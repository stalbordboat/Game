# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/FileUtils.rb:'

%w(
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
).const_defined_tests found_at, FileUtils

%w(
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
).response_tests found_at, FileUtils

%w(
exist?
file?
dir?
other?
size
length
create_time
modify_time
access_time
).response_tests found_at, FileUtils::Stat

