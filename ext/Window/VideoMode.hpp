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

#ifndef VIDEOMODE_HPP
#define VIDEOMODE_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/Window/VideoMode.hpp>

namespace rbVideoMode
{
    
    static inline void Free(void* clock);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::VideoMode* video_mode);
    static inline VALUE ToRuby(sf::VideoMode& video_mode);
    static inline sf::VideoMode* ToSFML(VALUE video_mode);
    
#if defined(VIDEOMODE_CPP)
    VALUE VideoMode;
#else
    extern VALUE VideoMode;
#endif
    
#if defined(RBSFML_WINDOW) || defined(RBSFML_SFML)
    
    void Init(VALUE SFML);
    
    // VideoMode.allocate
    static VALUE Allocate(VALUE);
    
    // VideoMode.desktop_mode
    static VALUE GetDesktopMode(VALUE self);
    
    // VideoMode.fullscreen_modes
    static VALUE GetFullscreenModes(VALUE self);
    
    // VideoMode#initialize
    static VALUE Initialize(int argc, VALUE args[], VALUE self);
    
    // VideoMode#initialize_copy
    static VALUE InitializeCopy(VALUE self, VALUE video_mode);
    
    // VideoMode#valid?
    static VALUE IsValid(VALUE self);
    
    // VideoMode#width
    static VALUE GetWidth(VALUE self);
    
    // VideoMode#height
    static VALUE GetHeight(VALUE self);
    
    // VideoMode#bits_per_pixel
    static VALUE GetBitsPerPixel(VALUE self);
    
    // VideoMode#width=(value)
    static VALUE SetWidth(VALUE self, VALUE value);
    
    // VideoMode#height=(value)
    static VALUE SetHeight(VALUE self, VALUE value);
    
    // VideoMode#bits_per_pixel=(value)
    static VALUE SetBitsPerPixel(VALUE self, VALUE value);
    
    // VideoMode#<=>(other)
    static VALUE Compare(VALUE self, VALUE other);
    
    // VideoMode#inspect
    static VALUE Inspect(VALUE self);
    
    // VideoMode#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
    
#endif
    
}

void rbVideoMode::Free(void* video_mode)
{
    delete (sf::VideoMode*)video_mode;
}

VALUE rbVideoMode::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, VideoMode))
    {
        return other;
    }
    else if (rb_type(other) == T_ARRAY)
    {
        VALUE* argv = RARRAY_PTR(other);
        return rb_class_new_instance(RARRAY_LEN(other), argv, VideoMode);
    }
    else
    {
        rb_raise(rb_eTypeError,
                 "can't convert %s into VideoMode", rb_obj_classname(other));
    }
}

VALUE rbVideoMode::ToRuby(sf::VideoMode* video_mode)
{
    return rb_data_object_alloc(VideoMode, video_mode, NULL, Free);
}

VALUE rbVideoMode::ToRuby(sf::VideoMode& video_mode)
{
    return rb_data_object_alloc(VideoMode, &video_mode, NULL, NULL);
}

sf::VideoMode* rbVideoMode::ToSFML(VALUE video_mode)
{
    return (sf::VideoMode*)DATA_PTR(video_mode);
}

#endif // VIDEOMODE_HPP
