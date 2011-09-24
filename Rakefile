require 'rake'
require 'rake/clean'
require 'rbconfig'
require 'digest/md5'
include Config

CFLAGS = CONFIG['CFLAGS']
CC = CONFIG['CC']
INSTALL = "install"
INST_DIR = File.join(CONFIG['sitearchdir'], 'sfml')
SFML_INC = ENV.key?('SFML_INCLUDE') ? ENV['SFML_INCLUDE'] : File.dirname(__FILE__) + '/includes'
SFML_LIB = ENV.key?('SFML_LIB') ? ENV['SFML_LIB'] : File.dirname(__FILE__) + '/libs'
RUBY_INC = CONFIG['rubyhdrdir']
RUBY_LIB = CONFIG['libdir']
RUBY_LINK = CONFIG['SOLIBS'] + (CONFIG['ENABLE_SHARED'] == 'yes' ? CONFIG['LIBRUBYARG_SHARED'] : CONFIG['LIBRUBYARG_STATIC'])
LINK = CONFIG['LDSHAREDXX']
# Windows screws up this variable...
LINK.sub!("$(if $(filter-out -g -g0,#{CONFIG["debugflags"]}),,-s)", '')
LINK_FLAGS = CONFIG['DLDFLAGS'] + " " + CONFIG['LDFLAGS']
LINK_FLAGS.sub!("$(DEFFILE)", "")
SRCS = {:audio    => FileList.new('sfml-audio/audio/*.cpp'),
        :graphics => FileList.new('sfml-graphics/graphics/*.cpp'),
        :window   => FileList.new('sfml-window/window/*.cpp'),
        :system   => FileList.new('sfml-system/system/*.cpp'),
        :all      => FileList.new('sfml-all/all/*.cpp'),
        :sfml     => FileList.new('sfml-sfml/sfml/*.cpp'),
        :shared   => FileList.new('shared/*.cpp')}
OBJ_DIR = 'obj'
SO_DIR = 'sfml'
LIBS = []
OBJS = {}
SRCS.each_key {|file| LIBS << "#{SO_DIR}/#{file}.so"}
CLEAN.include(OBJ_DIR)
CLOBBER.include(SO_DIR)

def calc_md5
  return if OBJS.size > 0
  puts "Calculating MD5 checksum..."
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

def create_obj(src)
  calc_md5
  list = SRCS[src]
  dir = "#{OBJ_DIR}/#{src}"
  mkdir_p OBJ_DIR if !File.exist?(OBJ_DIR)
  mkdir_p dir if !File.exist?(dir)
  s = ARGV.include?("static") ? "-DSFML_STATIC" : ""
  c = ARGV.include?("sfml") ? "-DSFML_RUBYEXT_SFML" : ""
  list.each_with_index do |file, i|
    obj = OBJS[src][i]
    next if File.exist?(obj)
    puts "Compiling #{src}/#{File.basename(file)}"
    system "#{CC} #{CFLAGS} -c #{file} -o #{obj} #{s} #{c} -I#{SFML_INC} -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']} -Ishared"
  end
end

def create_so(src)
  file = "#{SO_DIR}/#{src}.so"
  mkdir_p SO_DIR if !File.exist?(SO_DIR)
  puts "Creating #{src}.so"
  objs = OBJS[src]
  s = (ARGV.include?("static") ? "-s" : "")
  sfml = case src
  when :audio;    "-lsfml-audio#{s} -lsfml-system#{s}"
  when :graphics; "-lsfml-graphics#{s} -lsfml-window#{s} -lsfml-system#{s}"
  when :window;   "-lsfml-window#{s} -lsfml-system#{s}"
  when :system;   "-lsfml-system#{s}"
  when :sfml;     "-lsfml-audio#{s} -lsfml-graphics#{s} -lsfml-window#{s} -lsfml-system#{s}"
  end
  system "#{LINK} -o #{file} #{objs.join(' ')} #{OBJS[:shared].join(' ')} -L. -L#{SFML_LIB} -L#{RUBY_LIB} #{LINK_FLAGS} #{RUBY_LINK} #{sfml}"
end

task :default => [:all]

task :static do
  if ARGV == ["static"]
    ARGV << "sfml"
	Rake::Task["sfml"].invoke
  end
end

task :all => [:audio, :graphics, :window, :system] do
  create_obj(:all)
  create_so(:all)
end

task :audio do
  create_obj(:shared)
  create_obj(:audio)
  create_so(:audio)
end

task :graphics do
  create_obj(:shared)
  create_obj(:graphics)
  create_so(:graphics)
end

task :window do
  create_obj(:shared)
  create_obj(:window)
  create_so(:window)
end

task :system do
  create_obj(:shared)
  create_obj(:system)
  create_so(:system)
end

task :sfml do
  create_obj(:shared)
  create_obj(:system)
  create_obj(:window)
  create_obj(:graphics)
  create_obj(:audio)
  create_obj(:sfml)
  create_so(:sfml)
end

if ARGV.include? 'doc'
  require 'yard'
  YARD::Rake::YardocTask.new do |yard|
    yard.name = 'doc'
    yard.files = FileList.new('sfml-audio/doc/*.rb') +
                 FileList.new('sfml-graphics/doc/*.rb') +
                 FileList.new('sfml-window/doc/*.rb') +
                 FileList.new('sfml-system/doc/*.rb') +
                 FileList.new('shared/*.rb')
  end
end

task :install do
  mkdir_p SO_DIR if !File.exist?(SO_DIR)
  list = FileList.new(SO_DIR + "/*.so")
  if list.size == 0
    puts "Nothing to install."
  else
    mkdir_p INST_DIR if !File.exist?(INST_DIR)
    puts "Installing library to #{INST_DIR}"
    list.each do |file|
      puts "Installing #{file}..."
      system "#{INSTALL} #{file} #{INST_DIR}"
    end
  end
end

task :uninstall do
  if !File.exist?(INST_DIR)
    puts "Nothing to uninstall."
  else
    puts "Uninstalling library from #{INST_DIR}"
    system "rm -rf #{INST_DIR}"
  end
end

task :test do
  load( "test/test.rb" )
end
