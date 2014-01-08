require 'minitest/autorun'
require 'sfml/system'
include SFML

describe Vector3 do
  it "is initialized with 0, 1, or 3 numerical arguments" do
    proc { Vector3.new('aaa') }.must_raise TypeError
    proc { Vector3.new('aaa', 'bbb', 'ccc') }.must_raise TypeError
    proc { Vector3.new(1, 2) }.must_raise ArgumentError
    proc { Vector3.new(1, 2, 3, 4) }.must_raise ArgumentError
    Vector3.new
    Vector3.new(1, 2, 3)
  end

  it "is initialized to the zero vector with Fixnums by default" do
    vector = Vector3.new
    vector.x.must_equal 0
    vector.y.must_equal 0
    vector.z.must_equal 0
    vector.x.must_be_kind_of Fixnum
    vector.y.must_be_kind_of Fixnum
    vector.z.must_be_kind_of Fixnum
  end

  it "uses Fixnums when initialized with Fixnums" do
    vector = Vector3.new(10, 15, 20)
    vector.x.must_equal 10
    vector.y.must_equal 15
    vector.z.must_equal 20
    vector.x.must_be_kind_of Fixnum
    vector.y.must_be_kind_of Fixnum
    vector.z.must_be_kind_of Fixnum
  end

  it "uses Floats when initialized with any Floats" do
    vector = Vector3.new(10, 15.5, 20)
    vector.x.must_equal 10.0
    vector.y.must_equal 15.5
    vector.z.must_equal 20
    vector.x.must_be_kind_of Float
    vector.y.must_be_kind_of Float
    vector.z.must_be_kind_of Float
  end

  it "accepts initialization arguments in an Array" do
    Vector3.new(10, 15.5, 20).must_equal Vector3.new([10, 15.5, 20])
  end

  it "will test for equality using its components" do
    ivector = Vector3.new(10, 15, 20)
    fvector = Vector3.new(10.0, 15.0, 20)
    ivector.must_equal fvector
    ivector.wont_be_same_as fvector
  end

  describe "when used in arithmetic" do
    before do
      @v1 = Vector3.new(5, 5, 5)
      @v2 = Vector3.new(15, 15, 15)
      @v3 = Vector3.new(7.5, 10, 12.5)
      @v4 = Vector3.new(-5, -5, -5)
    end

    it "can be added to other vectors" do
      (@v1 + Vector3.new(2.5, 5, 7.5)).must_equal @v3
    end

    it "can be multiplied by other vectors" do
      (@v1 * Vector3.new(1.5, 2, 2.5)).must_equal @v3
    end

    it "can be multiplied by scalars" do
      (@v1 * 3).must_equal @v2
      (3 * @v1).must_equal @v2
    end

    it "can be divided by scalars" do
      (@v2 / 3).must_equal @v1
    end

    it "can be negated" do
      @v1.must_equal -@v4
      @v4.must_equal -@v1
      (@v3 + -Vector3.new(2.5, 5, 7.5)).must_equal @v1
    end
  end

  it "has useful string representations" do
    vector1 = Vector3.new(10, 15, 20)
    vector2 = Vector3.new(10, 15.5, 20)
    vector1.inspect.must_equal 'SFML::Vector3(10, 15, 20)'
    vector2.inspect.must_equal 'SFML::Vector3(10, 15.5, 20)'
    vector1.inspect.must_equal vector1.to_s
    vector2.inspect.must_equal vector2.to_s
  end

  describe "when subclassed" do
    before do
      class MyVector3 < Vector3
      end

      @my_vector = MyVector3.new(10, 15, 20)
    end

    it "can be used to initialize vectors and vice versa" do
      vector = Vector3.new(@my_vector)
      @my_vector.must_equal vector

      @my_vector = MyVector3.new(vector)
      @my_vector.must_equal vector
      vector.must_equal @my_vector
    end

    it "can be duped" do
      @my_vector.class.must_equal @my_vector.dup.class
    end

    it "has a useful string representation" do
      @my_vector.inspect.must_equal 'MyVector3(10, 15, 20)'
    end
  end
end
