require 'rake'
require 'rake/clean'
require 'rbconfig'
require 'digest/md5'
require 'fileutils'
include RbConfig
include FileUtils

module FileUtils
  def fu_output_message(msg)
    puts msg if $verbose
  end
end

RakeFileUtils.verbose_flag = false

OBJ_DIR = 'obj'
SO_DIR = 'sfml'
DOC_DIR = 'doc'
EXT_DIR = 'ext'
INST_DIR = File.join(CONFIG['sitearchdir'], SO_DIR)

SFML_INC = ENV['SFML_INCLUDE'] || "include"
SFML_LIB = ENV['SFML_LIB'] || "lib"

RUBY_INC = CONFIG['rubyhdrdir']
RUBY_LIB = CONFIG['libdir']
RUBY_LINK = CONFIG['SOLIBS'] + (CONFIG['ENABLE_SHARED'] == 'yes' ? CONFIG['LIBRUBYARG_SHARED'] : CONFIG['LIBRUBYARG_STATIC'])

CXX = CONFIG['CXX']
CXXFLAGS = "#{CONFIG['CXXFLAGS']} -I#{SFML_INC} -I#{EXT_DIR} -I#{RUBY_INC} -I#{RUBY_INC}/#{CONFIG['arch']}"

LINK = CONFIG['LDSHAREDXX'].sub("$(if $(filter-out -g -g0,#{CONFIG['debugflags']}),,-s)", "")
LINK_FLAGS = "#{CONFIG['DLDFLAGS']} #{CONFIG['LDFLAGS']} -L#{SFML_LIB} -L#{RUBY_LIB} #{RUBY_LINK}".sub("$(DEFFILE)", "")

SRCS = {:audio    => FileList.new("#{EXT_DIR}/Audio/*.cpp"),
        :graphics => FileList.new("#{EXT_DIR}/Graphics/*.cpp"),
        :window   => FileList.new("#{EXT_DIR}/Window/*.cpp"),
        :system   => FileList.new("#{EXT_DIR}/System/*.cpp"),
        :all      => FileList.new("#{EXT_DIR}/all.cpp"),
        :sfml     => FileList.new("#{EXT_DIR}/sfml.cpp")}

SHARED = ["#{EXT_DIR}/InputStream.cpp"]

LIBS = []
OBJS = {}
SRCS.each_key {|file| LIBS << "#{SO_DIR}/#{file}.#{CONFIG['DLEXT']}"}

CLEAN.include(OBJ_DIR)
CLOBBER.include(SO_DIR)
CLOBBER.include(DOC_DIR)

desc "Turn on verbose mode."
task :verbose do
  $verbose = true
  CXXFLAGS << " -Wall -Wextra "
  puts RUBY_DESCRIPTION
  puts ""
  puts "OBJ_DIR    = #{OBJ_DIR.inspect}"
  puts "SO_DIR     = #{SO_DIR.inspect}"
  puts "DOC_DIR    = #{DOC_DIR.inspect}"
  puts "EXT_DIR    = #{EXT_DIR.inspect}"
  puts "INST_DIR   = #{INST_DIR.inspect} (#{"not " unless File.exist?(INST_DIR)}found)"
  puts ""
  puts "SFML_INC   = #{SFML_INC.inspect} (#{"not " unless File.exist?(SFML_INC)}found)"
  puts "SFML_LIB   = #{SFML_LIB.inspect} (#{"not " unless File.exist?(SFML_LIB)}found)"
  puts ""
  puts "RUBY_INC   = #{RUBY_INC.inspect} (#{"not " unless File.exist?(RUBY_INC)}found)"
  puts "RUBY_LIB   = #{RUBY_LIB.inspect} (#{"not " unless File.exist?(RUBY_LIB)}found)"
  puts "RUBY_LINK  = #{RUBY_LINK.inspect}"
  puts ""
  puts "CXX        = #{CXX.inspect}"
  puts "CXXFLAGS   = #{CXXFLAGS.inspect}"
  puts ""
  puts "LINK       = #{LINK.inspect}"
  puts "LINK_FLAGS = #{LINK_FLAGS.inspect}"
  puts ""
end

def calc_md5(src)
  list = SRCS[src]
  OBJS[src] = []
  list.each do |file|
    code = File.read(file)
    digest = Digest::MD5.hexdigest(code)
    s = ".s" if ARGV.include? "static"
    OBJS[src] << "#{OBJ_DIR}/#{File.basename(file)}.#{digest}#{s}.o"
  end
  if src == :sfml
    OBJS[:sfml] += OBJS[:audio] + OBJS[:graphics] + OBJS[:window] + OBJS[:system]
  end
end

def compile_o(src)
  unless File.exist?(SFML_INC)
    raise RuntimeError, "Unable to find SFML include files at '#{SFML_INC}'"
  end
  calc_md5(src)
  mkdir_p OBJ_DIR
  defines = []
  defines << "SFML_STATIC" if ARGV.include? "static"
  if ARGV.include? "sfml"
    defines << "RBSFML_SYSTEM"
    defines << "RBSFML_WINDOW"
    defines << "RBSFML_GRAPHICS"
    defines << "RBSFML_AUDIO"
    defines << "RBSFML_SFML"
  else
    defines << "RBSFML_#{src.to_s.upcase}"
  end
  d = defines.map{|m|"-D#{m}"}.join(" ")
  SRCS[src].each_with_index do |file, i|
    obj = OBJS[src][i]
    next if File.exist?(obj)
    puts "Compiling #{file}"
    sh "#{CXX} #{CXXFLAGS} -c #{file} -o #{obj} #{d}"
  end
end

def create_so(src)
  unless File.exist?(SFML_LIB)
    raise RuntimeError, "Unable to find SFML lib files at '#{SFML_LIB}'"
  end
  so = "#{SO_DIR}/#{src}.#{CONFIG['DLEXT']}"
  mkdir_p SO_DIR
  puts "Creating #{so}"
  objs = OBJS[src].join(" ")
  s = "-s" if ARGV.include? "static"
  sfml_link = case src
  when :audio;    "-lsfml-audio#{s} -lsfml-system#{s}"
  when :graphics; "-lsfml-graphics#{s} -lsfml-window#{s} -lsfml-system#{s}"
  when :window;   "-lsfml-window#{s} -lsfml-system#{s}"
  when :system;   "-lsfml-system#{s}"
  when :sfml;     "-lsfml-audio#{s} -lsfml-graphics#{s} -lsfml-window#{s} -lsfml-system#{s}"
  end
  sh "#{LINK} #{objs} -o #{so} #{LINK_FLAGS} #{sfml_link}"
end

task :default => [:all]

desc "Link statically against SFML."
task :static do
  unless ARGV.any? {|arg| ["system", "window", "graphics", "audio", "all"].include? arg }
    ARGV << "sfml"
    Rake::Task["sfml"].invoke
  end
end

desc "Build all modules."
task :all => [:system, :window, :graphics, :audio] do
  compile_o(:all)
  create_so(:all)
end

desc "Build audio module (audio.#{CONFIG['DLEXT']})."
task :audio => [:system] do
  SRCS[:audio] += SHARED
  compile_o(:audio)
  create_so(:audio)
end

desc "Build graphics module (graphics.#{CONFIG['DLEXT']})."
task :graphics => [:system, :window] do
  SRCS[:graphics] += SHARED
  compile_o(:graphics)
  create_so(:graphics)
end

desc "Build window module (window.#{CONFIG['DLEXT']})."
task :window => [:system] do
  SRCS[:window] += SHARED
  compile_o(:window)
  create_so(:window)
end

desc "Build system module (system.#{CONFIG['DLEXT']})."
task :system do
  SRCS[:system] += SHARED
  compile_o(:system)
  create_so(:system)
end

desc "Build all modules as a single file (sfml.#{CONFIG['DLEXT']})."
task :sfml do
  SRCS[:sfml] += SHARED
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
  # TODO: Find a way to remove '[View source]' from docs.
  YARD::Rake::YardocTask.new do |yard|
    yard.name = DOC_DIR
    yard.files = FileList.new("ext/**/*.rb")
    yard.options << "--no-save" << "--no-cache"
    at_exit do
      uri = "file:///\"#{File.dirname(__FILE__)}/#{DOC_DIR}\"/frames.html"
      case RUBY_PLATFORM
      when /darwin|mac os/i          # Mac OS
        system "open #{uri}" # TODO: It works?
      when /mingw|mswin|windows/i    # Windows
        system "start /b #{uri}"
      when /cygwin/i                 # Cygwin
        system "cmd /C start /b #{uri}"
      when /linux|bsd|aix|solaris/i  # Linux
        system "xdg-open #{uri}" # TODO: It works?
      end
    end
  end
end

desc "Install rbSFML."
task :install => [:uninstall] do
  mkdir_p SO_DIR
  list = FileList.new("#{SO_DIR}/*.#{CONFIG['DLEXT']}")
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
  ARGV.replace []
  if $verbose
    ARGV << "-v"
  end
  
  load "test/test.rb"
end

desc "Run samples."
task :samples do
  cd "samples"
  Dir.entries(".").select{|e| e =~ /\.rb$/ }.each do |sample|
    ruby("#{sample}", verbose: true) { }
  end
end
