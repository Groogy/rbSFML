module SFML
  
  # <tt>VideoMode</tt> defines a video mode (<tt>width</tt>, <tt>height</tt>,
  # <tt>bpp</tt>) 
  #
  # A video mode is defined by a width and a height (in pixels) and a depth
  # (in bits per pixel).
  #
  # Video modes are used to setup windows (<tt>Window</tt>) at creation time.
  #
  # The main usage of video modes is for fullscreen mode: indeed you must use
  # one of the valid video modes allowed by the OS (which are defined by what
  # the monitor and the graphics card support), otherwise your window creation
  # will just fail.
  #
  # <tt>VideoMode</tt> provides a class method for retrieving the list of all
  # the video modes supported by the system: <tt>fullscreen_modes</tt>.
  #
  # A custom video mode can also be checked directly for fullscreen
  # compatibility with its <tt>valid?</tt> method.
  #
  # Additionnally, <tt>VideoMode</tt> provides a class method to get the mode
  # currently used by the desktop: <tt>desktop_mode</tt>. This allows to build
  # windows with the same size or pixel depth as the current resolution.
  # 
  # A array whose arguments fits on <tt>VideoMode.new()</tt> can be used as
  # argument anywhere a video mode is requested.
  #
  # @example
  #   # Display the list of all the video modes available for fullscreen
  #   modes = VideoMode.fullscreen_modes
  #   modes.each do |mode|
  #     p mode
  #   end
  #
  #   # Create a window with the same pixel depth as the desktop
  #   desktop = VideoMode.desktop_mode
  #   window.create([1024, 768, desktop.bpp], "SFML window")
  class VideoMode
    include Comparable
    
    class << self
      
      # Gets the current desktop video mode. 
      # @return [VideoMode] Current desktop video mode 
      def desktop_mode
      end
      alias GetDesktopMode desktop_mode
      
      # Retrieves all the video modes supported in fullscreen mode. When
      # creating a fullscreen window, the video mode is restricted to be
      # compatible with what the graphics driver and monitor support. This
      # function returns the complete list of all video modes that can be used
      # in fullscreen mode. The returned array is sorted from best to worst,
      # so that the first element will always give the best mode (higher
      # width, height and bits-per-pixel).
      # @return [Array] Array containing all the supported fullscreen modes 
      def fullscreen_modes
      end
      alias GetFullscreenModes fullscreen_modes
      
    end
    
    # @return [Fixnum]
    attr_accessor :width
    alias Width width
    
    # @return [Fixnum]
    attr_accessor :height
    alias Height height
    
    # @return [Fixnum]
    attr_accessor :bpp
    alias BitsPerPixel bpp
    alias bitsPerPixel bpp
    alias bits_per_pixel bpp
    alias bits bpp
    
    # @overload initialize()
    #   Creates a <tt>VideoMode(0, 0, 0)</tt>.
    # @overload initialize(video_mode)
    #   Constructs the video mode from another video mode, with the same
    #   attributes.
    #   @param [VideoMode] video_mode Another video mode
    # @overload initialize(width, height, bpp = 32)
    #   Constructs the video mode from its coordinates.
    #   @param [Fixnum] width Width in pixels
    #   @param [Fixnum] height Height in pixels
    #   @param [Fixnum] bpp Pixel depths in bits per pixel
    def initialize
    end
    
    # Tells whether or not the video mode is valid. The validity of video
    # modes is only relevant when using fullscreen windows; otherwise any
    # video mode can be used with no restriction.
    # @return [Boolean]<tt>true</tt> if the video mode is valid for fullscreen
    #   mode, <tt>false</tt>
    def valid?
    end
    alias IsValid valid?
    
    # Compares the video mode with another one.
    # @param [VideoMode] other Video mode to be compared with.
    # @return [Boolean] <tt>0</tt> if they are equal, <tt>1</tt> if the
    #   argument is greater, <tt>-1</tt> otherwise
    def <=>(other)
    end
    
    # Same as <tt>==</tt>
    # @return [Boolean] <tt>true</tt> if they are equal, <tt>false</tt>
    def eql?
    end
    alias eql? ==
    alias equal? ==
    
    # Returns a formated string to represent the video mode.
    # @return [String]
    def inspect
    end
    alias to_s inspect
    
    # Returns how much memory was allocated by this object.
    # @return [Fixnum]
    def memory_usage
    end
    
  end
  
end
