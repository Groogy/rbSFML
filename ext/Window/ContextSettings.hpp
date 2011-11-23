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

#ifndef WINDOW_CONTEXTSETTINGS_HPP
#define WINDOW_CONTEXTSETTINGS_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/Window/ContextSettings.hpp>

namespace rbContextSettings
{
    
    static inline void Free(void* settings);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::ContextSettings* settings);
    static inline VALUE ToRuby(sf::ContextSettings& settings);
    static inline sf::ContextSettings* ToSFML(VALUE settings);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(WINDOW_CONTEXTSETTINGS_CPP)
    VALUE ContextSettings;
#else
    extern VALUE ContextSettings;
#endif
    
#if defined(RBSFML_WINDOW) || defined(RBSFML_SFML)
    
    void Init(VALUE SFML);
    
    // ContextSettings#initialize
    static VALUE Initialize(int argc, VALUE args[], VALUE self);
    
    // ContextSettings#depth_bits
    static VALUE GetDepthBits(VALUE self);
    
    // ContextSettings#stencil_bits
    static VALUE GetStencilBits(VALUE self);
    
    // ContextSettings#antialiasing_level
    static VALUE GetAntialiasingLevel(VALUE self);
    
    // ContextSettings#major_version
    static VALUE GetMajorVersion(VALUE self);
    
    // ContextSettings#minor_version
    static VALUE GetMinorVersion(VALUE self);
    
    // ContextSettings#depth_bits=(value)
    static VALUE SetDepthBits(VALUE self, VALUE value);
    
    // ContextSettings#stencil_bits=(value)
    static VALUE SetStencilBits(VALUE self, VALUE value);
    
    // ContextSettings#antialiasing_level=(value)
    static VALUE SetAntialiasingLevel(VALUE self, VALUE value);
    
    // ContextSettings#major_version=(value)
    static VALUE SetMajorVersion(VALUE self, VALUE value);
    
    // ContextSettings#minor_version=(value)
    static VALUE SetMinorVersion(VALUE self, VALUE value);

#endif
    
}

void rbContextSettings::Free(void* settings)
{
    delete (sf::ContextSettings*)settings;
}

VALUE rbContextSettings::Allocate(VALUE)
{
    sf::ContextSettings* video_mode = new(std::nothrow) sf::ContextSettings;
    if (video_mode == NULL) rb_memerror();
    return ToRuby(video_mode);
}

VALUE rbContextSettings::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, ContextSettings))
    {
        return other;
    }
    else
    {
        rb_raise(rb_eTypeError,
                 "can't convert %s into ContextSettings", rb_obj_classname(other));
    }
}

VALUE rbContextSettings::ToRuby(sf::ContextSettings* settings)
{
    return rb_data_object_alloc(ContextSettings, settings, NULL, Free);
}

VALUE rbContextSettings::ToRuby(sf::ContextSettings& settings)
{
    return rb_data_object_alloc(ContextSettings, &settings, NULL, NULL);
}

sf::ContextSettings* rbContextSettings::ToSFML(VALUE settings)
{
    settings = ToRuby(settings);
    return (sf::ContextSettings*)DATA_PTR(settings);
}

#endif // WINDOW_CONTEXTSETTINGS_HPP
