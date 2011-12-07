/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#define WINDOW_VIDEOMODE_CPP
#include "VideoMode.hpp"

void rbVideoMode::Init(VALUE SFML)
{
    VideoMode = rb_define_class_under(SFML, "VideoMode", rb_cObject);
    rb_include_module(VideoMode, rb_mComparable);
    
    // Class methods
    rb_define_alloc_func(VideoMode, Allocate);
    rb_define_singleton_method(VideoMode, "desktop_mode",     GetDesktopMode,     0);
    rb_define_singleton_method(VideoMode, "fullscreen_modes", GetFullscreenModes, 0);
    
    // Instance methods
    rb_define_method(VideoMode, "initialize",      Initialize,     -1);
    rb_define_method(VideoMode, "initialize_copy", InitializeCopy,  1);
    rb_define_method(VideoMode, "marshal_dump",    MarshalDump,     0);
    rb_define_method(VideoMode, "marshal_load",    MarshalLoad,     1);
    rb_define_method(VideoMode, "valid?",          IsValid,         0);
    rb_define_method(VideoMode, "width",           GetWidth,        0);
    rb_define_method(VideoMode, "height",          GetHeight,       0);
    rb_define_method(VideoMode, "bpp",             GetBitsPerPixel, 0);
    rb_define_method(VideoMode, "width=",          SetWidth,        1);
    rb_define_method(VideoMode, "height=",         SetHeight,       1);
    rb_define_method(VideoMode, "bpp=",            SetBitsPerPixel, 1);
    rb_define_method(VideoMode, "<=>",             Compare,         1);
    rb_define_method(VideoMode, "inspect",         Inspect,         0);
    rb_define_method(VideoMode, "memory_usage",    GetMemoryUsage,  0);
    
    // Class aliasses
    VALUE sVideoMode = rb_singleton_class(VideoMode);
    rb_define_alias(sVideoMode, "GetDesktopMode",     "desktop_mode"    );
    rb_define_alias(sVideoMode, "GetFullscreenModes", "fullscreen_modes");
    
    // Instance aliasses
    rb_define_alias(VideoMode, "IsValid",         "valid?"  );
    rb_define_alias(VideoMode, "Width",           "width"   );
    rb_define_alias(VideoMode, "Height",          "height"  );
    rb_define_alias(VideoMode, "BitsPerPixel",    "bpp"     );
    rb_define_alias(VideoMode, "bits_per_pixel",  "bpp"     );
    rb_define_alias(VideoMode, "bits",            "bpp"     );
    rb_define_alias(VideoMode, "Width=",          "width="  );
    rb_define_alias(VideoMode, "Height=",         "height=" );
    rb_define_alias(VideoMode, "BitsPerPixel=",   "bpp="    );
    rb_define_alias(VideoMode, "bits_per_pixel=", "bpp="    );
    rb_define_alias(VideoMode, "bits=",           "bpp="    );
    rb_define_alias(VideoMode, "eql?",            "=="      );
    rb_define_alias(VideoMode, "equal?",          "=="      );
    rb_define_alias(VideoMode, "to_s",            "inspect" );
}

// VideoMode::desktop_mode
// VideoMode::GetDesktopMode
VALUE rbVideoMode::GetDesktopMode(VALUE self)
{
    VALUE video_mode = Allocate(self);
    *ToSFML(video_mode) = sf::VideoMode::GetDesktopMode();
    return video_mode;
}

// VideoMode::fullscreen_modes
// VideoMode::GetFullscreenModes
VALUE rbVideoMode::GetFullscreenModes(VALUE self)
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::GetFullscreenModes();
    VALUE ary = rb_ary_new2(modes.size());
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        VALUE video_mode = Allocate(self);
        *ToSFML(video_mode) = modes[i];
        rb_ary_push(ary, video_mode);
    }
    return ary;
}

// VideoMode#initialize
VALUE rbVideoMode::Initialize(int argc, VALUE argv[], VALUE self)
{
    sf::VideoMode* video_mode = ToSFML(self);
  
    switch(argc)
    {
        case 0:
            video_mode->Width = 0;
            video_mode->Height = 0;
            video_mode->BitsPerPixel = 0;
            break;
        case 1:
            InitializeCopy(self, ToRuby(argv[0]));
            break;
        case 2:
            video_mode->Width = NUM2UINT(argv[0]);
            video_mode->Height = NUM2UINT(argv[1]);
            video_mode->BitsPerPixel = 32;
            break;
        case 3:
            video_mode->Width = NUM2UINT(argv[0]);
            video_mode->Height = NUM2UINT(argv[1]);
            video_mode->BitsPerPixel = NUM2UINT(argv[2]);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..3)", argc);
    }
    
    return Qnil;
}

// VideoMode#initialize_copy(video_mode)
VALUE rbVideoMode::InitializeCopy(VALUE self, VALUE video_mode)
{
    *ToSFML(self) = *ToSFML(video_mode);
    return self;
}

// VideoMode#marshal_dump
VALUE rbVideoMode::MarshalDump(VALUE self)
{
    sf::VideoMode* video_mode = ToSFML(self);
    
    VALUE ptr[3];
    ptr[0] = UINT2NUM(video_mode->Width);
    ptr[1] = UINT2NUM(video_mode->Height);
    ptr[2] = UINT2NUM(video_mode->BitsPerPixel);
    return rb_ary_new4(3, ptr);
}

// VideoMode#marshal_load(data)
VALUE rbVideoMode::MarshalLoad(VALUE self, VALUE data)
{
    sf::VideoMode* video_mode = ToSFML(self);
    
    VALUE* ptr = RARRAY_PTR(data);
    video_mode->Width        = NUM2UINT(ptr[0]);
    video_mode->Height       = NUM2UINT(ptr[1]);
    video_mode->BitsPerPixel = NUM2UINT(ptr[2]);
    return Qnil;
}

// VideoMode#valid?
// VideoMode#IsValid
VALUE rbVideoMode::IsValid(VALUE self)
{
    return RBOOL(ToSFML(self)->IsValid());
}

// VideoMode#width
// VideoMode#Width
VALUE rbVideoMode::GetWidth(VALUE self)
{
    return UINT2NUM(ToSFML(self)->Width);
}

// VideoMode#height
// VideoMode#Height
VALUE rbVideoMode::GetHeight(VALUE self)
{
    return UINT2NUM(ToSFML(self)->Height);
}

// VideoMode#bpp
// VideoMode#BitsPerPixel
// VideoMode#bits_per_pixel
// VideoMode#bits
VALUE rbVideoMode::GetBitsPerPixel(VALUE self)
{
    return UINT2NUM(ToSFML(self)->BitsPerPixel);
}

// VideoMode#width=(value)
// VideoMode#Width=(value)
VALUE rbVideoMode::SetWidth(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->Width = NUM2UINT(value);
    return Qnil;
}

// VideoMode#height=(value)
// VideoMode#Height=(value)
VALUE rbVideoMode::SetHeight(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->Height = NUM2UINT(value);
    return Qnil;
}

// VideoMode#bpp=(value)
// VideoMode#BitsPerPixel=(value)
// VideoMode#bits_per_pixel=(value)
// VideoMode#bits=(value)
VALUE rbVideoMode::SetBitsPerPixel(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->BitsPerPixel = NUM2UINT(value);
    return Qnil;
}

// VideoMode#<=>(other)
VALUE rbVideoMode::Compare(VALUE self, VALUE other)
{
    sf::VideoMode* vm1 = ToSFML(self);
    sf::VideoMode* vm2 = ToSFML(other, CLASS_OF(self));
    if (*vm1 == *vm2) return INT2FIX(0);
    if (*vm1 > *vm2) return INT2FIX(1);
    return INT2FIX(-1);
}

// VideoMode#inspect
// VideoMode#to_s
VALUE rbVideoMode::Inspect(VALUE self)
{
    sf::VideoMode* video_mode = ToSFML(self);
    return rb_sprintf("%s(%ux%u, %u-bits)",
                      rb_obj_classname(self),
                      video_mode->Width,
                      video_mode->Height,
                      video_mode->BitsPerPixel);
}

// VideoMode#memory_usage
VALUE rbVideoMode::GetMemoryUsage(VALUE self)
{
    return SIZET2NUM(sizeof(sf::VideoMode));
}