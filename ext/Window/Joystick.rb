module SFML
  
  # Give access to the real-time state of the joysticks. <tt>Joystick</tt>
  # provides an interface to the state of the joysticks. It only contains
  # module functions. Instead, each joystick is identified by an index that is
  # passed to the functions of this module. This module allows users to query
  # the state of joysticks at any time and directly, without having to deal
  # with a window and its events. Compared to the <tt>JoystickMoved</tt>,
  # <tt>JoystickButtonPressed</tt> and <tt>JoystickButtonReleased</tt> events,
  # <tt>Joystick</tt> can retrieve the state of axes and buttons of joysticks
  # at any time (you don't need to store and update a boolean on your side in
  # order to know if a button is pressed or released), and you always get the
  # real state of joysticks, even if they are moved, pressed or released when
  # your window is out of focus and no event is triggered.
  #   
  # SFML supports: 
  # - 8 joysticks (<tt>Joystick::Count</tt>)
  # - 32 buttons per joystick (<tt>Joystick::ButtonCount</tt>)
  # - 8 axes per joystick (<tt>Joystick::AxisCount</tt>)
  #   
  # Unlike the keyboard or mouse, the state of joysticks is sometimes not
  # directly available (depending on the OS), therefore an <tt>update</tt>
  # method must be called in order to update the current state of joysticks.
  # When you have a window with event handling, this is done automatically,
  # you don't need to call anything. But if you have no window, or if you want
  # to check joysticks state before creating one, you must call
  # <tt>Joystick::Update</tt> explicitely.
  # @example
  #   # Is joystick #0 connected?
  #   connected = Joystick.connected?(0)
  #   
  #   # How many buttons does joystick #0 support?
  #   buttons = Joystick.button_count(0)
  #   
  #   # Does joystick #0 define a X axis?
  #   has_x = Joystick.axis?(0, Joystick::X)
  #   
  #   # Is button #2 pressed on joystick #0?
  #   pressed = Joystick.button_pressed?(0, 2)
  #   
  #   # What's the current position of the Y axis on joystick #0?
  #   position = Joystick.axis_position(0, Joystick::Y)
  # @see Keyboard
  # @see Mouse
  module Joystick
    
    # Maximum number of supported joysticks.
    Count = 8
    
    # Maximum number of supported buttons.
    ButtonCount = 32
    
    # Maximum number of supported axes.
    AxisCount = 8
    
    # The X axis.
    X = 0
    
    # The Y axis.
    Y = 1
    
    # The Z axis.
    Z = 2
    
    # The R axis.
    R = 3
    
    # The U axis.
    U = 4
    
    # The V axis.
    V = 5
    
    # The X axis of the point-of-view hat.
    PovX = 6
    
    # The Y axis of the point-of-view hat.
    PovY = 7
    
    class << self
      
      # Check if a joystick is connected.
      # @param [Fixnum] id Index of the joystick to check
      # @return [Boolean] <tt>true</tt> if the joystick is connected,
      #   <tt>false</tt> otherwise 
      def connected?(id)
      end
      alias IsConnected connected?
      
      # Return the number of buttons supported by a joystick. If the joystick
      # is not connected, this function returns <tt>0</tt>.
      # @param [Fixnum] id Index of the joystick
      # @return [Fixnum] Number of buttons supported by the joystick
      def button_count(id)
      end
      alias GetButtonCount button_count
      
      # Check if a joystick supports a given axis. If the joystick is not
      # connected, this function returns <tt>false</tt>.
      # @param [Fixnum] id Index of the joystick
      # @param [Fixnum] axis Axis to check
      # @return [Boolean] <tt>true</tt> if the joystick supports the axis,
      #   <tt>false</tt> otherwise
      def axis?(id, axis)
      end
      alias HasAxis axis?
      
      # Check if a joystick button is pressed. If the joystick is not
      # connected, this function returns <tt>false</tt>.
      # @param [Fixnum] id Index of the joystick
      # @param [Fixnum] button Button to check
      # @return [Boolean] <tt>true</tt> if the button is pressed,
      #   <tt>false</tt> otherwise
      def button_pressed?(id, button)
      end
      alias IsButtonPressed button_pressed?
      alias pressed? button_pressed?
      
      # Get the current position of a joystick axis. If the joystick
      # is not connected, this function returns <tt>0</tt>.
      # @param [Fixnum] id Index of the joystick
      # @param [Fixnum] axis Axis to check
      # @return [Float] Current position of the axis, in range
      #   <tt>-100..100</tt> 
      def axis_position(id, axis)
      end
      alias GetAxisPosition axis_position
      
      # Update the states of all joysticks. This function is used internally
      # by SFML, so you normally don't have to call it explicitely. However,
      # you may need to call it if you have no window yet (or no window at
      # all): in this case the joysticks states are not updated automatically.
      def update
      end
      alias Update update
      
    end
    
  end
  
end
