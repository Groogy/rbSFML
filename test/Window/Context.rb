
# TODO: test it including OpenGL calls

class TestContext < Test::Unit::TestCase
  include SFML
  
  def test1
    context = Context.new
    context.active = true
    context.active = false
    context.active = true
  end
  
  def test2
    context = Context.new(ContextSettings.new, 100, 100)
    context.active = true
    context.active = false
    context.active = true
  end
  
end
