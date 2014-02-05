require 'minitest/autorun'
require 'sfml/window'
include SFML

describe Window do
  # TODO: How to test it better?

  before do
    @window = Window.new
  end

  it "is not open by default" do
    @window.wont_be :open?
  end

  it "has useful string represntations" do
    @window.inspect.must_match /^SFML::Window\([0-9a-fx]+\)$/
    @window.to_s.must_match /^SFML::Window\([0-9a-fx]+\)$/
  end

  it "can be created after initialization" do
    @window.create([100, 100], "test1")
    @window.inspect.must_match /^SFML::Window\([0-9a-fx]+: "test1"\)$/
    @window.to_s.must_match /^SFML::Window\([0-9a-fx]+: "test1"\)$/
    @window.must_be :open?

    @window.show false
    @window.must_be :open?
    @window.close
    @window.wont_be :open?

    @window.create([100, 100], "Test1")
    @window.must_be :open?
    @window.close
    @window.wont_be :open?
  end

  it "has writable attributes" do
    @window.settings.must_be_kind_of ContextSettings
    @window.vertical_sync = true
    @window.mouse_cursor = false
    @window.position = [100, 100]
  end

  it "can change its title after initialization" do
    @window.title = "==TEST1=="
    @window.inspect.must_match /^SFML::Window\([0-9a-fx]+: "==TEST1=="\)$/
    @window.inspect.must_match /^SFML::Window\([0-9a-fx]+: "==TEST1=="\)$/
  end

  it "cannot be duped" do
    proc { @window.dup }.must_raise TypeError
  end

  it "cannot be cloned" do
    proc { @window.clone }.must_raise TypeError
  end
end
