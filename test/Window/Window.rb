
class TestWindow < Test::Unit::TestCase
  include SFML
  
  # TODO: How to test it better?
  
  def test1
    # Initialize without opening
    w = Window.new
    refute(w.opened?)
    assert_match(/Window\([0-9a-fx]+\)/, w.inspect)
    assert_match(/ Window\([0-9a-fx]+\) /, " #{w} ")
    # Create window
    w.create([100, 100], "test1")
    assert_match(/Window\([0-9a-fx]+: "test1"\)/, w.inspect)
    assert_match(/ Window\([0-9a-fx]+: "test1"\) /, " #{w} ")
    assert(w.opened?)
    # Check methods (ensure there's no segfalt)
    assert_instance_of(ContextSettings, w.settings)
    w.vertical_sync = true
    w.mouse_cursor = false
    w.title = "==TEST1=="
    w.position = [100, 100]
    assert_match(/Window\([0-9a-fx]+: "==TEST1=="\)/, w.inspect)
    assert_match(/ Window\([0-9a-fx]+: "==TEST1=="\) /, " #{w} ")
    w.show(false)
    assert(w.opened?)
    w.close
    refute(w.opened?)
    # Recreate closed window
    w.create([100, 100], "Test1")
    assert(w.opened?)
    w.close
    refute(w.opened?)
  end
  
  def test_exceptions
    assert_raise(TypeError) { Window.new.dup }
    assert_raise(TypeError) { Window.new.clone }
  end
  
end
