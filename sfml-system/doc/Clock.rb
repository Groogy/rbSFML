module SFML
  
  # <tt>Clock</tt> is a lightweight class for measuring time. Its resolution depends on the underlying OS, but you can generally expect a <tt>1</tt> ms resolution.
  #
  # @example
  #   clock = Clock.new
  #   # ...
  #   puts clock.elapsed_time
  #   clock.reset
  #   # ...
  #   puts clock.elapsed_time
  class Clock
    
    # @overload ==(other)
    #   This operator compares two clocks and checks if they are equal.
    #   @param [Color] other The right operand
    #   @return [Color]
    def ==
    end
    
    # Returns a formated string to represent the clock. 
    # @return [String] <tt>Clock(elapsed_time)</tt>
    def inspect
    end
    alias to_s inspect
    alias to_str inspect
    
    # Returns the time elapsed since the last call to <tt>reset</tt> (or the construction of the instance if <tt>reset</tt> has not been called).
    # @return [Fixnum] Time elapsed, in milliseconds
    def elapsed_time
    end
    alias ElapsedTime elapsed_time
    alias elapsedTime elapsed_time
    alias GetElapsedTime elapsed_time
    alias getElapsedTime elapsed_time
    alias get_elapsed_time elapsed_time
    alias time elapsed_time
    
    # Restarts the timer putting the time counter back to zero. 
    # @return [NilClass]
    def reset
    end
    alias Reset reset
    
  end
  
end
