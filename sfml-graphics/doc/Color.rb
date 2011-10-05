module SFML
  
  # Utility class for manpulating RGBA colors. <tt>Color</tt> is a simple color class composed of 4 components:
  #
  # - Red
  # - Green
  # - Blue
  # - Alpha (opacity)
  #
  # Each component is a public attribute in the range <tt>[0, 255]</tt>. Thus, colors can be constructed and manipulated very easily.
  #
  # The fourth component of colors, named "alpha", represents the opacity of the color. A color with an alpha value of <tt>255</tt> will be fully opaque, while an alpha value of <tt>0</tt> will make a color fully transparent, whatever the value of the other components.
  #
  # The most common colors are already defined as constants: 
  #
  # - <tt>Color::Black</tt>
  # - <tt>Color::White</tt>
  # - <tt>Color::Red</tt>	
  # - <tt>Color::Green</tt>
  # - <tt>Color::Blue</tt>
  # - <tt>Color::Yellow</tt>
  # - <tt>Color::Magenta</tt>
  # - <tt>Color::Cyan</tt>
  #
  # Colors can also be added and modulated (multiplied) using the operators <tt>+</tt> and <tt>*</tt>. 
  # 
  # A array whose arguments fits on <tt>Color.new()</tt> can be used as argument anywhere a color is requested.
  # 
  # @example
  #   c1 = Color.new(255, 0, 0) # red
  #   c1.red = 0                # make it black
  #   c1.blue = 128             # make it dark blue
  class Color
    
    # @return [Fixnum]
    attr_accessor :r
    alias red r
    
    # @return [Fixnum]
    attr_accessor :g
    alias green g
    
    # @return [Fixnum]
    attr_accessor :b
    alias blue b
    
    # @return [Fixnum]
    attr_accessor :a
    alias alpha a
    
    # @overload initialize()
    #   Constructs an opaque black color. It is equivalent to <tt>Color.new(0, 0, 0, 255)</tt>.
    # @overload initialize(color)
    #   Constructs the color from another color, with the same components.
    #   @param [Color] color Another color
    # @overload initialize(red, green, blue, alpha=255)
    #   Constructs the color from its 4 RGBA components.
    #   @param [Numeric] red Red component (in the range <tt>[0, 255]</tt>)
    #   @param [Numeric] green Green component (in the range <tt>[0, 255]</tt>)
    #   @param [Numeric] blue Blue component (in the range <tt>[0, 255]</tt>)
    #   @param [Numeric] alpha Alpha (opacity) component (in the range <tt>[0, 255]</tt>, default is <tt>255</tt>)
    def initialize
    end
    
    # @overload +(other)
    #  This operator returns the component-wise sum of two colors. Components that exceed 255 are clamped to 255.
    #  @param [Color] other The right operand
    #   @return [Color]
    def +
    end
    
    # @overload *(other)
    #   This operator returns the component-wise multiplication (also called "modulation") of two colors. Components are then divided by 255 so that the result is still in the range <tt>[0, 255]</tt>.
    #   @param [Color] other The right operand
    #   @return [Color]
    def *
    end
    
    # @overload ==(other)
    #   This operator compares two colors and check if they are equal.
    #   @param [Color] other The right operand
    #   @return [Color]
    def ==
    end
    
    # Returns a formated string to represent the color. 
    # @return [String] <tt>Color(red, green, blue, alpha)</tt>
    def inspect
    end
    alias to_s inspect
    
    # Black predefined color. 
    Black = Color.new(0, 0, 0)
    
    # White predefined color. 
    White = Color.new(255, 255, 255)
    
    # Red predefined color. 
    Red = Color.new(255, 0, 0)
    
    # Green predefined color. 
    Green = Color.new(0, 255, 0)
    
    # Blue predefined color. 
    Blue = Color.new(0, 0, 255)
    
    # Yellow predefined color. 
    Yellow = Color.new(255, 255, 0)
    
    # Magenta predefined color. 
    Magenta = Color.new(255, 0, 255)
    
    # Cyan predefined color. 
    Cyan = Color.new(0, 255, 255)
    
  end
  
end