module SFML
  # Represents a time value.
  #
  # <tt>SFML::Time</tt> encapsulates a time value in a flexible way.
  #
  # It allows to define a time value either as a number of seconds, milliseconds or microseconds. It also works the other way round: you can read a time value as either a number of seconds, milliseconds or microseconds.
  #
  # By using such a flexible interface, the API doesn't impose any fixed type or resolution for time values, and let the user choose its own favorite representation.
  #
  # Time values support the usual mathematical operations: you can add or subtract two times, multiply or divide a time by a number, compare two times, etc.
  #
  # Since they represent a time span and not an absolute time value, times can also be negative.
  #
  # @example
  #   t1 = SFML::seconds( 0.1 )
  #   milli = t1.as_miliseconds // 100
  #
  #   t2 = SFML::milliseconds( 30 )
  #   micro = t2.as_microseconds() // 30000
  #
  #   t3 = sf::microseconds( -800000 )
  #   sec = t3.as_seconds() // -0.8
  #
  #   def update( elapsed )
  #    position += speed * elapsed.as_seconds()
  #   end
  #  
  #   update( SFML::milliseconds( 100 ) )
  class Time
    # Return the time value as a number of seconds. 
    # @return [Float] Time in seconds
    def as_seconds
    end
    alias asSeconds as_seconds
    alias toSeconds as_seconds
    alias to_seconds as_seconds
    
    # Return the time value as a number of milliseconds
    # @return [Fixnum] Time in milliseconds
    def as_milliseconds
    end
    alias asMilliseconds as_milliseconds
    alias toMilliseconds as_milliseconds
    alias to_milliseconds as_milliseconds
    
    # Return the time value as a number of microseconds
    # @return [Fixnum] Time in microseconds
    def as_microseconds
    end
    alias asMicroseconds as_microseconds
    alias toMicroseconds as_microseconds
    alias to_microseconds as_microseconds
    
    # Overload of == operator to compare two time values. 
    # @param [Time] other Time to be compared with.
    # @return [Boolean] <tt>true</tt> if they are equal, <tt>false</tt>
    def ==(other)
    end
    alias eql? ==
    alias equal? ==
    
    # Returns a formated string to represent the time. 
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
