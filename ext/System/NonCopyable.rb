module SFML
  
  # Utility mixin module that makes any derived class non-copyable.
  #
  # This module makes its instances non-copyable, by explicitely disabling its copy initializer.
  #
  # To create a non-copyable class, simply mixin from SFML::NonCopyable.
  #
  # Deciding whether the instances of a class can be copied or not is a very important design choice. You are strongly encouraged to think about it before writing a class, and to use SFML::NonCopyable when necessary to prevent many potential future errors when using it. This is also a very important indication to users of your class. 
  #
  # @example
  #   class MyNonCopyableClass
  #     include SFML::NonCopyable
  #   end
  #
  module NonCopyable
  end
end
