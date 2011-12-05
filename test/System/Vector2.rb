
class TestVector2 < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    vector = Vector2.new
    assert_equal(0, vector.x)
    assert_equal(0, vector.y)
    assert_instance_of(Fixnum, vector.x)
    assert_instance_of(Fixnum, vector.y)
  end
  
  def test_initialization2
    vector = Vector2.new(10, 15)
    assert_equal(10, vector.x)
    assert_equal(15, vector.y)
    assert_instance_of(Fixnum, vector.x)
    assert_instance_of(Fixnum, vector.y)
    assert(vector == Vector2.new(10.0, 15.0))
    refute(vector.eql? Vector2.new(10.0, 15.0))
  end
  
  def test_initialization3
    vector = Vector2.new(10, 15.5)
    assert_equal(10.0, vector.x)
    assert_equal(15.5, vector.y)
    assert_instance_of(Float, vector.x)
    assert_instance_of(Float, vector.y)
    assert_equal(vector, Vector2.new([10, 15.5]))
  end
  
  def test_operators
    v1 = Vector2.new(5, 5)
    v2 = Vector2.new(15, 15)
    v3 = Vector2.new(7.5, 10)
    v4 = Vector2.new(-5, -5)
    assert_equal(v2, v1 + 10)
    assert_equal(v2, v1 * 3)
    assert_equal(v3, v1 + Vector2.new(2.5, 5))
    assert_equal(v3, v1 * Vector2.new(1.5, 2))
    assert_equal(v1, v2 - 10)
    assert_equal(v1, v2 / 3)
    assert_equal(v1, v3 - Vector2.new(2.5, 5))
    assert_equal(v1, v3 + -Vector2.new(2.5, 5))
    assert_equal(v1, v3 / Vector2.new(1.5, 2))
    assert_equal(v1, -v4)
    assert_equal(v4, -v1)
  end
  
  def test_inspect
    vector1 = Vector2.new(10, 15)
    vector2 = Vector2.new(10, 15.5)
    assert_equal("Vector2(10, 15)", vector1.inspect)
    assert_equal("Vector2(10, 15.5)", vector2.inspect)
    assert_equal(" #{vector1.inspect} ", " #{vector1} ")
    assert_equal(" #{vector2.inspect} ", " #{vector2} ")
  end
  
  def test_exceptions
    assert_raise(TypeError)     { Vector2.new("aaa") }
    assert_raise(TypeError)     { Vector2.new("aaa", "bbb") }
    assert_raise(ArgumentError) { Vector2.new(1, 2, 3) }
  end
  
end
