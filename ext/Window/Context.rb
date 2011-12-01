module SFML
  
  # Class holding a valid drawing context. If you need to make OpenGL calls
  # without having an active window, you can use an instance of this class to
  # get a valid context. Having a valid context is necessary for *every*
  # OpenGL call. Note that a context is only active in its current thread, if
  # you create a new thread it will have no valid context by default. To use 
  # <tt>Context</tt> instance, just construct it and let it live as long as
  # you need a valid context. No explicit activation is needed, all it has to
  # do is to exist. Its destructor will take care of deactivating and freeing
  # all the attached resources.
  class Context
    
    # @overload initialize()
    #   Default constructor. The constructor creates and activates the
    #   context.
    # @overload initialize(settings, width, height)
    #   Construct a in-memory context. This constructor is for internal use,
    #   you don't need to bother with it.
    #   @param [ContextSettings] settings Creation parameters
    #   @param [Fixnum] width Back buffer width
    #   @param [Fixnum] height Back buffer height
    def initialize
    end
    
    # Activate or deactivate explicitely the context.
    # @param [Boolean] active True to activate, false to deactivate
    # @return [Boolean] <tt>true</tt> on success, <tt>false</tt> on failure 
    def active=(active)
    end
    alias SetActive active=
    alias active active=
    
    # Returns how much memory was allocated by this object.
    # @return [Fixnum]
    def memory_usage
    end
    
  end
  
end
