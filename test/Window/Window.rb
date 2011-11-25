
class TestWindow < Test::Unit::TestCase
  include SFML
  
  def test1
    w = Window.new
    refute(w.opened?)
    w.create([100, 100], "test1")
    assert(w.opened?)
    assert_instance_of(ContextSettings, w.settings)
    w.vertical_sync = true
    w.mouse_cursor = false
    w.title = "==TEST1=="
    w.position = [100, 100]
    assert(w.opened?)
    w.show(false)
    assert(w.opened?)
    w.show(true)
    assert(w.opened?)
    w.close
    refute(w.opened?)
  end
  
  def test_exceptions
    assert_raise(TypeError) { Window.new.dup }
    assert_raise(TypeError) { Window.new.clone }
  end
  
end
