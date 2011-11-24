module SFML
  
  # Window that serves as a target for OpenGL rendering. 
  # 
  # <tt>Window</tt> is the main class of the Window module. It defines an OS
  # window that is able to receive an OpenGL rendering.
  #
  # A <tt>Window</tt> can create its own new window, or be embedded into an
  # already existing control using the <tt>Window#create(handle)</tt> method.
  # This can be useful for embedding an OpenGL rendering area into a view
  # which is part of a bigger GUI with existing windows, controls, etc. It can
  # also serve as embedding an OpenGL rendering area into a window created by
  # another (probably richer) GUI library like Qt or wxWidgets.
  # 
  # The <tt>Window</tt> class provides a simple interface for manipulating the
  # window: move, resize, show/hide, control mouse cursor, etc. It also
  # provides event handling through its <tt>Window#poll_event</tt> and
  # <tt>Window#wait_event</tt> methods.
  #
  # Note that OpenGL experts can pass their own parameters (antialiasing
  # level, bits for the depth and stencil buffers, etc.) to the OpenGL context
  # attached to the window, with the sf::ContextSettings structure which is
  # passed as an optional argument when creating the window.
  #
  # @example
  #   # Declare and create a new window
  #   window = Window.new(VideoMode.new(800, 600), "SFML window")
  #   
  #   # Limit the framerate to 60 frames per second (this step is optional)
  #   window.framerate = 60
  #   
  #   # The main loop - ends as soon as the window is closed
  #   while window.opened?
  #     # Event processing
  #     window.each_event do |event|
  #       if event === Event::Closed
  #         window.close
  #       end
  #     end
  #     
  #     # OpenGL drawing commands go here...
  #     
  #     # End the current frame and display its contents on screen
  #     window.display
  #   end
  class Window
    
    # Same as <tt>create(*args)</tt>. But if you pass zero arguments, it does
    # nothing.
    def initialize(*args)
    end
    
    # Create (or recreate) the window.
    # @overload create(mode, title, style=Style::Default, settings=ContextSettings.new)
    #   This constructor creates the window with the size and pixel depth
    #   defined in <tt>mode</tt>. An optional <tt>style</tt> can be passed to
    #   customize the look and behaviour of the window (borders, title bar,
    #   resizable, closable, ...). If <tt>style</tt> contains
    #   <tt>Style::Fullscreen</tt>, then <tt>mode</tt> must be a valid video
    #   mode. The fourth parameter is an optional structure specifying
    #   advanced OpenGL context settings such as antialiasing, depth-buffer
    #   bits, etc.
    #   @param [VideoMode] mode Video mode to use (defines the width, height
    #     and depth of the rendering area of the window)
    #   @param [String] title Title of the window
    #   @param [Fixnum] style Window style
    #   @param [ContextSettings] settings Additional settings for the
    #     underlying OpenGL context
    #   @return [NilClass]
    # @overload create(handle, settings=ContextSettings.new)
    #   Create (or recreate) the window from an existing control. Use this
    #   method if you want to create an OpenGL rendering area into an already
    #   existing control. If the window was already created, it closes it
    #   first.
    #   @param [Fixnum] handle Platform-specific handle of the control
    #   @param [ContextSettings] settings Additional settings for the
    #     underlying OpenGL context
    #   @return [NilClass]
    def create
    end
    alias Create create
    
    # Close the window and destroy all the attached resources. 
    # After calling this function, the <tt>Window</tt> instance remains valid
    # and you can call <tt>#create</tt> to recreate the window. All other
    # functions such as <tt>#poll_event</tt> or <tt>#display</tt> will still
    # work (i.e. you don't have to test <tt>#opened?</tt> every time), and
    # will have no effect on closed windows.
    # @return [NilClass]
    def close
    end
    alias Close close
    
    # Tell whether or not the window is opened. This function returns whether
    # or not the window exists. Note that a hidden window
    # (<tt>window.show = false</tt>) will return true.
    # @return [Boolean] <tt>true</tt> if the window is opened, <tt>false</tt>
    #   if it has been closed 
    def opened?
    end
    alias IsOpened opened?
    
    # Get the width of the rendering region of the window. The width doesn't
    # include the titlebar and borders of the window.
    # @return [Fixnum] Width in pixels
    # @see #height
    def width
    end
    alias GetWidth width
    
    # Get the height of the rendering region of the window. The height doesn't
    # include the titlebar and borders of the window.
    # @return [Fixnum] Height in pixels
    # @see #width
    def height
    end
    alias GetHeight height
    
    # Get the settings of the OpenGL context of the window. Note that these
    # settings may be different from what was passed to the constructor or the
    # <tt>#create</tt> method, if one or more settings were not supported. In
    # this case, SFML chose the closest match.
    # @return [ContextSettings] Structure containing the OpenGL context
    #   settings 
    def settings
    end
    alias GetSettings settings
    
    # Pop the event on top of events stack, if any, and return it.
    # @overload poll_event
    #   Pop the event on top of events stack, if any, and return it. This
    #   method is not blocking: if there's no pending event then it will
    #   return <tt>nil</tt>. Note that more than one event may be present in
    #   the events stack, thus you should always call this method in a loop to
    #   make sure that you process every pending event.
    #   @example
    #     while event = window.poll_event
    #       # process event...
    #     end
    #   @return [Event, NilClass] The event, or <tt>nil</tt> if the events
    #     stack was empty
    # @overload poll_event(event)
    #   Pop the event on top of events stack, if any, and return it. This
    #   method is not blocking: if there's no pending event then it will
    #   return <tt>false</tt> and leave <tt>event</tt> unmodified. Note that
    #   more than one event may be present in the events stack, thus you
    #   should always call this method in a loop to make sure that you process
    #   every pending event.
    #   @example
    #     event = Event.new
    #     while window.poll_event(event)
    #       # process event...
    #     end
    #   @param [Event] event Event to be returned
    #   @return [Boolean] <tt>true</tt> if an event was returned, or
    #     <tt>false</tt> if the events stack was empty
    # @see #wait_event
    def poll_event
    end
    alias PollEvent poll_event
    alias event poll_event
    
    # Wait for an event and return it.
    # @overload wait_event
    #   Wait for an event and return it. This function is blocking: if there's
    #   no pending event then it will wait until an event is received. After
    #   this method returns (and no error occured), the event object is always
    #   valid and filled properly. This function is typically used when you
    #   have a thread that is dedicated to events handling: you want to make
    #   this thread sleep as long as no new event is received.
    #   @example
    #     while event = window.wait_event
    #       # process event...
    #     end
    #   @return [Event] The event
    # @overload wait_event(event)
    #   Wait for an event and return it. This function is blocking: if there's
    #   no pending event then it will wait until an event is received. After
    #   this method returns (and no error occured), the event object is always
    #   valid and filled properly. This function is typically used when you
    #   have a thread that is dedicated to events handling: you want to make
    #   this thread sleep as long as no new event is received.
    #   @example
    #     event = Event.new
    #     while window.wait_event(event)
    #       # process event...
    #     end
    #   @param [Event] event Event to be returned
    #   @return [Boolean] <tt>false</tt> if any error occured
    # @see #poll_event
    def wait_event
    end
    alias WaitEvent wait_event
    
    # Iterates over all events present in the events stack. This method can
    # also be used as a enumerator. Note that this method pops the events from
    # the stack.
    # @example
    #   window.each_event do |event|
    #     # process event...
    #   end
    # @example
    #   window.each_event.map(&:info).each do |event_info|
    #     # process event information...
    #     # note: if event is Closed, LostFocus or a few others, event_info
    #     # will be nil.
    #   end
    # @return [NilClass, Enumerator]
    def each_event
    end
    
    # Enable or disable vertical synchronization. Activating vertical
    # synchronization will limit the number of frames displayed to the refresh
    # rate of the monitor. This can avoid some visual artifacts, and limit the
    # framerate to a good value (but not constant across different computers).
    # Vertical synchronization is disabled by default.
    # @param [Boolean] enabled True to enable v-sync, false to deactivate
    def vertical_sync=(enabled)
    end
    alias EnableVerticalSync vertical_sync=
    alias vertical_sync vertical_sync=
    
    # Show or hide the mouse cursor. The mouse cursor is shown by default.
    # @param [Boolean] show True to show, false to hide
    def mouse_cursor=(show)
    end
    alias ShowMouseCursor mouse_cursor=
    alias mouse_cursor mouse_cursor=
    
    # Change the position of the window on screen. This function only works
    # for top-level windows (i.e. it will be ignored for windows created from
    # the handle of a child window/control).
    # @param [Fixnum] x Left position
    # @param [Fixnum] y Top position
    def position(x, y)
    end
    alias SetPosition position
    
    # Change the position of the window on screen. This function only works
    # for top-level windows (i.e. it will be ignored for windows created from
    # the handle of a child window/control).
    # @param [Vector2] vector2 The position
    # @example
    #   window.position = [200, 300]
    def position=(vector2)
    end
    
    
    # Change the size of the rendering region of the window. 
    # @param [Fixnum] width New width, in pixels
    # @param [Fixnum] height New height, in pixels
    def size(width, height)
    end
    alias SetSize size
    
    # Change the size of the rendering region of the window. 
    # @param [Vector2] vector2 The new size, in pixels
    # @example
    #   window.size = [640, 480]
    def size=(vector2)
    end
    
    # Change the title of the window.
    # @param [String] title New title
    def title=(title)
    end
    alias SetTitle title=
    alias title title=
    
    # Show or hide the window. The window is shown by default.
    # @param [Boolean] show True to show, false to hide
    def show=(show)
    end
    alias Show show=
    alias show show=
    
  end
  
end
