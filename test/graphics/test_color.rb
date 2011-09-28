
class TestColor < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    color = Color.new(1, 2, 3, 4)
    assert_equal(1, color.r)
    assert_equal(2, color.g)
    assert_equal(3, color.b)
    assert_equal(4, color.a)
  end
  
  def test_initialization2
    color = Color.new(0, 0, 0)
    assert_equal(0, color.r)
    assert_equal(0, color.g)
    assert_equal(0, color.b)
    assert_equal(255, color.a)
    assert_equal(Color::Black, color)
  end
  
  def test_equal
    c0 = Color.new(0, 0, 0)
    c1 = Color::Black
    c2 = Color.new(1, 1, 1)
    c3 = [1, 1, 1]
    assert(c0 == c0)
    assert(c0 == c1)
    assert(c1 != c2)
    assert(c2 == c3)
  end
  
  def test_add
    c0 = Color.new(0, 0, 0)
    c1 = Color.new(100, 100, 100)
    c2 = [200, 200, 200]
    c3 = Color::White
    assert_equal(c1, c1 + c0)
    assert_equal(Color.new(c2), c1 + c1)
    assert_equal(c3, c1 + c1 + c1)
    assert_equal(c3, c1 + c2)
    assert_equal(c0 + c1, c1 + c0)
  end
  
  def test_mult
    c0 = Color.new(128, 128, 128)
    c1 = Color::White
    c2 = Color::Black
    c3 = [64, 64, 64]
    assert_equal(Color.new(c3), c0 * c0)
    assert_equal(c2, c2 * c0)
    assert_equal(c2, c2 * c1)
    assert_equal(c2, c2 * c3)
    assert_equal(c0, c1 * c0)
    assert_equal(c2, c1 * c2)
    assert_equal(Color.new(c3), c1 * c3)
  end
  
  def test_exceptions
    assert_raise(TypeError)     { Color.new("aaa")     }
    assert_raise(ArgumentError) { Color.new(1, 2)      }
    assert_raise(TypeError)     { Color.new(0, 0, "0") }
    assert_raise(RuntimeError)  { Color::White.r = 0   }
    assert_raise(TypeError)     { Color::White + nil   }
    assert_raise(TypeError)     { [5, 5, 5] + Color::Black } # TODO: Make it working
  end
  
end
