
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
  
end
