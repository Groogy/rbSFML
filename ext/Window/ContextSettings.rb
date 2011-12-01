module SFML
  
  # Structure defining the settings of the OpenGL context attached to a
  # window. <tt>ContextSettings</tt> allows to define several advanced
  # settings of the OpenGL context attached to a window. All these settings
  # have no impact on the regular SFML rendering (graphics module) -- except
  # the anti-aliasing level, so you may need to use this structure only if
  # you're using SFML as a windowing system for custom OpenGL rendering. The
  # <tt>depth_bits</tt> and <tt>stencil_bits</tt> attributes define the number
  # of bits per pixel requested for the (respectively) depth and stencil
  # buffers. <tt>antialiasing_level</tt> represents the requested number of
  # multisampling levels for anti-aliasing. <tt>major_version</tt> and
  # <tt>minor_version</tt> define the version of the OpenGL context that you
  # want. Only versions greater or equal to 3.0 are relevant; versions lesser
  # than 3.0 are all handled the same way (i.e. you can use any version < 3.0
  # if you don't want an OpenGL 3 context). Please note that these values are
  # only a hint. No failure will be reported if one or more of these values
  # are not supported by the system; instead, SFML will try to find the
  # closest valid match. You can then retrieve the settings that the window
  # actually used to create its context, with <tt>Window#settings</tt>.
  # You can represent a <tt>ContextSettings</tt> with a hash.
  # @example
  #   window = Window.new([640, 480], "rbSFML Window", Style::Default,
  #                       {depth_bits: 32, major_version: 3})
  class ContextSettings
    
    # Bits of the depth buffer.
    # @return [Fixnum]
    attr_accessor :depth_bits
    alias DepthBits depth_bits
    
    # Bits of the stencil buffer.
    # @return [Fixnum]
    attr_accessor :stencil_bits
    alias StencilBits stencil_bits
    
    # Level of antialiasing.
    # @return [Fixnum]
    attr_accessor :antialiasing_level
    alias AntialiasingLevel antialiasing_level
    
    # Major number of the context version to create.
    # @return [Fixnum]
    attr_accessor :major_version
    alias MajorVersion major_version
    
    # Minor number of the context version to create.
    # @return [Fixnum]
    attr_accessor :minor_version
    alias MinorVersion minor_version
    
    # Default constructor.
    # @param [Fixnum] depth Depth buffer bits
    # @param [Fixnum] stencil Stencil buffer bits
    # @param [Fixnum] antialiasing Antialiasing level
    # @param [Fixnum] major Major number of the context version
    # @param [Fixnum] minor Minor number of the context version
    def initialize(depth=0, stencil=0, antialiasing=0, major=2, minor=0)  
    end
    
    # This operator compares two context settings and checks if they are
    # equal.
    # @param [ContextSettings] other Context settings to be compared with.
    # @return [Boolean] <tt>true</tt> if they are equal, <tt>false</tt>
    def ==(other)
    end
    alias eql? ==
    alias equal? ==
    
    # Returns a formated string to represent the Context settings. 
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
