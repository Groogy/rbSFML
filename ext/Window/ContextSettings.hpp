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
#endif
    
#if defined(WINDOW_CONTEXTSETTINGS_CPP)
    // ContextSettings#initialize(...)
    static VALUE Initialize(int argc, VALUE args[], VALUE self);
    
    // ContextSettings#depth_bits
    // ContextSettings#DepthBits
    static VALUE GetDepthBits(VALUE self);
    
    // ContextSettings#stencil_bits
    // ContextSettings#StencilBits
    static VALUE GetStencilBits(VALUE self);
    
    // ContextSettings#antialiasing_level
    // ContextSettings#AntialiasingLevel
    static VALUE GetAntialiasingLevel(VALUE self);
    
    // ContextSettings#major_version
    // ContextSettings#MajorVersion
    static VALUE GetMajorVersion(VALUE self);
    
    // ContextSettings#minor_version
    // ContextSettings#MinorVersion
    static VALUE GetMinorVersion(VALUE self);
    
    // ContextSettings#depth_bits=(value)
    // ContextSettings#DepthBits=(value)
    static VALUE SetDepthBits(VALUE self, VALUE value);
    
    // ContextSettings#stencil_bits=(value)
    // ContextSettings#StencilBits=(value)
    static VALUE SetStencilBits(VALUE self, VALUE value);
    
    // ContextSettings#antialiasing_level=(value)
    // ContextSettings#AntialiasingLevel=(value)
    static VALUE SetAntialiasingLevel(VALUE self, VALUE value);
    
    // ContextSettings#major_version=(value)
    // ContextSettings#MajorVersion=(value)
    static VALUE SetMajorVersion(VALUE self, VALUE value);
    
    // ContextSettings#minor_version=(value)
    // ContextSettings#MinorVersion=(value)
    static VALUE SetMinorVersion(VALUE self, VALUE value);
    
    // ContextSettings#==(other)
    // ContextSettings#eql?(other)
    // ContextSettings#equal?(other)
    static VALUE Equal(VALUE self, VALUE other);
    
    // ContextSettings#inspect
    // ContextSettings#to_s
    static VALUE Inspect(VALUE self);
    
    // ContextSettings#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif
    
}

void rbContextSettings::Free(void* settings)
{
    delete (sf::ContextSettings*)settings;
}

VALUE rbContextSettings::Allocate(VALUE)
{
    sf::ContextSettings* settings = new(std::nothrow) sf::ContextSettings;
    if (settings == NULL) rb_memerror();
    return ToRuby(settings);
}

static int ToRubyHashIterator(VALUE key, VALUE value, VALUE extra)
{
    sf::ContextSettings* settings = (sf::ContextSettings*)extra;
    
    char* sym;
    if (rb_type(key) == T_SYMBOL)
        sym = RSTRING_PTR(rb_sym_to_s(key));
    else
        sym = RSTRING_PTR(StringValue(key));
    
    if (strcmp(sym, "depth_bits") or strcmp(sym, "DepthBits"))
        settings->DepthBits = NUM2UINT(value);
    else if (strcmp(sym, "stencil_bits") or strcmp(sym, "StencilBits"))
        settings->StencilBits = NUM2UINT(value);
    else if (strcmp(sym, "antialiasing_level") or strcmp(sym, "AntialiasingLevel"))
        settings->AntialiasingLevel = NUM2UINT(value);
    else if (strcmp(sym, "major_version") or strcmp(sym, "MajorVersion"))
        settings->MajorVersion = NUM2UINT(value);
    else if (strcmp(sym, "minor_version") or strcmp(sym, "MinorVersion"))
        settings->MinorVersion = NUM2UINT(value);
    else
        rb_raise(rb_eArgError,
                 "unknown attribute %s for ContextSettings", sym);
                 
    return ST_CONTINUE;
}

VALUE rbContextSettings::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, ContextSettings))
    {
        return other;
    }
    else if (rb_type(other) == T_HASH)
    {
        sf::ContextSettings* settings = new(std::nothrow) sf::ContextSettings;
        if (settings == NULL) rb_memerror();
        rb_hash_foreach(other, (int(*)(...))ToRubyHashIterator, (VALUE)settings);  
        return ToRuby(settings);
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
