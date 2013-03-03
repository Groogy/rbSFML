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
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( sf::VideoMode* aVideoMode );
    static inline sf::VideoMode* ToSFML( VALUE aVideoMode );
    
#if defined( WINDOW_VIDEOMODE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif
    
#if defined( RBSFML_WINDOW )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_VIDEOMODE_CPP)
    // VideoMode.desktop_mode
	// VideoMode.get_desktop_mode
    // VideoMode.getDesktopMode
    static VALUE GetDesktopMode( VALUE aSelf );
    
    // VideoMode.fullscreen_modes
	// VideoMode.get_fullscreen_modes
    // VideoMode.getFullscreenModes
    static VALUE GetFullscreenModes( VALUE aSelf );
    
    // VideoMode#initialize
    static VALUE Initialize( int argc, VALUE args[], VALUE aSelf );
    
    // VideoMode#initialize_copy(video_mode)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aVideoMode );
    
    // VideoMode#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // VideoMode#marshal_load(data)
    static VALUE MarshalLoad( VALUE aSelf, VALUE someData );
    
    // VideoMode#valid?
	// VideoMode#is_valid?
	// VideoMode#is_valid
    // VideoMode#isValid
    static VALUE IsValid( VALUE aSelf );
    
    // VideoMode#width
    static VALUE GetWidth( VALUE aSelf );
    
    // VideoMode#height
    static VALUE GetHeight( VALUE aSelf );
    
    // VideoMode#bpp
    // VideoMode#bitsPerPixel
    // VideoMode#bits_per_pixel
    // VideoMode#bits
    static VALUE GetBitsPerPixel( VALUE aSelf );
    
    // VideoMode#width=(value)
    static VALUE SetWidth( VALUE aSelf, VALUE aValue );
    
    // VideoMode#height=(value)
    static VALUE SetHeight( VALUE aSelf, VALUE aValue );
    
    // VideoMode#bpp=(value)
    // VideoMode#bitsPerPixel=(value)
    // VideoMode#bits_per_pixel=(value)
    // VideoMode#bits=(value)
    static VALUE SetBitsPerPixel( VALUE aSelf, VALUE aValue );
    
    // VideoMode#<=>(other)
    static VALUE Compare( VALUE aSelf, VALUE anOther );
    
    // VideoMode#inspect
    // VideoMode#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
    
}

VALUE rbVideoMode::ToRuby( VALUE anOther )
{    
    if( rb_obj_is_kind_of( anOther, rbVideoMode::Class ) )
        return anOther;
    
    if( rb_type( anOther ) == T_ARRAY )
        return rb_class_new_instance( RARRAY_LEN( anOther ), RARRAY_PTR( anOther ),
                                      rbVideoMode::Class );
    
    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbVideoMode::Class ) );
}

VALUE rbVideoMode::ToRuby( sf::VideoMode* aVideoMode )
{
    return rb_data_object_alloc( rbVideoMode::Class, aVideoMode, NULL, rbMacros::Free< sf::VideoMode > );
}

sf::VideoMode* rbVideoMode::ToSFML( VALUE aVideoMode )
{
    aVideoMode = rbVideoMode::ToRuby( aVideoMode );
    return static_cast< sf::VideoMode* >( DATA_PTR( aVideoMode ) );
}

#endif // WINDOW_VIDEOMODE_HPP
