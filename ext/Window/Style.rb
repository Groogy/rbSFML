module SFML
  
  # Enumeration of the window styles.
  class Style
    
    # No border / title bar. (this flag and all others are mutually exclusive)
    None = 0
    
    # Title bar + fixed border.
    Titlebar = 1 << 0
    
    # Title bar + resizable border + maximize button.
    Resize = 1 << 1
    
    # Title bar + close button.
    Close = 1 << 2
    
    # Fullscreen mode. (this flag and all others are mutually exclusive)
    Fullscreen = 1 << 3
    
    # Default window style.
    Default = Titlebar | Resize | Close
  
  end
  
end
