
class TestStyle < Test::Unit::TestCase
  include SFML
  
  def test_constants
    assert(defined? Style)
    assert(defined? Style::None)
    assert(defined? Style::Titlebar)
    assert(defined? Style::Resize)
    assert(defined? Style::Close)
    assert(defined? Style::Fullscreen)
    assert(defined? Style::Default)
  end
  
end
