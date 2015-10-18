# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

$CXXFLAGS += "--std=c++0x -DSFML_STATIC"
#$LDFLAGS += "-lsfml-system"

# Give it a name
extension_name = 'rbsfml'

# Try and find SFML
HEADER_DIRS = [
  "C:/Program Files (x86)/SFML/include",
  "C:/Program Files (x86)/glew/include",
]
LIB_DIRS = [
  "C:/Program Files (x86)/SFML/lib",
  "C:/Program Files (x86)/glew/lib",
]

dir_config("config", HEADER_DIRS, LIB_DIRS)

have_library("freetype") or raise "Need supported version freetype!"
have_library("jpeg") or raise "Need supported version jpeg!"
have_library("glew32") or raise "Need supported version glew!"
have_library("gdi32") or raise "Need supported version gdi32!"
have_library("opengl32") or raise "Need supported version opengl32!"
have_library("openal32") or raise "Need supported version openal32!"
have_library("winmm") or raise "Need supported version winmm!"
have_library("sfml-system-s") or raise "Need supported version of sfml-system!"
have_library("sfml-window-s") or raise "Need supported version of sfml-window!"
have_library("sfml-graphics-s") or raise "Need supported version of sfml-graphics!"
have_library("sfml-audio-s") or raise "Need supported version of sfml-audio!"

create_header
create_makefile(extension_name)