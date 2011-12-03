module SFML
  
  # Give access to the real-time state of the keyboard. <tt>Keyboard</tt>
  # provides an interface to the state of the keyboard. It only contains
  # module functions (a single keyboard is assumed). This module allows users
  # to query the keyboard state at any time and directly, without having to
  # deal with a window and its events. Compared to the <tt>KeyPressed</tt>
  # and <tt>KeyReleased</tt> events, <tt>Keyboard</tt> can retrieve the state
  # of a key at any time (you don't need to store and update a boolean on your
  # side in order to know if a key is pressed or released), and you always get
  # the real state of the keyboard, even if keys are pressed or released when
  # your window is out of focus and no event is triggered.
  # @example
  #   if Keyboard.pressed? Keyboard::Left
  #     # move left...
  #   elsif Keyboard.pressed? Keyboard::Right
  #     # move right...
  #   elsif Keyboard.pressed? Keyboard::Escape
  #     # quit...
  #   end
  # @see Joystick
  # @see Mouse
  module Keyboard
    
    # The <tt>A</tt> key.
    A = 0
    
    # The <tt>B</tt> key.
    B = 1
    
    # The <tt>C</tt> key.
    C = 2
    
    # The <tt>D</tt> key.
    D = 3
    
    # The <tt>E</tt> key.
    E = 4
    
    # The <tt>F</tt> key.
    F = 5
    
    # The <tt>G</tt> key.
    G = 6
    
    # The <tt>H</tt> key.
    H = 7
    
    # The <tt>I</tt> key.
    I = 8
    
    # The <tt>J</tt> key.
    J = 9
    
    # The <tt>K</tt> key.
    K = 10
    
    # The <tt>L</tt> key.
    L = 11
    
    # The <tt>M</tt> key.
    M = 12
    
    # The <tt>N</tt> key.
    N = 13
    
    # The <tt>O</tt> key.
    O = 14
    
    # The <tt>P</tt> key.
    P = 15
    
    # The <tt>Q</tt> key.
    Q = 16
    
    # The <tt>R</tt> key.
    R = 17
    
    # The <tt>S</tt> key.
    S = 18
    
    # The <tt>T</tt> key.
    T = 19
    
    # The <tt>U</tt> key.
    U = 20
    
    # The <tt>V</tt> key.
    V = 21
    
    # The <tt>W</tt> key.
    W = 22
    
    # The <tt>X</tt> key.
    X = 23
    
    # The <tt>Y</tt> key.
    Y = 24
    
    # The <tt>Z</tt> key.
    Z = 25
    
    # The <tt>0</tt> key.
    Num0 = 26
    
    # The <tt>1</tt> key.
    Num1 = 27
    
    # The <tt>2</tt> key.
    Num2 = 28
    
    # The <tt>3</tt> key.
    Num3 = 29
    
    # The <tt>4</tt> key.
    Num4 = 30
    
    # The <tt>5</tt> key.
    Num5 = 31
    
    # The <tt>6</tt> key.
    Num6 = 32
    
    # The <tt>7</tt> key.
    Num7 = 33
    
    # The <tt>8</tt> key.
    Num8 = 34
    
    # The <tt>9</tt> key.
    Num9 = 35
    
    # The Escape key.
    Escape = 36
    
    # The left Control key.
    LControl = 37
    
    # The left Shift key.
    LShift = 38
    
    # The left Alt key.
    LAlt = 39
    
    # The left System key.
    LSystem = 40
    
    # The right Control key.
    RControl = 41
    
    # The right Shift key.
    RShift = 42
    
    # The right Alt key.
    RAlt = 43
    
    # The right System key.
    RSystem = 44
    
    # The Menu key.
    Menu = 45
    
    # The <tt>[</tt> key.
    LBracket = 46
    
    # The <tt>]</tt> key.
    RBracket = 47
    
    # The <tt>;</tt> key.
    SemiColon = 48
    
    # The <tt>,</tt> key.
    Comma = 49
    
    # The <tt>.</tt> key.
    Period = 50
    
    # The <tt>'</tt> key.
    Quote = 51
    
    # The <tt>/</tt> key.
    Slash = 52
    
    # The <tt>\ </tt>key.
    BackSlash = 53
    
    # The <tt>~</tt> key.
    Tilde = 54
    
    # The <tt>=</tt> key.
    Equal = 55
    
    # The <tt>-</tt> key.
    Dash = 56
    
    # The Space key.
    Space = 57
    
    # The Return key.
    Return = 58
    
    # The Backspace key.
    Back = 59
    
    # The Tab key.
    Tab = 60
    
    # The Page up key.
    PageUp = 61
    
    # The Page down key.
    PageDown = 62
    
    # The End key.
    End = 63
    
    # The Home Key.
    Home = 64
    
    # The Insert key.
    Insert = 65
    
    # The Delete key.
    Delete = 66
    
    # The <tt>+</tt> key.
    Add = 67
    
    # The <tt>-</tt> key.
    Subtract = 68
    
    # The <tt>*</tt> key.
    Multiply = 69
    
    # The <tt>/</tt> key.
    Divide = 70
    
    # Left arrow.
    Left = 71
    
    # Right arrow.
    Right = 72
    
    # Up arrow.
    Up = 73
    
    # Down arrow.
    Down = 74
    
    # The numpad <tt>1</tt> key.
    Numpad0 = 75
    
    # The numpad <tt>1</tt> key.
    Numpad1 = 76
    
    # The numpad <tt>1</tt> key.
    Numpad2 = 77
    
    # The numpad <tt>1</tt> key.
    Numpad3 = 78
    
    # The numpad <tt>1</tt> key.
    Numpad4 = 79
    
    # The numpad <tt>1</tt> key.
    Numpad5 = 80
    
    # The numpad <tt>1</tt> key.
    Numpad6 = 81
    
    # The numpad <tt>1</tt> key.
    Numpad7 = 82
    
    # The numpad <tt>1</tt> key.
    Numpad8 = 83
    
    # The numpad <tt>1</tt> key.
    Numpad9 = 84
    
    # The <tt>F1</tt> key.
    F1 = 85
    
    # The <tt>F2</tt> key.
    F2 = 86
    
    # The <tt>F3</tt> key.
    F3 = 87
    
    # The <tt>F4</tt> key.
    F4 = 88
    
    # The <tt>F5</tt> key.
    F5 = 89
    
    # The <tt>F6</tt> key.
    F6 = 90
    
    # The <tt>F7</tt> key.
    F7 = 91
    
    # The <tt>F8</tt> key.
    F8 = 92
    
    # The <tt>F9</tt> key.
    F9 = 93
    
    # The <tt>F10</tt> key.
    F10 = 94
    
    # The <tt>F11</tt> key.
    F11 = 95
    
    # The <tt>F12</tt> key.
    F12 = 96
    
    # The <tt>F13</tt> key.
    F13 = 97
    
    # The <tt>F14</tt> key.
    F14 = 98
    
    # The <tt>F15</tt> key.
    F15 = 99
    
    # The Pause key.
    Pause = 100
    
    class << self
      
      # Check if a key is pressed.
      # @param [Fixnum] button Key to check
      # @return [Boolean] <tt>true</tt> if the key is pressed,
      #   <tt>false</tt> otherwise 
      def key_pressed?(key)
      end
      alias IsKeyPressed key_pressed?
      alias key_pressed key_pressed?
      
    end
    
  end
  
end
