require 'rake'
require 'rbconfig'
include RbConfig

RUBY_INC = CONFIG['rubyhdrdir']
RUBY_LIB = CONFIG['libdir']
RUBY_LINK = CONFIG['SOLIBS'] + CONFIG['LIBRUBYARG_SHARED']

CXX = CONFIG['CXX']
CXX_FLAGS = "-std=c++0x -O3 -Wall -Wextra -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']} "

LD = CONFIG['LDSHAREDXX'].sub("$(if $(filter-out -g -g0,#{CONFIG['debugflags']}),,-s)", "")
LD_FLAGS = "-L#{RUBY_LIB} #{RUBY_LINK}".sub("$(DEFFILE)", "")

task :default do
  sh "#{CXX} #{CXX_FLAGS} -c test.cpp -o test.o"
  sh "#{LD} -s test.o -o test.so #{LD_FLAGS}"
  sh "irb -r./test"
end
