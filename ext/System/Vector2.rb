module SFML
  
  # <tt>Vector2</tt> is a simple class that defines a mathematical vector with
  # two coordinates (<tt>x</tt> and <tt>y</tt>).
  # 
  # It can be used to represent anything that has two dimensions: a size, a
  # point, a velocity, etc.
  # The coordinates can be any type that supports arithmetic operations
  # (<tt>+</tt>, <tt>-</tt>, <tt>/</tt>, <tt>*</tt>) and comparisons
  # (<tt>==</tt>, <tt>!=</tt>), for example <tt>Integer</tt> or <tt>Float</tt>
  # (anything that inherits from <tt>Numeric</tt>).
  # 
  # The <tt>Vector2</tt> class has a small and simple interface, its
  # <tt>x</tt> and <tt>y</tt> attributes can be accessed directly and it
  # contains no mathematical function like dot product, cross product, length,
  # etc.
  # 
  # A array whose arguments fits on <tt>Vector2.new()</tt> or a single numeric
  # value can be used as argument anywhere a vector2 is requested.
  # 
  # @note for 3-dimensional vectors, see <tt>Vector3</tt>. 
  #
  # @example
  #   v1 = Vector2.new(16.5, 24)
  #   v1.x = 18.2
  #   y = v1.y
  #   v2 = v1 * 5
  #   v3 = v1 + v2
  class Vector2
    
    # @return [Fixnum, Float]
    attr_accessor :x
    alias X x
    
    # @return [Fixnum, Float]
    attr_accessor :y
    alias Y y
    
    # @overload initialize()
    #   Creates a <tt>Vector(0, 0)</tt>.
    # @overload initialize(vector2)
    #   Constructs the vector from another vector, with the same attributes.
    #   @param [Vector2] vector2 Another vector
    # @overload initialize(num)
    #   Creates a <tt>Vector(num, num)</tt>.
    #   @param [Numeric] num A numeric value
    # @overload initialize(x, y)
    #   Constructs the vector from its coordinates.
    #   @param [Numeric] x X coordinate of the vector
    #   @param [Numeric] y Y coordinate of the vector
    def initialize
    end
    
    # Calcs the opposite.
    # @return [Vector2]
    def -@
    end
    
    # Calcs the memberwise addition.
    # @param [Vector2] other The right operand
    # @return [Vector2]
    def +(other)
    end
    
    # Calcs the memberwise subtraction.
    # @param [Vector2] other The right operand
    # @return [Vector2]
    def -(other)
    end
    
    # Calcs the memberwise multiplication.
    # @param [Vector2] other The right operand
    # @return [Vector2]
    def *(other)
    end
    
    # Calcs the memberwise division.
    # @param [Vector2] other The right operand
    # @return [Vector2]
    def /(other)
    end
    
    # Compares the vector with another one.
    # @param [Vector2] other Vector to be compared with.
    # @return [Boolean] <tt>true</tt> if they are equal, <tt>false</tt>
    #   otherwise
    def ==(other)
    end
    
    # Compares the vector with another one (strictly).
    # @param [Vector2] other Vector to be compared with.
    # @return [Boolean] <tt>true</tt> if they are strictly equal,
    #   <tt>false</tt> otherwise
    def eql?(other)
    end
    alias equal? eql?
    
    # Returns a formated string to represent the vector. 
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
