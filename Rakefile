require 'rake'
require 'rubygems'
require 'rdoc/task'
require 'rake/clean'
require 'rake/gempackagetask'
require 'rbconfig'
require 'pp'
include Config
include Rake

# Configurable section
RUBYSFML_VERSION = "2.0"
SO_SRCS = {'audio' => FileList.new('sfml-audio/audio/*.cpp'),
                     'graphics' => FileList.new('sfml-graphics/graphics/*.cpp'),
                     'window' => FileList.new('sfml-window/window/*.cpp'),
                     'system' => FileList.new('sfml-system/system/*.cpp'),
                     'all' => FileList.new('sfml-all/all/*.cpp') }
OTHER_SRCS = FileList.new('shared/*.cpp')
OBJDIR = 'obj'
SODIR = 'sfml'

spec = Gem::Specification.new do |s|
    s.platform = Gem::Platform::CURRENT
    s.name     = "rbSFML"
    s.version  = RUBYSFML_VERSION
    s.authors = ["Henrik Valter Vogelius Hansson", 'Brandon Whitehead']
    s.email    = "groogy@groogy.se"
    s.homepage = 'http://sfml-dev.org'
    s.summary  = "Ruby bindings for SFML 2.0"
    s.has_rdoc = true
    s.requirements << 'none'
    s.require_path = ''
    s.files = FileList.new do |fl|
        fl.include("sfml-audio/audio/*.cpp", "sfml-audio/audio/*.hpp")
        fl.include("sfml-graphics/graphics/*.cpp", "sfml-graphics/graphics/*.hpp")
        fl.include("sfml-window/window/*.cpp", "sfml-window/window/*.hpp")
        fl.include("sfml-system/system/*.cpp", "sfml-system/system/*.hpp")
        fl.include("sfml-all/all/*.cpp", "sfml-all/all/*.hpp")
    end
    s.extensions = ["Rakefile"]
    s.description = <<-EOF
        rbSFML are bindings for the SFML library version 2.0 for Ruby.
        SFML or Simple Fast Multimedia library is is a free multimedia C++ API 
        that provides you low and high level access to graphics, input, audio, etc.
    EOF
    s.extra_rdoc_files = FileList.new do |fl|
        fl.include "doc/*.rdoc"
    end
end
verbose(false)

# Do not touch
SO_OBJS = {}
SO_SRCS.each do |file, list| 
    SO_OBJS[file] = list.collect { |fn| File.join("#{OBJDIR}/#{file}", File.basename(fn).ext('o')) } 
end

OTHER_OBJS = OTHER_SRCS.collect {|fn| File.join("#{OBJDIR}/shared/#{file}", File.basename(fn).ext('o')) }

SO_LIBS = []
SO_SRCS.each_key {|file| SO_LIBS << "#{SODIR}/#{file}.so"}	
SO_SRCS.each_key {|dir| CLEAN.include("#{OBJDIR}/#{dir}")}
SO_OBJS.each_value {|list| CLEAN.include(list)}
CLEAN.include(OTHER_OBJS)
CLEAN.include("#{OBJDIR}/shared")
CLEAN.include(OBJDIR)

SO_LIBS.each {|so_file| CLOBBER.include(so_file)}
CLOBBER.include(SODIR)


# Sets the default task to build
task :default => [:build]

desc "Compiles and builds the library"
task :build
desc "Recompiles the library"
task :rebuild
desc "Installs the generated files"
task :install
desc "Uninstalls the generated files"
task :uninstall

task :clean do
    puts "Cleaning out temporary generated files"
end

task :clobber do
    puts "Cleaning out all generated files"
end

task :rebuild => [:clobber, :build] do
end

Rake::GemPackageTask.new(spec) do |pkg|
  pkg.need_tar_bz2 = true
end

RDoc::Task.new do |rd|
    rd.title = "RSFML #{RUBYSFML_VERSION} Documentation"
    rd.rdoc_files.include(SO_SRCS.values)
    rd.options << '--line-numbers' << '--quiet' << '--all'
    rd.rdoc_dir = "doc"
end

CFLAGS = CONFIG['CFLAGS']
CC = CONFIG['CC']
# CONFIG['INSTALL_PROGRAM']
INSTALL = "install"
LOCATION = CONFIG['sitearchdir'] + '/sfml'

RUBYSFML_INC = "shared"
SFML_INC = ENV.key?('SFML_INCLUDE') ? ENV['SFML_INCLUDE'] : File.dirname(__FILE__)
SFML_LIB = ENV.key?('SFML_LIB') ? ENV['SFML_LIB'] : File.dirname(__FILE__)
SFML_LIBS = '-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system'
RUBY_INC = CONFIG['rubyhdrdir']
RUBY_LIB = (CONFIG['ENABLE_SHARED'] == 'yes' ? CONFIG['LIBRUBYARG_SHARED'] : CONFIG['LIBRUBYARG_STATIC']) + ' ' + CONFIG['SOLIBS']
RUBY_LIB_PATH = CONFIG['libdir']
LINK = CONFIG['LDSHAREDXX']
# Windows screws up this variable...
LINK.sub!("$(if $(filter-out -g -g0,#{CONFIG["debugflags"]}),,-s)", '')
LINK_FLAGS = CONFIG['DLDFLAGS'] + " " + CONFIG['LDFLAGS']
LINK_FLAGS.sub!("$(DEFFILE)", "")

SO_SRCS.each_key {|dir| directory "#{OBJDIR}/#{dir}"}
directory "#{OBJDIR}/shared"
directory SODIR
directory LOCATION

OTHER_SRCS.each do |srcfile|
    objdir = "#{OBJDIR}/shared"
    objfile = File.join(objdir, File.basename(srcfile).ext('o'))
    file objfile => [srcfile, objdir] do
        puts "Compiling #{File.basename(srcfile)}"
        sh "#{CC} #{CFLAGS} -c #{srcfile} -o #{objfile} -I#{SFML_INC} -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']} -I#{RUBYSFML_INC}"
    end
end

task :shared => OTHER_OBJS
    
SO_SRCS.each do |so_file, list|
    begin
        list.each do |srcfile|
            objdir = "#{OBJDIR}/#{so_file}"
            objfile = File.join(objdir, File.basename(srcfile).ext('o'))
            file objfile => [srcfile, objdir] do
                puts "Compiling #{File.basename(srcfile)}"
                sh "#{CC} #{CFLAGS} -c #{srcfile} -o #{objfile} -I#{SFML_INC} -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']} -I#{RUBYSFML_INC}"
                #p "#{CC} #{CFLAGS} -c #{srcfile} -o #{objfile} -I#{SFML_INC} -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']} -I#{RUBYSFML_INC}"
            end
        end
    rescue
    end
end

SO_OBJS.each do |so_file, objs|
    begin
        prestep = "pre#{so_file}".to_sym
        task prestep do
            puts "Creating #{so_file}.so"
        end
        file "#{SODIR}/#{so_file}.so" => [prestep, :shared, SODIR, *objs] do
            puts "Linking files to create #{so_file}.so"
            #p "#{LINK} -o #{SODIR}/#{so_file}.so #{objs} -L. -L#{SFML_LIB} -L#{RUBY_LIB_PATH} #{LINK_FLAGS} #{RUBY_LIB} #{SFML_LIBS}"
            sh "#{LINK} -o #{SODIR}/#{so_file}.so #{objs} #{OTHER_OBJS} -L. -L#{SFML_LIB} -L#{RUBY_LIB_PATH} #{LINK_FLAGS} #{RUBY_LIB} #{SFML_LIBS}"
        end
    rescue
    end
end

task :install => [:build, LOCATION] do
    puts "Installing library to #{LOCATION}"
    begin
        SO_SRCS.each_key do |so_file|
            sh "#{INSTALL} #{SODIR}/#{so_file}.so #{LOCATION}"
        end
    rescue Exception=>e
	p e
    end
end

task :uninstall do
    puts "Uninstalling library to #{LOCATION}"
    begin
        SO_SRCS.each_key do |so_file|
            sh "rm -f #{LOCATION}/#{so_file}.so"
        end
        sh "rm -rf #{LOCATION}"
    rescue
    end
end
        
task :build => [:shared, *SO_LIBS] do
end
