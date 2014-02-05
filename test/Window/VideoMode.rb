require 'minitest/autorun'
require 'sfml/window'
include SFML

describe VideoMode do
  it "must be initialized with 0, 2, or 3 integer arguments" do
    proc { VideoMode.new(1000) }.must_raise TypeError
    proc { VideoMode.new("aaa", "bbb") }.must_raise TypeError
    proc { VideoMode.new(0, 0, 0, 0) }.must_raise ArgumentError
    VideoMode.new
    VideoMode.new(800, 600)
    VideoMode.new(800, 600, 32)
  end

  it "can be created with specific dimensions and bit depth" do
    video_mode = VideoMode.new(640, 480, 8)
    video_mode.width.must_equal 640
    video_mode.height.must_equal 480
    video_mode.bpp.must_equal 8
  end

  it "defaults to 32bpp" do
    video_mode = VideoMode.new(800, 600)
    video_mode.bpp.must_equal 32
    video_mode.must_equal VideoMode.new(800, 600, 32)
    video_mode.must_be_same_as VideoMode.new(800, 600)
  end

  it "can be constructed equivalently with an Array" do
    VideoMode.new(800, 600).must_equal VideoMode.new([800, 600])
    VideoMode.new(800, 600, 8).must_equal VideoMode.new([800, 600, 8])
    VideoMode.new.must_equal VideoMode.new([])
  end

  it "is an invalid mode by default and can be made valid afterwards" do
    video_mode = VideoMode.new
    video_mode.width.must_equal 0
    video_mode.height.must_equal 0
    video_mode.bpp.must_equal 0
    video_mode.wont_be :valid?

    video_mode.width = 544
    video_mode.height = 416
    video_mode.bpp = 24
    video_mode.width.must_equal 544
    video_mode.height.must_equal 416
    video_mode.bpp.must_equal 24
    video_mode.must_be :valid?
  end

  it "has built-in modes" do
    desktop_mode = VideoMode.desktop_mode
    desktop_mode.must_be_kind_of VideoMode

    VideoMode.fullscreen_modes.each do |mode|
      mode.must_be_kind_of VideoMode
      mode.must_be :valid?
    end
  end

  it "can be compared to other video modes by dimension" do
    video_mode1 = VideoMode.new(800, 600)
    video_mode2 = VideoMode.new(640, 480, 8)
    video_mode3 = VideoMode.new(640, 480, 32)
    video_mode4 = VideoMode.new(800, 600)
    video_mode1.must_be :>, video_mode2
    video_mode1.must_be :>, video_mode3
    video_mode1.must_be :>=, video_mode4
    video_mode1.must_be :<=, video_mode4
    video_mode1.must_be :==, video_mode4
    video_mode1.wont_be :<, video_mode2
    video_mode1.wont_be :<, video_mode3
    video_mode2.must_be :<, video_mode3
  end

  it "has useful string representations" do
    video_mode1 = VideoMode.new(800, 600)
    video_mode2 = VideoMode.new(640, 480, 8)
    video_mode1.inspect.must_equal "SFML::VideoMode(800x600, 32-bits)"
    video_mode2.inspect.must_equal "SFML::VideoMode(640x480, 8-bits)"
    video_mode1.to_s.must_equal video_mode1.inspect
    video_mode2.to_s.must_equal video_mode2.inspect
  end

  describe "when subclassed" do
    before do
      class MyVideoMode < VideoMode
      end

      @my_video_mode = MyVideoMode.new(800, 600)
    end

    it "can be used to initialize video modes and vice versa" do
      video_mode = VideoMode.new(@my_video_mode)
      video_mode.must_equal @my_video_mode
      @my_video_mode = MyVideoMode.new(video_mode)
      video_mode.must_equal @my_video_mode
    end

    it "can be duped" do
      @my_video_mode.dup.class.must_equal @my_video_mode.class
    end

    it "has a useful string representation" do
      @my_video_mode.inspect.must_equal "MyVideoMode(800x600, 32-bits)"
    end

    it "has built-in modes" do
      MyVideoMode.desktop_mode.must_be_kind_of MyVideoMode

      MyVideoMode.fullscreen_modes.each do |mode|
        mode.must_be_kind_of MyVideoMode
      end
    end
  end
end
