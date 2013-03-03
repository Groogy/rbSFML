/* rbSFML
 * Copyright (c) 2012 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#ifndef GRAPHICS_GLYPH_HPP
#define GRAPHICS_GLYPH_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include "Rect.hpp"

#include <SFML/Graphics/Glyph.hpp>

namespace rbGlyph
{
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( const sf::Glyph& aGlyph );
    static inline sf::Glyph ToSFML( VALUE aGlyph );

    static inline VALUE GetAdvance( VALUE aGlyph );
	static inline VALUE GetBounds( VALUE aGlyph );
	static inline VALUE GetTextureRect( VALUE aGlyph );
	static inline void SetAdvance( VALUE aGlyph, VALUE aValue );
	static inline void SetBounds( VALUE aGlyph, VALUE aValue );
	static inline void SetTextureRect( VALUE aGlyph, VALUE aValue );

#if defined( GRAPHICS_GLYPH_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_GLYPH_CPP )
    // Glyph#initialize
    static VALUE Initialize( VALUE aSelf );

    // Glyph#initialize_copy(glyph)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aGlyph );
	
    // Glyph#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Glyph#marshal_load(data)
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // Glyph#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Glyph#inspect
    // Glyph#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

VALUE rbGlyph::ToRuby( VALUE anOther )
{
    if(rb_obj_is_kind_of( anOther, rbGlyph::Class ) )
        return anOther;

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbGlyph::Class ) );
}

VALUE rbGlyph::ToRuby( const sf::Glyph& aGlyph )
{
    VALUE advance = INT2FIX( aGlyph.advance );
    VALUE bounds = rbRect::ToRuby( aGlyph.bounds );
    VALUE textureRect = rbRect::ToRuby( aGlyph.textureRect );
    VALUE instance =  rb_class_new_instance( 0, NULL, rbGlyph::Class );
	rbGlyph::SetAdvance( instance, advance );
	rbGlyph::SetBounds( instance, bounds );
	rbGlyph::SetTextureRect( instance, textureRect );
	return instance;
}

sf::Glyph rbGlyph::ToSFML( VALUE aGlyph )
{
    aGlyph = ToRuby( aGlyph );
    int advance = NUM2INT( GetAdvance( aGlyph ) );
    sf::IntRect bounds = rbRect::ToSFMLi( GetBounds( aGlyph ) );
    sf::IntRect textureRect = rbRect::ToSFMLi( GetTextureRect( aGlyph ) );
    sf::Glyph glyph;
	glyph.advance = advance;
	glyph.bounds = bounds;
	glyph.textureRect = textureRect;
	return glyph;
}

VALUE rbGlyph::GetAdvance( VALUE aGlyph )
{
    return rb_iv_get( aGlyph, "@advance" );
}

VALUE rbGlyph::GetBounds( VALUE aGlyph )
{
    return rb_iv_get( aGlyph, "@bounds" );
}

VALUE rbGlyph::GetTextureRect( VALUE aGlyph )
{
    return rb_iv_get( aGlyph, "@texture_rect" );
}

void rbGlyph::SetAdvance( VALUE aGlyph, VALUE aValue )
{
    rb_check_frozen( aGlyph );
    rb_iv_set( aGlyph, "@advance", aValue );
}

void rbGlyph::SetBounds( VALUE aGlyph, VALUE aValue )
{
    rb_check_frozen( aGlyph );
    rb_iv_set( aGlyph, "@bounds", aValue );
}

void rbGlyph::SetTextureRect( VALUE aGlyph, VALUE aValue )
{
    rb_check_frozen( aGlyph );
    rb_iv_set( aGlyph, "@texture_rect", aValue );
}

#endif // GRAPHICS_GLYPH_HPP
