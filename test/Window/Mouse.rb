
class TestMouse < Test::Unit::TestCase
  include SFML
  
  def test_constants
    constants = [:Left, :Right, :Middle, :XButton1, :XButton2]
    constants.each.with_index do |constant, index|
      assert_equal(index, SFML::Mouse.const_get(constant))
    end
  end
  
end
