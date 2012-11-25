# Based on SFML example Window
# https://github.com/LaurentGomila/SFML/blob/master/examples/window/Window.cpp

begin
  require 'sfml/sfml'
rescue LoadError
  require 'sfml/system'
  require 'sfml/window'
end

require 'opengl' # from ruby-opengl gem

include SFML

# Create the main window
window = Window.new([640, 480], "rbSFML Window", Style::Default, depth_bits: 32)

# Create a clock for measuring the time elapsed
clock = Clock.new

# Set the color and depth clear values
glClearDepth(1.0)
glClearColor(0.0, 0.0, 0.0, 0.0)

# Enable Z-buffer read and write
glEnable(GL_DEPTH_TEST)
glDepthMask(GL_TRUE)

# Setup a perspective projection
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
gluPerspective(90.0, 1.0, 1.0, 500.0)

# Start the game loop
while window.open?
  
  # Process events
  window.each_event do |event|
    case event.type
    when Event::Closed # Close window : exit
      window.close
    when Event::KeyPressed # Escape key : exit
      window.close if event.key.code == Keyboard::Escape
    when Event::Resized # Resize event : adjust viewport
      glViewport(0, 0, event.size.width, event.size.height)
    end
  end
  
  # Activate the window before using OpenGL commands.
  # This is useless here because we have only one window which is
  # always the active one, but don't forget it if you use multiple windows
  window.set_active
  
  # Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
  
  # Apply some transformations
  glMatrixMode(GL_MODELVIEW)
  glLoadIdentity()
  glTranslatef(0.0, 0.0, -200.0)
  glRotatef(clock.time.as_milliseconds * 0.05, 1.0, 0.0, 0.0)
  glRotatef(clock.time.as_milliseconds * 0.03, 0.0, 1.0, 0.0)
  glRotatef(clock.time.as_milliseconds * 0.09, 0.0, 0.0, 1.0)
  
  # Draw a cube
  glBegin(GL_QUADS)
    
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-50.0, -50.0, -50.0)
    glVertex3f(-50.0,  50.0, -50.0)
    glVertex3f( 50.0,  50.0, -50.0)
    glVertex3f( 50.0, -50.0, -50.0)
    
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-50.0, -50.0, 50.0)
    glVertex3f(-50.0,  50.0, 50.0)
    glVertex3f( 50.0,  50.0, 50.0)
    glVertex3f( 50.0, -50.0, 50.0)
    
    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(-50.0, -50.0, -50.0)
    glVertex3f(-50.0,  50.0, -50.0)
    glVertex3f(-50.0,  50.0,  50.0)
    glVertex3f(-50.0, -50.0,  50.0)
    
    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(50.0, -50.0, -50.0)
    glVertex3f(50.0,  50.0, -50.0)
    glVertex3f(50.0,  50.0,  50.0)
    glVertex3f(50.0, -50.0,  50.0)
    
    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(-50.0, -50.0,  50.0)
    glVertex3f(-50.0, -50.0, -50.0)
    glVertex3f( 50.0, -50.0, -50.0)
    glVertex3f( 50.0, -50.0,  50.0)
    
    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(-50.0, 50.0,  50.0)
    glVertex3f(-50.0, 50.0, -50.0)
    glVertex3f( 50.0, 50.0, -50.0)
    glVertex3f( 50.0, 50.0,  50.0)
  
  glEnd()
  
  # Finally, display the rendered frame on screen
  window.display
end
