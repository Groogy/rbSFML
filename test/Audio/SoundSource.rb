require 'minitest/autorun'
require 'sfml/audio'
include SFML

describe SoundSource do
  it "cannot be manually instantiated" do
    proc { SoundSource.new }.must_raise RuntimeError
  end

  describe "when subclassed" do
    before do
      class MySoundSource < SoundSource
      end
    end

    it "cannot be manually instantiated" do
      proc { MySoundSource.new }.must_raise RuntimeError
    end

    it "cannot be manually instantiated if allocate is redefined" do
      def MySoundSource.allocate
        raise TypeError
      end
      proc { MySoundSource.new }.must_raise RuntimeError
    end

    it "cannot be manually instantiated if allocate is undefined in the singleton class" do
      class << MySoundSource
        undef allocate
      end
      proc { MySoundSource.new }.must_raise RuntimeError
    end
  end
end
