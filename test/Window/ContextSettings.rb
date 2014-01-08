require 'minitest/autorun'
require 'sfml/window'
include SFML

describe ContextSettings do
  it "can be initialized without arguments" do
    settings = ContextSettings.new
    settings.depth_bits.must_equal 0
    settings.stencil_bits.must_equal 0
    settings.antialiasing_level.must_equal 0
    settings.major_version.must_equal 2
    settings.minor_version.must_equal 0
    settings.depth_bits.must_be_kind_of Fixnum
    settings.stencil_bits.must_be_kind_of Fixnum
    settings.antialiasing_level.must_be_kind_of Fixnum
    settings.major_version.must_be_kind_of Fixnum
    settings.minor_version.must_be_kind_of Fixnum
  end

  it "can be intialized with arguments" do
    settings = ContextSettings.new(10, Rational(30, 5), 2.6, 9)
    settings.depth_bits.must_equal 10
    settings.stencil_bits.must_equal 6
    settings.antialiasing_level.must_equal 2
    settings.major_version.must_equal 9
    settings.minor_version.must_equal 0
    settings.depth_bits.must_be_kind_of Fixnum
    settings.stencil_bits.must_be_kind_of Fixnum
    settings.antialiasing_level.must_be_kind_of Fixnum
    settings.major_version.must_be_kind_of Fixnum
    settings.minor_version.must_be_kind_of Fixnum
  end

  it "can be initialized with an options hash" do
    settings = ContextSettings.new(depth_bits: 10, "MajorVersion" => 2.6, "stencil_bits" => Rational(30, 5))
    settings.depth_bits.must_equal 10
    settings.stencil_bits.must_equal 6
    settings.antialiasing_level.must_equal 0
    settings.major_version.must_equal 2
    settings.minor_version.must_equal 0
    settings.depth_bits.must_be_kind_of Fixnum
    settings.stencil_bits.must_be_kind_of Fixnum
    settings.antialiasing_level.must_be_kind_of Fixnum
    settings.major_version.must_be_kind_of Fixnum
    settings.minor_version.must_be_kind_of Fixnum
  end

  it "can be modified after initialization" do
    settings = ContextSettings.new
    settings.depth_bits = 10
    settings.stencil_bits = Rational(30, 5)
    settings.antialiasing_level = 2.6
    settings.major_version = 9
    settings.depth_bits.must_equal 10
    settings.stencil_bits.must_equal 6
    settings.antialiasing_level.must_equal 2
    settings.major_version.must_equal 9
    settings.minor_version.must_equal 0
    settings.depth_bits.must_be_kind_of Fixnum
    settings.stencil_bits.must_be_kind_of Fixnum
    settings.antialiasing_level.must_be_kind_of Fixnum
    settings.major_version.must_be_kind_of Fixnum
    settings.minor_version.must_be_kind_of Fixnum
  end

  it "has useful string representations" do
    settings1 = ContextSettings.new
    settings2 = ContextSettings.new(10, Rational(30, 5), 2.6, 9)
    settings1.inspect.must_equal "SFML::ContextSettings(depth_bits: 0, stencil_bits: 0, antialiasing_level: 0, major_version: 2, minor_version: 0)"
    settings2.inspect.must_equal "SFML::ContextSettings(depth_bits: 10, stencil_bits: 6, antialiasing_level: 2, major_version: 9, minor_version: 0)"
    settings1.to_s.must_equal settings1.inspect
    settings2.to_s.must_equal settings2.inspect
  end

  it "is initialized with 0 or 4 arguments" do
    proc { ContextSettings.new("aaa") }.must_raise TypeError
    proc { ContextSettings.new("aaa", "bbb") }.must_raise TypeError
    proc { ContextSettings.new(1, 2, 3, 4, 5, 6) }.must_raise ArgumentError
  end
end
