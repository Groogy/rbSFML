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
]
LIB_DIRS = [
  "C:/Program Files (x86)/SFML/lib",
]

dir_config("config", HEADER_DIRS, LIB_DIRS)

have_library("sfml-system-s") or raise "Need supported version of sfml-system!"

create_header
create_makefile(extension_name)