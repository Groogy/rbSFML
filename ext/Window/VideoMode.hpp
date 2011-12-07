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

#ifndef WINDOW_VIDEOMODE_HPP
#define WINDOW_VIDEOMODE_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/Window/VideoMode.hpp>

namespace rbVideoMode
{
    
    static inline void Free(void* video_mode);
    static inline VALUE Allocate(VALUE self);
    
    static inline VALUE ToRuby(VALUE other, VALUE klass=false);
    static inline VALUE ToRuby(sf::VideoMode* video_mode, VALUE klass=false);
    static inline sf::VideoMode* ToSFML(VALUE video_mode, VALUE klass=false);
    
#if defined(WINDOW_VIDEOMODE_CPP)
    VALUE VideoMode;
#else
    extern VALUE VideoMode;
#endif
    
#if defined(RBSFML_WINDOW)
    void Init(VALUE SFML);
#endif
    
#if defined(WINDOW_VIDEOMODE_CPP)
    // VideoMode::desktop_mode
    // VideoMode::GetDesktopMode
    static VALUE GetDesktopMode(VALUE self);
    
    // VideoMode::fullscreen_modes
    // VideoMode::GetFullscreenModes
    static VALUE GetFullscreenModes(VALUE self);
    
    // VideoMode#initialize
    static VALUE Initialize(int argc, VALUE args[], VALUE self);
    
    // VideoMode#initialize_copy(video_mode)
    static VALUE InitializeCopy(VALUE self, VALUE video_mode);
    
    // VideoMode#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // VideoMode#marshal_load(data)
    static VALUE MarshalLoad(VALUE self, VALUE data);
    
    // VideoMode#valid?
    // VideoMode#IsValid
    static VALUE IsValid(VALUE self);
    
    // VideoMode#width
    // VideoMode#Width
    static VALUE GetWidth(VALUE self);
    
    // VideoMode#height
    // VideoMode#Height
    static VALUE GetHeight(VALUE self);
    
    // VideoMode#bpp
    // VideoMode#BitsPerPixel
    // VideoMode#bits_per_pixel
    // VideoMode#bits
    static VALUE GetBitsPerPixel(VALUE self);
    
    // VideoMode#width=(value)
    // VideoMode#Width=(value)
    static VALUE SetWidth(VALUE self, VALUE value);
    
    // VideoMode#height=(value)
    // VideoMode#Height=(value)
    static VALUE SetHeight(VALUE self, VALUE value);
    
    // VideoMode#bpp=(value)
    // VideoMode#BitsPerPixel=(value)
    // VideoMode#bits_per_pixel=(value)
    // VideoMode#bits=(value)
    static VALUE SetBitsPerPixel(VALUE self, VALUE value);
    
    // VideoMode#<=>(other)
    static VALUE Compare(VALUE self, VALUE other);
    
    // VideoMode#inspect
    // VideoMode#to_s
    static VALUE Inspect(VALUE self);
    
    // VideoMode#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif
    
}

void rbVideoMode::Free(void* video_mode)
{
    delete (sf::VideoMode*)video_mode;
}

VALUE rbVideoMode::Allocate(VALUE self)
{
    sf::VideoMode* video_mode = new(std::nothrow) sf::VideoMode;
    if (video_mode == NULL) rb_memerror();
    return ToRuby(video_mode, self);
} 

VALUE rbVideoMode::ToRuby(VALUE other, VALUE klass)
{
    if (!klass)
        klass = VideoMode;
    
    if (rb_obj_is_kind_of(other, VideoMode))
        return other;
    
    if (rb_type(other) == T_ARRAY)
        return rb_class_new_instance(RARRAY_LEN(other), RARRAY_PTR(other),
                                     klass);
    
    rb_raise(rb_eTypeError, "can't convert %s into %s",
             rb_obj_classname(other), rb_class2name(klass));
}

VALUE rbVideoMode::ToRuby(sf::VideoMode* video_mode, VALUE klass)
{
    if (!klass)
        klass = VideoMode;
    
    return rb_data_object_alloc(klass, video_mode, NULL, Free);
}

sf::VideoMode* rbVideoMode::ToSFML(VALUE video_mode, VALUE klass)
{
    video_mode = ToRuby(video_mode, klass);
    return (sf::VideoMode*)DATA_PTR(video_mode);
}

#endif // WINDOW_VIDEOMODE_HPP
