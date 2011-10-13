require 'rake'
require 'rake/clean'
require 'rbconfig'
require 'digest/md5'
include Config

CFLAGS = CONFIG['CFLAGS']
CC = CONFIG['CC']

SFML_INC = ENV['SFML_INCLUDE'] || File.dirname(__FILE__) + '/include'
SFML_LIB = ENV['SFML_LIB'] || File.dirname(__FILE__) + '/lib'

RUBY_INC = CONFIG['rubyhdrdir']
RUBY_LIB = CONFIG['libdir']
RUBY_LINK = CONFIG['SOLIBS'] + (CONFIG['ENABLE_SHARED'] == 'yes' ? CONFIG['LIBRUBYARG_SHARED'] : CONFIG['LIBRUBYARG_STATIC'])

LINK = CONFIG['LDSHAREDXX']
# Windows screws up this variable...
LINK.sub!("$(if $(filter-out -g -g0,#{CONFIG["debugflags"]}),,-s)", '')
LINK_FLAGS = CONFIG['DLDFLAGS'] + " " + CONFIG['LDFLAGS']
LINK_FLAGS.sub!("$(DEFFILE)", "")

OBJ_DIR = 'obj'
SO_DIR = 'sfml'
DOC_DIR = 'doc'
INST_DIR = File.join(CONFIG['sitearchdir'], 'sfml')

SRCS = {:audio    => FileList.new('sfml-audio/audio/*.cpp'),
        :graphics => FileList.new('sfml-graphics/graphics/*.cpp'),
        :window   => FileList.new('sfml-window/window/*.cpp'),
        :system   => FileList.new('sfml-system/system/*.cpp'),
        :all      => FileList.new('sfml-all/all/*.cpp'),
        :sfml     => FileList.new('sfml-sfml/sfml/*.cpp'),
        :shared   => FileList.new('shared/*.cpp')}
LIBS = []
OBJS = {}
SRCS.each_key {|file| LIBS << "#{SO_DIR}/#{file}.so"}

CLEAN.include(OBJ_DIR)
CLOBBER.include(SO_DIR)
CLOBBER.include(DOC_DIR)

def calc_md5
  return if OBJS.size > 0
  puts "Calculating MD5 checksum"
  SRCS.each do |k, list|
    OBJS[k] = []
    list.each do |file|
      code = File.read(file)
      digest = Digest::MD5.hexdigest(code)
      s = ".s" if ARGV.include? "static"
      OBJS[k] << File.join("#{OBJ_DIR}/#{k}", "#{File.basename(file)}.#{digest}#{s}.o")
    end
  end
  OBJS[:sfml] += OBJS[:audio] + OBJS[:graphics] + OBJS[:window] + OBJS[:system]
end

def compile_o(src)
  calc_md5
  list = SRCS[src]
  dir = "#{OBJ_DIR}/#{src}"
  mkdir_p dir
  s = ARGV.include?("static") ? "-DSFML_STATIC" : ""
  c = ARGV.include?("sfml") ? "-DSFML_RUBYEXT_SFML" : ""
  unless File.exist?(SFML_INC)
    raise RuntimeError, "Unable to find SFML include files at '#{SFML_INC}'"
  end
  list.each_with_index do |file, i|
    obj = OBJS[src][i]
    next if File.exist?(obj)
    puts "Compiling #{src}/#{File.basename(file)}"
    exit unless system "#{CC} #{CFLAGS} -c #{file} -o #{obj} #{s} #{c} -I#{SFML_INC} -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']} -Ishared"
  end
end

def create_so(src)
  file = "#{SO_DIR}/#{src}.so"
  mkdir_p SO_DIR
  puts "Creating #{src}.so"
  objs = OBJS[src]
  s = (ARGV.include?("static") ? "-s" : "")
  unless File.exist?(SFML_LIB)
    raise RuntimeError, "Unable to find SFML lib files at '#{SFML_LIB}'"
  end
  sfml = case src
  when :audio;    "-lsfml-audio#{s} -lsfml-system#{s}"
  when :graphics; "-lsfml-graphics#{s} -lsfml-window#{s} -lsfml-system#{s}"
  when :window;   "-lsfml-window#{s} -lsfml-system#{s}"
  when :system;   "-lsfml-system#{s}"
  when :sfml;     "-lsfml-audio#{s} -lsfml-graphics#{s} -lsfml-window#{s} -lsfml-system#{s}"
  end
  exit unless system "#{LINK} -o #{file} #{objs.join(' ')} #{OBJS[:shared].join(' ')} -L. -L#{SFML_LIB} -L#{RUBY_LIB} #{LINK_FLAGS} #{RUBY_LINK} #{sfml}"
end

task :default => [:all]

desc "Link statically against SFML."
task :static do
  if ARGV == ["static"]
    ARGV << "sfml"
    Rake::Task["sfml"].invoke
  end
end

desc "Build the whole rbSFML."
task :all => [:audio, :graphics, :window, :system] do
  compile_o(:all)
  create_so(:all)
end

desc "Build only audio module (audio.so)."
task :audio do
  compile_o(:shared)
  compile_o(:audio)
  create_so(:audio)
end

desc "Build only graphics module (graphics.so)."
task :graphics do
  compile_o(:shared)
  compile_o(:graphics)
  create_so(:graphics)
end

desc "Build only window module (window.so)."
task :window do
  compile_o(:shared)
  compile_o(:window)
  create_so(:window)
end

desc "Build only system module (system.so)."
task :system do
  compile_o(:shared)
  compile_o(:system)
  create_so(:system)
end

desc "Build rbSFML as a single file (sfml.so)."
task :sfml do
  compile_o(:shared)
  compile_o(:system)
  compile_o(:window)
  compile_o(:graphics)
  compile_o(:audio)
  compile_o(:sfml)
  create_so(:sfml)
end

desc "Build and open documentation."
task :doc

if ARGV.include? 'doc'
  require 'yard'
  YARD::Rake::YardocTask.new do |yard|
    yard.name = DOC_DIR
    yard.files = FileList.new('sfml-audio/doc/*.rb') +
                 FileList.new('sfml-graphics/doc/*.rb') +
                 FileList.new('sfml-window/doc/*.rb') +
                 FileList.new('sfml-system/doc/*.rb') +
                 FileList.new('shared/*.rb')
    yard.options << "--verbose" << "--no-save" << "--no-cache"
    at_exit do
      uri = "file:///#{File.dirname(__FILE__)}/#{DOC_DIR}/frames.html"
      case
      when RUBY_PLATFORM.downcase.include?("darwin") # MAC
        system "open #{uri}"
      when RUBY_PLATFORM.downcase.include?("mswin") ||
           RUBY_PLATFORM.downcase.include?("mingw")  # Windows
        system "start #{uri}"
      when RUBY_PLATFORM.downcase.include?("linux")  # Linux
        system "xdg-open #{uri}"
      else
        # WTF?
      end
    end
  end
end

desc "Install rbSFML."
task :install do
  mkdir_p SO_DIR
  list = FileList.new("#{SO_DIR}/*.so")
  if list.size == 0
    puts "Nothing to install."
  else
    mkdir_p INST_DIR
    puts "Installing library to #{INST_DIR}"
    list.each do |file|
      puts "Installing #{file}..."
      copy_file(file, File.join(INST_DIR, File.basename(file)))
    end
  end
end

desc "Uninstall rbSFML."
task :uninstall do
  if !File.exist?(INST_DIR)
    puts "Nothing to uninstall."
  else
    puts "Uninstalling library from #{INST_DIR}"
    remove_dir(INST_DIR, true)
  end
end

desc "Run tests."
task :test do
  load "test/test.rb"
end
