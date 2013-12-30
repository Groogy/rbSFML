require 'minitest/autorun'
require 'sfml/graphics'
include SFML

describe Color do
  it "will set RGBA components using Fixnums" do
    color = Color.new(1, 2, 3, 4)
    color.r.must_equal 1
    color.g.must_equal 2
    color.b.must_equal 3
    color.a.must_equal 4
    color.r.must_be_instance_of Fixnum
    color.g.must_be_instance_of Fixnum
    color.b.must_be_instance_of Fixnum
    color.a.must_be_instance_of Fixnum
  end

  it "can be initialized using an array" do
    Color.new(200, 200, 200).must_equal Color.new([200, 200, 200])
  end

  it "will have maximum opacity by default" do
    color = Color.new(0, 0, 0)
    color.a.must_equal 255
  end

  it "will be opaque black by default" do
    color = Color.new
    color.must_equal Color.new(0, 0, 0)
    color.must_equal Color::Black
  end

  it "will be comparable with Arrays" do
    ary = [1, 1, 1]
    Color.new(1, 1, 1).must_equal ary
    Color.new(0, 0, 0).wont_equal ary
  end

  it "can be added to other colors" do
    c0 = Color.new(0, 0, 0)
    c1 = Color.new(100, 100, 100)
    c2 = [200, 200, 200]
    c3 = Color::White
    c1.must_equal(c1 + c0)
    c2.must_equal(c1 + c1)
    c3.must_equal(c1 + c1 + c1)
    c3.must_equal(c1 + c2)
    proc { Color::White + nil       }.must_raise TypeError
    proc { [5, 5, 5] + Color::Black }.must_raise TypeError
  end

  it "can be multiplied by other colors" do
    c0 = Color.new(128, 128, 128)
    c1 = Color::White
    c2 = Color::Black
    c3 = [64, 64, 64]
    c2.must_equal(c2 * c0)
    c2.must_equal(c2 * c1)
    c2.must_equal(c2 * c3)
    c0.must_equal(c1 * c0)
    c2.must_equal(c1 * c2)
    (c0 * c0).must_equal c3
    (c1 * c3).must_equal c3
  end

  it "can only be initialized with 0, 3, or 4 numbers" do
    proc { Color.new('aaa')    }.must_raise TypeError
    proc { Color.new(1, 2)     }.must_raise ArgumentError
    proc { Color.new(0, 0, ?0) }.must_raise TypeError
  end

  it "cannot change the components of constants" do
    proc { Color::White.r = 0 }.must_raise RuntimeError
  end
end
