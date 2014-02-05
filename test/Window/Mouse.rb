require 'minitest/autorun'
require 'sfml/window'
include SFML

describe Mouse do
  it "has button constants" do
    constants = [:Left, :Right, :Middle, :XButton1, :XButton2]

    constants.each.with_index do |constant, index|
      Mouse.const_get(constant).must_equal index
    end
  end
end
