module SFML
  
  # Utility class for manipulating 2D axis aligned rectangles. A rectangle is defined by its top-left corner and its size.
  # 
  # It is a very simple class defined for convenience, so its instance variables (<tt>@left</tt>, <tt>@top</tt>, <tt>@width</tt> and <tt>@height</tt>) can be accessed directly, just like the vector classes (<tt>Vector2</tt> and <tt>Vector3</tt>).
  # 
  # To keep things simple, <tt>Rect</tt> doesn't define functions to emulate the properties that are not directly members (such as <tt>right</tt>, <tt>bottom</tt>, <tt>center</tt>, etc.), it rather only provides intersection functions.
  # Rect uses the usual rules for its boundaries: 
  # 
  # - The <tt>left</tt> and <tt>top</tt> edges are included in the rectangle's area 
  # - The <tt>right</tt> (<tt>left</tt> + <tt>width</tt>) and <tt>bottom</tt> (<tt>top</tt> + <tt>height</tt>) edges are excluded from the rectangle's area 
  # 
  # This means that <tt>Rect(0, 0, 1, 1)</tt> and <tt>Rect(1, 1, 1, 1)</tt> don't intersect.
  # 
  # @example  
  #   # Define a rectangle, located at (0, 0) with a size of 20x5
  #   r1 = Rect.new(0, 0, 20, 5)
  #   
  #   # Define another rectangle, located at (4, 2) with a size of 18x10
  #   position = Vector2.new(4, 2)
  #   size = Vector2.new(18, 10)
  #   r2 = Rect.new(position, size)
  #   
  #   # Test intersections with the point (3, 1)
  #   r1.contains?(3, 1) # => true
  #   r2.contains?(3, 1) # => false 
  #   
  #   # Test the intersection between r1 and r2
  #   !!r1.intersects(r2) # => true
  #   r1.intersects(r2)   # => Rect(4, 2, 16, 3)
  class Rect
  
    # @return [Fixnum, Float]
    attr_accessor :left
    alias Left left
    
    # @return [Fixnum, Float]
    attr_accessor :top
    alias Top top
    
    # @return [Fixnum, Float]
    attr_accessor :width
    alias Width width
    
    # @return [Fixnum, Float]
    attr_accessor :height
    alias Height height
    
    # @overload initialize()
    #   Creates an empty rectangle (it is equivalent to calling <tt>Rect(0, 0, 0, 0)</tt>).
    # @overload initialize(rect)
    #   Constructs the rectangle from another rectangle, with the same coordinates.
    #   @param [Rect] rect Another rectangle
    # @overload initialize(ary)
    #   Constructs the rectangle from a array.
    #   @param [Array] ary Array in the format <tt>[left, top, width, height]</tt>
    # @overload initialize(left, top, width, height)
    #   Constructs the rectangle from its coordinates. Be careful, the last two parameters are the <tt>width</tt> and <tt>height</tt>, not the <tt>right</tt> and <tt>bottom</tt> coordinates!
    #   @param [Numeric] left Left coordinate of the rectangle
    #   @param [Numeric] top Top coordinate of the rectangle
    #   @param [Numeric] width Width of the rectangle
    #   @param [Numeric] height Height of the rectangle
    # @overload initialize(position, size)
    #   Constructs the rectangle from position and size. Be careful, the last parameter is the size, not the bottom-right corner!
    #   @param [Vector2] position Position of the top-left corner of the rectangle
    #   @param [Vector2] size Size of the rectangle
    def initialize
    end
    
    # Checks if a point is inside the rectangle's area.
    # @return [Boolean] <tt>true</tt> if the point is inside, <tt>false</tt> otherwise
    # @overload contains?(point)
    #   @param [Vector2] point Point to test
    # @overload contains?(x, y)
    #   @param [Numeric] x X coordinate of the point to test
    #   @param [Numeric] y Y coordinate of the point to test
    def contains?
    end
    alias Contains contains?
    alias contains contains?
    alias include? contains?
    
    # Checks the intersection between two rectangles. 
    # @return [Rect, NilClass] The overlapped rectangle if they intersects, <tt>nil</tt> otherwise
    # @overload intersects(rect)
    #   @param [Rect] rect Another rectangle
    # @overload intersects(ary)
    #   @param [Array] ary Array in the format <tt>[left, top, width, height]</tt>
    def intersects
    end
    alias Intersects intersects
    
    # Returns a formated string to represent the rectangle. 
    # @return [String] <tt>Rect(left, top, width, height)</tt>
    def inspect
    end
	alias to_s inspect
	alias to_str inspect
    
  end
  
end