module SFML
  
  # Give access to the real-time state of the mouse. <tt>Mouse</tt> provides
  # an interface to the state of the mouse. It only contains module functions
  # (a single mouse is assumed), so it's not meant to be instanciated. This
  # class allows users to query the mouse state at any time and directly,
  # without having to deal with a window and its events. Compared to the
  # <tt>Event::MouseMoved</tt>, <tt>Event::MouseButtonPressed</tt> and
  # <tt>Event::MouseButtonReleased</tt> events, <tt>Mouse</tt> can retrieve
  # the state of the cursor and the buttons at any time (you don't need to
  # store and update a boolean on your side in order to know if a button is
  # pressed or released), and you always get the real state of the mouse, even
  # if it is moved, pressed or released when your window is out of focus and
  # no event is triggered. The <tt>position</tt> and <tt>position=</tt>
  # methods can be used to change or retrieve the current position of the
  # mouse pointer. There are two versions: one that operates in global
  # coordinates (relative to the desktop) and one that operates in window
  # coordinates (relative to a specific window).
  # @example
  #   if Mouse.button_pressed? Mouse::Left
  #     # left click...
  #   end
  #
  #   # get global mouse position
  #   position = Mouse.position
  #
  #   # set mouse position relative to a window
  #   Mouse.position([100, 200], window)
  # @see Joystick
  # @see Keyboard
  module Mouse
    
    # The left mouse button.
    Left = 0
    
    # The right mouse button.
    Right = 1
    
    # The middle (wheel) mouse button.
    Middle = 2
    
    # The first extra mouse button.
    XButton1 = 3
    
    # The second extra mouse button.
    XButton2 = 4
    
    class << self
      
      # Check if a mouse button is pressed.
      # @param [Fixnum] button Button to check
      # @return [Boolean] <tt>true</tt> if the button is pressed,
      #   <tt>false</tt> otherwise 
      def button_pressed?(button)
      end
      alias IsButtonPressed button_pressed?
      alias button_pressed button_pressed?
      
      # @overload position
      #   Get the current position of the mouse in desktop coordinates. This
      #   function returns the global position of the mouse cursor on the
      #   desktop.
      #   @return [Vector2] Current position of the mouse
      # @overload position(relative_to)
      #   Get the current position of the mouse in window coordinates. This
      #   function returns the current position of the mouse cursor, relative
      #   to the given window.
      #   @param [Window] relativeTo Reference window
      #   @return [Vector2] Current position of the mouse
      # @overload position=(position)
      #   Set the current position of the mouse in desktop coordinates. This
      #   function sets the global position of the mouse cursor on the
      #   desktop.
      #   @param [Vector2] position New position of the mouse
      # @overload position(position, relative_to)
      #   Set the current position of the mouse in window coordinates. This
      #   function sets the current position of the mouse cursor, relative to
      #   the given window.
      #   @param [Vector2] position New position of the mouse
      #   @param [Window] relativeTo Reference window
      def position
      end
      alias position= position
      alias GetPosition position
      alias SetPosition position
      
    end
    
  end
  
end
