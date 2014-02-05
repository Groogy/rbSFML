require 'minitest/autorun'
require 'sfml/graphics'
include SFML

describe Rect do
  it "will create a size 0 rect by default" do
    rect = Rect.new
    rect.left.must_equal   0
    rect.top.must_equal    0
    rect.width.must_equal  0
    rect.height.must_equal 0
    rect.left.must_be_instance_of   Fixnum
    rect.top.must_be_instance_of    Fixnum
    rect.width.must_be_instance_of  Fixnum
    rect.height.must_be_instance_of Fixnum
  end

  it "can set left/top/width/height using Fixnums" do
    rect = Rect.new(10, 15, 50, 40)
    rect.left.must_equal   10
    rect.top.must_equal    15
    rect.width.must_equal  50
    rect.height.must_equal 40
    rect.left.must_be_instance_of   Fixnum
    rect.top.must_be_instance_of    Fixnum
    rect.width.must_be_instance_of  Fixnum
    rect.height.must_be_instance_of Fixnum
    rect.wont_equal Rect.new(10.0, 15.0, 50.0, 40.0)
  end

  it "can set left/top/width/height using Floats" do
    rect = Rect.new(10, 15, 50, 40.0)
    rect.left.must_equal   10.0
    rect.top.must_equal    15.0
    rect.width.must_equal  50.0
    rect.height.must_equal 40.0
    rect.left.must_be_instance_of   Float
    rect.top.must_be_instance_of    Float
    rect.width.must_be_instance_of  Float
    rect.height.must_be_instance_of Float
    rect.wont_equal Rect.new(10, 15, 50, 40)
  end

  it "can be initialized using Vectors" do
    pos = Vector2.new(10, 15)
    size = Vector2.new(20.3, 10.5)
    rect = Rect.new(pos, size)
    rect.left.must_equal   10.0
    rect.top.must_equal    15.0
    rect.width.must_equal  20.3
    rect.height.must_equal 10.5
    rect.left.must_be_instance_of   Float
    rect.top.must_be_instance_of    Float
    rect.width.must_be_instance_of  Float
    rect.height.must_be_instance_of Float
    rect.must_equal Rect.new([pos, size])
  end

  it "can test for containment of points" do
    rect = Rect.new(5, 5, 10, 10)
    rect.must_be :contains?, 7.5, 6
    rect.must_be :contains?, 5, 5
    rect.must_be :contains?, 10, 10
    rect.wont_be :contains?, 4, 5
    rect.wont_be :contains?, 16, 8
    proc { Rect.new.contains? nil }.must_raise TypeError
    proc { Rect.new.contains? "", "" }.must_raise TypeError
  end

  it "can be intersected with other Rects" do
    rect1 = Rect.new(5, 5, 10, 10)
    rect2 = Rect.new(2, 3, 13, 6)
    rect3 = Rect.new(3.5, 0, 1, 10)
    rect1.must_equal(rect1 & rect1)
    Rect.new(5, 5, 10, 4).must_equal(rect1 & rect2)
    Rect.new(3.5, 3.0, 1.0, 6.0).must_equal(rect2 & rect3)
    (rect1 & rect3).must_be_nil
    proc { Rect.new & nil }.must_raise TypeError
  end

  it "has a useful string representation" do
    rect1 = Rect.new(10, 15, 50, 40)
    rect2 = Rect.new(10, 15, 50, 40.5)
    rect1.inspect.must_equal "SFML::Rect(10, 15, 50, 40)"
    rect2.inspect.must_equal "SFML::Rect(10.0, 15.0, 50.0, 40.5)"
    rect1.to_s.must_equal "SFML::Rect(10, 15, 50, 40)"
    rect2.to_s.must_equal "SFML::Rect(10.0, 15.0, 50.0, 40.5)"
  end

  it "is initialized with 0 or 4 numbers" do
    proc { Rect.new('aaa') }.must_raise TypeError
    proc { Rect.new('aaa', 'bbb') }.must_raise TypeError
    proc { Rect.new(1, 2, 3) }.must_raise ArgumentError
    proc { Rect.new(0, 0, 10, ?5) }.must_raise TypeError
  end
end
