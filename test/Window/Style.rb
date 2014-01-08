require 'minitest/autorun'
require 'sfml/window'
include SFML

describe Style do
  it "has presets" do
    assert(defined? Style)
    assert(defined? Style::None)
    assert(defined? Style::Titlebar)
    assert(defined? Style::Resize)
    assert(defined? Style::Close)
    assert(defined? Style::Fullscreen)
    assert(defined? Style::Default)
  end
end
