require 'minitest/autorun'
require 'sfml/window'
include SFML

# TODO: test it including OpenGL calls

describe Context do
  it "can be made active/inactive with the default constructor" do
    context = Context.new
    context.active = true
    context.active = false
    context.active = true
  end

  it "can be made active/inactive when constructed with arguments" do
    context = Context.new(ContextSettings.new, 100, 100)
    context.active = true
    context.active = false
    context.active = true
  end
end
