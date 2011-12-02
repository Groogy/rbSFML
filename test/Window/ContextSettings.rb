
class TestContextSettings < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    settings = ContextSettings.new
    assert_equal(0, settings.depth_bits)
    assert_equal(0, settings.stencil_bits)
    assert_equal(0, settings.antialiasing_level)
    assert_equal(2, settings.major_version)
    assert_equal(0, settings.minor_version)
    assert_instance_of(Fixnum, settings.depth_bits)
    assert_instance_of(Fixnum, settings.stencil_bits)
    assert_instance_of(Fixnum, settings.antialiasing_level)
    assert_instance_of(Fixnum, settings.major_version)
    assert_instance_of(Fixnum, settings.minor_version)
  end
  
  def test_initialization2
    settings = ContextSettings.new(10, Rational(30, 5), 2.6, 9)
    assert_equal(10, settings.depth_bits)
    assert_equal(6, settings.stencil_bits)
    assert_equal(2, settings.antialiasing_level)
    assert_equal(9, settings.major_version)
    assert_equal(0, settings.minor_version)
    assert_instance_of(Fixnum, settings.depth_bits)
    assert_instance_of(Fixnum, settings.stencil_bits)
    assert_instance_of(Fixnum, settings.antialiasing_level)
    assert_instance_of(Fixnum, settings.major_version)
    assert_instance_of(Fixnum, settings.minor_version)
  end
  
  def test_initialization_from_hash
    settings = ContextSettings.new(:depth_bits => 10, "MajorVersion" => 2.6, "stencil_bits" => Rational(30, 5))
    assert_equal(10, settings.depth_bits)
    assert_equal(6, settings.stencil_bits)
    assert_equal(0, settings.antialiasing_level)
    assert_equal(2, settings.major_version)
    assert_equal(0, settings.minor_version)
    assert_instance_of(Fixnum, settings.depth_bits)
    assert_instance_of(Fixnum, settings.stencil_bits)
    assert_instance_of(Fixnum, settings.antialiasing_level)
    assert_instance_of(Fixnum, settings.major_version)
    assert_instance_of(Fixnum, settings.minor_version)
  end
  
  def test_set_values
    settings = ContextSettings.new
    settings.depth_bits = 10
    settings.stencil_bits = Rational(30, 5)
    settings.antialiasing_level = 2.6
    settings.major_version = 9
    assert_equal(10, settings.depth_bits)
    assert_equal(6, settings.stencil_bits)
    assert_equal(2, settings.antialiasing_level)
    assert_equal(9, settings.major_version)
    assert_equal(0, settings.minor_version)
    assert_instance_of(Fixnum, settings.depth_bits)
    assert_instance_of(Fixnum, settings.stencil_bits)
    assert_instance_of(Fixnum, settings.antialiasing_level)
    assert_instance_of(Fixnum, settings.major_version)
    assert_instance_of(Fixnum, settings.minor_version)
  end
  
  def test_inspect
    settings1 = ContextSettings.new
    settings2 = ContextSettings.new(10, Rational(30, 5), 2.6, 9)
    assert_equal("ContextSettings(depth_bits: 0, stencil_bits: 0, antialiasing_level: 0, major_version: 2, minor_version: 0)", settings1.inspect)
    assert_equal("ContextSettings(depth_bits: 10, stencil_bits: 6, antialiasing_level: 2, major_version: 9, minor_version: 0)", settings2.inspect)
    assert_equal(" ContextSettings(depth_bits: 0, stencil_bits: 0, antialiasing_level: 0, major_version: 2, minor_version: 0) ", " #{settings1} ")
    assert_equal(" ContextSettings(depth_bits: 10, stencil_bits: 6, antialiasing_level: 2, major_version: 9, minor_version: 0) ", " #{settings2} ")
  end
  
  def test_exceptions
    assert_raise(TypeError)     { ContextSettings.new("aaa") }
    assert_raise(TypeError)     { ContextSettings.new("aaa", "bbb") }
    assert_raise(ArgumentError) { ContextSettings.new(1, 2, 3, 4, 5, 6) }
  end
  
end
