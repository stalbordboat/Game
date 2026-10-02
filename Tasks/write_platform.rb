COPYRIGHT   = "MIT LICENSE - Ralph St.Albord (c) #{Time.now.year}"
DESCRIPTION = 'Description: A file generated during the building process to get the correct platform.'

def my_uname
  mach = `uname -m`.chomp
  name = `uname -s`.chomp

  "#{mach}-#{name.downcase}"
end

HEADER  = %Q[// #{COPYRIGHT}
// #{DESCRIPTION}
#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H

#define GAME_PLATFORM "#{my_uname}"

#endif /*GAME_PLATFORM_H*/
]

def write_platform
  File.write('Include/Native/Platform.h', HEADER)
end
