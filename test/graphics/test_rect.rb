
class TestRect < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    rect = Rect.new
    assert_equal(0, rect.left)
    assert_equal(0, rect.top)
    assert_equal(0, rect.width)
    assert_equal(0, rect.height)
    assert_equal(Fixnum, rect.left.class)
    assert_equal(Fixnum, rect.top.class)
    assert_equal(Fixnum, rect.width.class)
    assert_equal(Fixnum, rect.height.class)
  end
  
  def test_initialization2
    rect = Rect.new(10, 15, 50, 40)
    assert_equal(10, rect.left)
    assert_equal(15, rect.top)
    assert_equal(50, rect.width)
    assert_equal(40, rect.height)
    assert_equal(Fixnum, rect.left.class)
    assert_equal(Fixnum, rect.top.class)
    assert_equal(Fixnum, rect.width.class)
    assert_equal(Fixnum, rect.height.class)
    assert(rect != Rect.new(10.0, 15.0, 50.0, 40.0))
  end
  
  def test_initialization3
    rect = Rect.new(10, 15, 50, 40.5)
    assert_equal(10.0, rect.left)
    assert_equal(15.0, rect.top)
    assert_equal(50.0, rect.width)
    assert_equal(40.5, rect.height)
    assert_equal(Float, rect.left.class)
    assert_equal(Float, rect.top.class)
    assert_equal(Float, rect.width.class)
    assert_equal(Float, rect.height.class)
  end
  
  def test_initialization4
    pos = Vector2.new(10, 15)
    size = Vector2.new(20.3, 10.5)
    rect = Rect.new(pos, size)
    assert_equal(10.0, rect.left)
    assert_equal(15.0, rect.top)
    assert_equal(20.3, rect.width)
    assert_equal(10.5, rect.height)
    assert_equal(Float, rect.left.class)
    assert_equal(Float, rect.top.class)
    assert_equal(Float, rect.width.class)
    assert_equal(Float, rect.height.class)
    assert_equal(rect, Rect.new([pos, size]))
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
    assert_equal(rect1, rect1 & rect1)
    assert_equal(Rect.new(5, 5, 10, 4), rect1 & rect2)
    assert_equal(Rect.new(3.5, 3.0, 1.0, 6.0), rect2 & rect3)
    assert_equal(nil, rect1 & rect3)
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
    assert_raise(TypeError)     { Rect.new("aaa") }
    assert_raise(TypeError)     { Rect.new("aaa", "bbb") }
    assert_raise(ArgumentError) { Rect.new(1, 2, 3) }
    assert_raise(TypeError)     { Rect.new(0, 0, 10, "5") }
    assert_raise(TypeError)     { Rect.new & nil }
    assert_raise(TypeError)     { Rect.new.contains?(nil) }
    assert_raise(TypeError)     { Rect.new.contains?("", "") }
  end
  
end
