require 'minitest/autorun'
require 'sfml/audio'
include SFML

describe Sound do
  before do
    @sound = Sound.new
  end

  it "will create distinct instances" do
    sound = Sound.new
    @sound.wont_equal sound
  end

  describe "when loading sound buffers" do
    before do
      @sound_buffer = SoundBuffer.new
      @sound_buffer.load('test/canary.wav')
    end

    it "will be initially empty" do
      @sound.buffer.must_be_nil
    end

    it "will copy the reference of a loaded buffer" do
      @sound.buffer = @sound_buffer
      @sound_buffer.object_id.must_equal @sound.buffer.object_id
    end

    it "will keep its buffer contents if the referenced buffer is destroyed" do
      @sound.buffer = @sound_buffer
      dumped = Marshal.dump(@sound_buffer)
      @sound_buffer = nil
      GC.start
      @sound.buffer.must_equal Marshal.load(dumped)
    end
  end

  it "can't be marshalled" do
    proc { Marshal.dump(@sound) }.must_raise TypeError
  end

  it "will respond usefully when inspected" do
    @sound.inspect.must_match /^SFML::Sound\([0-9a-fx]+\)$/
  end

  describe "when subclassed" do
    it "will duplicate correctly" do
      class MySound < Sound
      end

      my_sound = MySound.new
      my_sound.class.must_equal my_sound.dup.class
    end
  end
end
