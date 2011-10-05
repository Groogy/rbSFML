
class TestRect < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    rect = Rect.new
    assert_equal(0, rect.left)
    assert_equal(0, rect.top)
    assert_equal(0, rect.width)
    assert_equal(0, rect.height)
  end
  
  def test_initialization2
    rect = Rect.new(10, 15, 50, 40)
    assert_equal(10, rect.left)
    assert_equal(15, rect.top)
    assert_equal(50, rect.width)
    assert_equal(40, rect.height)
  end
  
  def test_initialization3
    rect = Rect.new(10, 15, 50, 40.5)
    assert(Float === rect.left)
    assert(Float === rect.top)
    assert(Float === rect.width)
    assert(Float === rect.height)
  end
  
  def test_initialization4
    pos = Vector2.new(10, 15)
    size = Vector2.new(20.3, 10.5)
    rect = Rect.new(pos, size)
    assert(Float === rect.left)
    assert(Float === rect.top)
    assert(Float === rect.width)
    assert(Float === rect.height)
    assert_equal(rect, Rect.new([pos, size])) # WHY IT FAILS?
  end
  
  def test_contains
    rect = Rect.new(5, 5, 10, 10)
    assert(rect.contains?(7.5, 6))
    assert(rect.contains?(5, 5))
    assert(rect.contains?(10, 10))
    assert(rect.contains?(10, 10))
  end
  
  def test_intersects
    rect1 = Rect.new(5, 5, 10, 10)
    rect2 = Rect.new(2, 3, 13, 6)
    rect3 = Rect.new(3.5, 0, 1, 10)
	assert_equal(rect1 & rect1, rect1) # WHY IT FAILS?
	assert_equal(rect1 & rect2, Rect.new(5, 5, 10, 4))
	assert_equal(rect2 & rect3, Rect.new(5, 5, 10, 4))
	assert_equal(rect1 & rect3, Rect.new(5, 5, 10, 4))
  end
  
  def test_inspect
    rect1 = Rect.new(10, 15, 50, 40)
    rect2 = Rect.new(10, 15, 50, 40.5)
    assert_equal("Rect(10, 15, 50, 40)", rect1.inspect)
    assert_equal("Rect(10.0, 15.0, 50.0, 40.5)", rect2.inspect)
    assert_equal("rect1 = #{rect1}", "rect1 = " + rect1.inspect)
    assert_equal("rect2 = #{rect2}", "rect2 = " + rect2.inspect)
  end
  
  def test_exceptions
    assert_raise(TypeError)     { Rect.new("aaa")         }
    assert_raise(TypeError)     { Rect.new("aaa", "bbb")  }
    assert_raise(ArgumentError) { Rect.new(1, 2, 3)       }
    assert_raise(TypeError)     { Rect.new(0, 0, 10, "5") }
  end
  
end
