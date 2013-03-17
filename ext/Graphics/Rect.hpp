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

#ifndef GRAPHICS_RECT_HPP
#define GRAPHICS_RECT_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace rbRect
{
    static inline int Type( VALUE aRect );
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( const sf::IntRect& aRect );
    static inline VALUE ToRuby( const sf::FloatRect& aRect );
    static inline sf::IntRect ToSFMLi( VALUE aRect );
    static inline sf::FloatRect ToSFMLf( VALUE aRect );

    static inline VALUE GetLeft( VALUE aRect );
    static inline VALUE GetTop( VALUE aRect );
    static inline VALUE GetWidth( VALUE aRect );
	static inline VALUE GetHeight( VALUE aRect );
    static inline void SetLeft( VALUE aRect, VALUE aValue );
    static inline void SetTop( VALUE aRect, VALUE aValue );
    static inline void SetWidth( VALUE aRect, VALUE aValue );
	static inline void SetHeight( VALUE aRect, VALUE aValue );

#if defined( GRAPHICS_RECT_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RECT_CPP )
    // Rect#initialize
    // Rect#initialize(rect)
	// Rect#initialize(position, size)
    // Rect#initialize(left, top, width, height)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Rect#initialize_copy(rect)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aRect );
	
	// Rect#contains?(x, y)
	// Rect#contains?(vector2)
	static VALUE Contains( int argc, VALUE* args, VALUE aSelf );
	
	// Rect#intersects?(rect)
	// Rect#intersects?(rect, intersection)
	static VALUE Intersects( int argc, VALUE* args, VALUE aSelf );

    // Rect#marshal_dump
    static VALUE MarshalDump(VALUE aSelf );

    // Rect#marshal_load(data)
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // Rect#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Rect#eql?(other)
    // Rect#equal?(other)
    static VALUE StrictEqual( VALUE aSelf, VALUE anOther );

    // Rect#inspect
    // Rect#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

int rbRect::Type( VALUE aRect )
{
    // T_FIXNUM or T_FLOAT
    return rb_type( GetLeft( aRect ) );
}

VALUE rbRect::ToRuby( VALUE anOther )
{
    if(rb_obj_is_kind_of( anOther, rbRect::Class ) )
        return anOther;

    if( rb_obj_is_kind_of( anOther, rb_cNumeric ) )
    {
        VALUE array[] = { anOther, anOther, anOther, anOther };
        return rb_class_new_instance( 4, array, rbRect::Class );
    }

    if( rb_type( anOther ) == T_ARRAY )
        return rb_class_new_instance( RARRAY_LEN( anOther ), RARRAY_PTR( anOther ),
                                      rbRect::Class );

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbRect::Class ) );
}

VALUE rbRect::ToRuby( const sf::IntRect& aRect )
{
    VALUE left = INT2FIX( aRect.left );
    VALUE top = INT2FIX( aRect.top );
    VALUE width = INT2FIX( aRect.width );
	VALUE height = INT2FIX( aRect.height );
    VALUE array[] = { left, top, width, height };
    return rb_class_new_instance( 4, array, rbRect::Class );
}

VALUE rbRect::ToRuby( const sf::FloatRect& aRect )
{
    VALUE left = rb_float_new( aRect.left );
    VALUE top = rb_float_new( aRect.top );
    VALUE width = rb_float_new( aRect.width );
	VALUE height = rb_float_new( aRect.height );
    VALUE array[] = { left, top, width, height };
    return rb_class_new_instance( 4, array, rbRect::Class );
}

sf::IntRect rbRect::ToSFMLi( VALUE aRect )
{
    aRect = ToRuby( aRect );
    int top = NUM2INT( GetLeft( aRect ) );
    int left = NUM2INT( GetTop( aRect ) );
    int width = NUM2INT( GetWidth( aRect ) );
	int height = NUM2INT( GetHeight( aRect ) );
    return sf::IntRect( top, left, width, height );
}

sf::FloatRect rbRect::ToSFMLf( VALUE aRect )
{
    aRect = ToRuby( aRect );
    float left = NUM2DBL( GetLeft( aRect ) );
    float top = NUM2DBL( GetTop( aRect ) );
    float width = NUM2DBL( GetWidth( aRect ) );
	float height = NUM2DBL( GetHeight( aRect ) );
    return sf::FloatRect( left, top, width, height );
}

VALUE rbRect::GetLeft( VALUE aRect )
{
    return rb_iv_get( aRect, "@left" );
}

VALUE rbRect::GetTop( VALUE aRect )
{
    return rb_iv_get( aRect, "@top" );
}

VALUE rbRect::GetWidth( VALUE aRect )
{
    return rb_iv_get( aRect, "@width" );
}

VALUE rbRect::GetHeight( VALUE aRect )
{
    return rb_iv_get( aRect, "@height" );
}

void rbRect::SetLeft( VALUE aRect, VALUE aValue )
{
    rb_check_frozen( aRect );
    rb_iv_set( aRect, "@left", aValue );
}

void rbRect::SetTop( VALUE aRect, VALUE aValue )
{
    rb_check_frozen( aRect );
    rb_iv_set( aRect, "@top", aValue );
}

void rbRect::SetWidth( VALUE aRect, VALUE aValue )
{
    rb_check_frozen( aRect );
    rb_iv_set( aRect, "@width", aValue );
}

void rbRect::SetHeight( VALUE aRect, VALUE aValue )
{
    rb_check_frozen( aRect );
    rb_iv_set( aRect, "@height", aValue );
}

#endif // GRAPHICS_RECT_HPP
