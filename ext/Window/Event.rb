module SFML
  
  # Defines a system event and its parameters. 
  # 
  # <tt>Event</tt> holds all the informations about a system event that just
  # happened.
  # 
  # Events are retrieved using the <tt>Window#poll_event</tt>,
  # <tt>Window#wait_event</tt> and <tt>Window#each_event</tt> methods.
  # 
  # A <tt>Event</tt> instance contains the type of the event (mouse moved, key
  # pressed, window closed, ...) as well as the details about this particular
  # event. Please note that the event parameters are defined in a union, which
  # means that only the member matching the type of the event will be properly
  # filled; all other members will have undefined values and must not be read
  # if the type of the event doesn't match. For example, if you received a
  # <tt>KeyPressed</tt> event, then you must read the <tt>event#key</tt>
  # method, all other methods such as <tt>event#mouse_move</tt> or
  # <tt>event#text</tt> will have undefined values.
  # 
  # @example
  #   window.each_event do |event|
  #     # Request for closing the window
  #     if event === Event::Closed
  #       window.close
  #     end
  #     
  #     # The escape key was pressed
  #     if event === Event::KeyPressed and event.key.code == Keyboard::Escape
  #       window.close
  #     end
  #     
  #     # The window was resized
  #     if event === Event::Resized
  #       do_something(event.size.width, event.size.height)
  #     end
  #     
  #     # Etc ...
  #     
  #   end
  class Event
    
    # Size events parameters (<tt>Resized</tt>)
    class Size
      
      # New width, in pixels.
      # @return [Fixnum]
      attr_accessor :width
      alias Width width
      
      # New height, in pixels.
      # @return [Fixnum]
      attr_accessor :height
      alias Height height
      
    end
    
    # Keyboard event parameters (<tt>KeyPressed</tt>, <tt>KeyReleased</tt>) 
    class Key
      
      # Code of the key that has been pressed.
      # @return [Fixnum]
      attr_accessor :code
      alias Code code
      
      # Is the Alt key pressed?
      # @return [Fixnum]
      attr_accessor :alt
      alias Alt alt
      
      # Is the Control key pressed?
      # @return [Fixnum]
      attr_accessor :control
      alias Control control
      
      # Is the Shift key pressed?
      # @return [Fixnum]
      attr_accessor :shift
      alias Shift shift
      
      # Is the System key pressed?
      # @return [Fixnum]
      attr_accessor :system
      alias System system
      
    end
    
    # Text event parameters (<tt>TextEntered</tt>)
    class Text
      
      # UTF-32 unicode value of the character.
      # @return [Fixnum]
      attr_accessor :unicode
      alias Unicode unicode
      
    end
    
    # Mouse move event parameters (<tt>MouseMoved</tt>) 
    class MouseMove
      
      # X position of the mouse pointer, relative to the left of the owner
      # window.
      # @return [Fixnum]
      attr_accessor :x
      alias X x
      
      # Y position of the mouse pointer, relative to the top of the owner
      # window.
      # @return [Fixnum]
      attr_accessor :y
      alias Y y
      
    end
    
    # Mouse buttons events parameters (<tt>MouseButtonPressed</tt>,
    # <tt>MouseButtonReleased</tt>) 
    class MouseButton
      
      # Code of the button that has been pressed.
      # @return [Fixnum]
      attr_accessor :button
      alias Button button
      
      # X position of the mouse pointer, relative to the left of the owner
      # window.
      # @return [Fixnum]
      attr_accessor :x
      alias X x
      
      # Y position of the mouse pointer, relative to the top of the owner
      # window.
      # @return [Fixnum]
      attr_accessor :y
      alias Y y
      
    end
    
    # Mouse wheel events parameters (<tt>MouseWheelMoved</tt>)
    class MouseWheel
      
      # Number of ticks the wheel has moved (positive is up, negative is down)
      # @return [Fixnum]
      attr_accessor :delta
      alias Delta delta
      
      # X position of the mouse pointer, relative to the left of the owner
      # window.
      # @return [Fixnum]
      attr_accessor :x
      alias X x
      
      # Y position of the mouse pointer, relative to the top of the owner
      # window.
      # @return [Fixnum]
      attr_accessor :y
      alias Y y
      
    end
    
    # Joystick axis move event parameters (<tt>JoystickMoved</tt>)
    class JoystickMove
      
      # Index of the joystick (in range <tt>0...Joystick::Count</tt>)
      # @return [Fixnum]
      attr_accessor :id
      alias JoystickId id
      
      # Axis on which the joystick moved.
      # @return [Fixnum]
      attr_accessor :axis
      alias Axis axis
      
      # New position on the axis (in range <tt>-100..100</tt>)
      # @return [Float]
      attr_accessor :position
      alias Position position
      
    end
    
    # Joystick buttons events parameters (<tt>JoystickButtonPressed</tt>,
    # <tt>JoystickButtonReleased</tt>) 
    class JoystickButton
      
      # Index of the joystick (in range <tt>0...Joystick::Count</tt>)
      # @return [Fixnum]
      attr_accessor :id
      alias JoystickId id
      
      # Index of the button that has been pressed (in range 
      # <tt>0...Joystick::ButtonCount</tt>)
      # @return [Fixnum]
      attr_accessor :button
      alias Button button
      
    end
    
    # Joystick connection events parameters (<tt>JoystickConnected</tt>,
    # <tt>JoystickDisconnected</tt>) 
    class JoystickConnect
      
      # Index of the joystick (in range <tt>0...Joystick::Count</tt>)
      # @return [Fixnum]
      attr_accessor :id
      alias JoystickId id
      
    end
    
    # The window was resized.
    Closed = 0
    
    # The window was resized.
    Resized = 1
    
    # The window lost the focus.
    LostFocus = 2
    
    # The window gained the focus.
    GainedFocus = 3
    
    # A character was entered.
    TextEntered = 4
    
    # A key was pressed.
    KeyPressed = 5
    
    # A key was released.
    KeyReleased = 6
    
    # The mouse wheel was scrolled.
    MouseWheelMoved = 7
    
    # A mouse button was pressed.
    MouseButtonPressed = 8
    
    # A mouse button was released.
    MouseButtonReleased = 9
    
    # The mouse cursor moved.
    MouseMoved = 10
    
    # The mouse cursor entered the area of the window.
    MouseEntered = 11
    
    # The mouse cursor left the area of the window.
    MouseLeft = 12
    
    # A joystick button was pressed.
    JoystickButtonPressed = 13
    
    # A joystick button was released.
    JoystickButtonReleased = 14
    
    # The joystick moved along an axis.
    JoystickMoved = 15
    
    # A joystick was connected.
    JoystickConnected = 16
    
    # A joystick was disconnected.
    JoystickDisconnected = 17
    
    # Type of the event
    # @return [Fixnum] Constant of the event type
    def type
    end
    alias Type type
    
    # @return [NilClass, Size, Key, Text, MouseMove, MouseButton, MouseWheel,
    #   JoystickMove, JoystickButton, JoystickConnect]
    def info
    end
    
    # Returns <tt>true</tt> if <tt>self</tt> is kind of, equal or of the same
    # type of <tt>other</tt>, <tt>false</tt> otherwise.
    # @return [Boolean]
    # @example
    #   case event
    #   when Event::Closed
    #     # Do something...
    #   when ...
    #   end
    def ===(other)
    end
    
    # Size event parameters.
    # @return [Size]
    def size
    end
    alias Size size
    
    # Key event parameters.
    # @return [Key]
    def key
    end
    alias Key key
    
    # Text event parameters.
    # @return [Text]
    def text
    end
    alias Text text
    
    # Mouse move event parameters.
    # @return [MouseMove]
    def mouse_move
    end
    alias MouseMove mouse_move
    
    # Mouse button event parameters.
    # @return [MouseButton]
    def mouse_button
    end
    alias MouseButton mouse_button
    
    # Mouse wheel event parameters.
    # @return [MouseWheel]
    def mouse_wheel
    end
    alias MouseWheel mouse_wheel
    
    # Joystick move event parameters.
    # @return [JoystickMove]
    def joystick_move
    end
    alias JoystickMove joystick_move
    
    # Joystick button event parameters.
    # @return [JoystickButton]
    def joystick_button
    end
    alias JoystickButton joystick_button
    
    # Joystick (dis)connect event parameters.
    # @return [JoystickConnect]
    def joystick_connect
    end
    alias JoystickConnect joystick_connect
    
  end
  
end
