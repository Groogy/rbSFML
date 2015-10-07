# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

$CXXFLAGS += "--std=c++0x"

# Give it a name
extension_name = 'rbsfml'

# Try and find SFML
HEADER_DIRS = [
  "C:/Program Files (x86)/SFML/include",
]
LIB_DIRS = [
  "C:/Program Files (x86)/SFML/lib",
]

dir_config("libs", HEADER_DIRS, LIB_DIRS)

have_library("libsfml-system")

create_header
create_makefile(extension_name)