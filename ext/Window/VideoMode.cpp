/* rbSFML - Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any
 *    source distribution.
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
    rb_define_alias(sVideoMode, "GetDesktopMode",       "desktop_mode"    );
    rb_define_alias(sVideoMode, "get_desktop_mode",     "desktop_mode"    );
    rb_define_alias(sVideoMode, "GetFullscreenModes",   "fullscreen_modes");
    rb_define_alias(sVideoMode, "get_fullscreen_modes", "fullscreen_modes");
    
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
    rb_define_alias(VideoMode, "to_str",          "inspect" );
}

VALUE rbVideoMode::GetDesktopMode(VALUE)
{
    VALUE video_mode = Allocate(VideoMode);
    *ToSFML(video_mode) = sf::VideoMode::GetDesktopMode();
    return video_mode;
}

VALUE rbVideoMode::GetFullscreenModes(VALUE)
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::GetFullscreenModes();
    VALUE ary = rb_ary_new2(modes.size());
    for (size_t i = 0; i < modes.size(); ++i)
    {
        VALUE video_mode = Allocate(VideoMode);
        *ToSFML(video_mode) = modes[i];
        rb_ary_push(ary, video_mode);
    }
    return ary;
}

VALUE rbVideoMode::Initialize(int argc, VALUE argv[], VALUE self)
{
    sf::VideoMode *video_mode = ToSFML(self);
    video_mode->BitsPerPixel = 32;
  
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
        case 3:
            VALIDATE_CLASS(argv[2], rb_cFixnum, FIXNUM_P(argv[2]));
            video_mode->BitsPerPixel = FIX2INT(argv[2]);
        case 2:
            VALIDATE_CLASS(argv[0], rb_cFixnum, FIXNUM_P(argv[0]));
            VALIDATE_CLASS(argv[1], rb_cFixnum, FIXNUM_P(argv[1]));
            video_mode->Width = FIX2INT(argv[0]);
            video_mode->Height = FIX2INT(argv[1]);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..3)", argc);
    }
}

VALUE rbVideoMode::InitializeCopy(VALUE self, VALUE video_mode)
{
    *ToSFML(self) = *ToSFML(video_mode);
    return self;
}

VALUE rbVideoMode::IsValid(VALUE self)
{
    return ToSFML(self)->IsValid() ? Qtrue : Qfalse;
}

VALUE rbVideoMode::GetWidth(VALUE self)
{
    return INT2FIX(ToSFML(self)->Width);
}

VALUE rbVideoMode::GetHeight(VALUE self)
{
    return INT2FIX(ToSFML(self)->Height);
}

VALUE rbVideoMode::GetBitsPerPixel(VALUE self)
{
    return INT2FIX(ToSFML(self)->BitsPerPixel);
}

VALUE rbVideoMode::SetWidth(VALUE self, VALUE value)
{
    ToSFML(self)->Width = FIX2INT(value);
}

VALUE rbVideoMode::SetHeight(VALUE self, VALUE value)
{
    ToSFML(self)->Height = FIX2INT(value);
}

VALUE rbVideoMode::SetBitsPerPixel(VALUE self, VALUE value)
{
    ToSFML(self)->BitsPerPixel = FIX2INT(value);
}

VALUE rbVideoMode::Compare(VALUE self, VALUE other)
{
    sf::VideoMode* vm1 = ToSFML(self);
    sf::VideoMode* vm2 = ToSFML(other);
    if (*vm1 == *vm2) return INT2FIX(0);
    if (*vm1 > *vm2) return INT2FIX(1);
    return INT2FIX(-1);
}

VALUE rbVideoMode::Inspect(VALUE self)
{
    VALUE result = rb_str_new2("VideoMode(");
    rb_str_append(result, rb_inspect(GetWidth(self)));
    rb_str_append(result, rb_str_new2("x"));
    rb_str_append(result, rb_inspect(GetHeight(self)));
    rb_str_append(result, rb_str_new2(", "));
    rb_str_append(result, rb_inspect(GetBitsPerPixel(self)));
    rb_str_append(result, rb_str_new2("bits)"));
    return result;
}

VALUE rbVideoMode::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::VideoMode));
}
