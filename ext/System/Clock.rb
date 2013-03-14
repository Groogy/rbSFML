module SFML
  
  # <tt>Clock</tt> is a lightweight class for measuring time. 
  #
  # It provides the most precise time that the underlying OS can achieve (generally microseconds or nanoseconds). It also ensures monotonicity, which means that the returned time can never go backward, even if the system time is changed..
  #
  # @example
  #   clock = SFML::Clock.new
  #   # ...
  #   puts clock.elapsed_time
  #   clock.restart
  #   # ...
  #   puts clock.elapsed_time
  class Clock
    
    # Returns the time elapsed since the last call to <tt>restart</tt> (or the construction of the instance if <tt>restart</tt> has not been called).
    # @return [Time] The elapsed Time
    def elapsed_time
    end
    alias getElapsedTime elapsed_time
    alias get_elapsed_time elapsed_time
    alias time elapsed_time
    
    # Restarts the timer putting the time counter back to zero. 
    # @return [Time] The elapsed Time
    def restart
    end
    
    # Returns a formated string to represent the clock. 
    # @return [String]
    def inspect
    end
    alias to_s inspect
  end
end
