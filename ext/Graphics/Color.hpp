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

#ifndef GRAPHICS_COLOR_HPP
#define GRAPHICS_COLOR_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/Color.hpp>

namespace rbColor
{
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( const sf::Color& aColor );
    static inline sf::Color ToSFML( VALUE aColor );

    static inline VALUE GetRed( VALUE aColor );
    static inline VALUE GetGreen( VALUE aCoor );
    static inline VALUE GetBlue( VALUE aColor );
	static inline VALUE GetAlpha( VALUE aColor );
    static inline void SetRed( VALUE aColor, VALUE aValue );
    static inline void SetGreen( VALUE aColor, VALUE aValue );
    static inline void SetBlue( VALUE aColor, VALUE aValue );
	static inline void SetAlpha( VALUE aColor, VALUE aValue );

#if defined( GRAPHICS_COLOR_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_COLOR_CPP )
    // Color#initialize
    // Color#initialize( color )
    // Color#initialize( red, green, blue, alpha = 255 )
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Color#initialize_copy( color )
    static VALUE InitializeCopy( VALUE aSelf, VALUE aColor );

    // Color#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Color#marshal_load( data )
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // Color#+(other)
    static VALUE Add( VALUE aSelf, VALUE anOther );

    // Color#*(other)
    static VALUE Multiply( VALUE aSelf, VALUE anOther );

    // Color#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Color#inspect
    // Color#to_s
    static VALUE Inspect( VALUE aSelf );
    
#endif

}

VALUE rbColor::ToRuby( VALUE anOther )
{
    if(rb_obj_is_kind_of( anOther, rbColor::Class ) )
        return anOther;

    if( rb_obj_is_kind_of( anOther, rb_cNumeric ) )
    {
        VALUE array[] = { anOther, anOther, anOther };
        return rb_class_new_instance( 3, array, rbColor::Class );
    }

    if( rb_type( anOther ) == T_ARRAY )
        return rb_class_new_instance( RARRAY_LEN( anOther ), RARRAY_PTR( anOther ),
                                      rbColor::Class );

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbColor::Class ) );
}

VALUE rbColor::ToRuby( const sf::Color& aColor )
{
    VALUE r = INT2FIX( aColor.r );
    VALUE g = INT2FIX( aColor.g );
    VALUE b = INT2FIX( aColor.b );
	VALUE a = INT2FIX( aColor.a );
    VALUE array[] = { r, g, b, a };
    return rb_class_new_instance( 4, array, rbColor::Class );
}

sf::Color rbColor::ToSFML( VALUE aColor )
{
    aColor = rbColor::ToRuby( aColor );
    sf::Uint8 r = NUM2CHR( GetRed( aColor ) );
    sf::Uint8 g = NUM2CHR( GetGreen( aColor ) );
    sf::Uint8 b = NUM2CHR( GetBlue( aColor ) );
	sf::Uint8 a = NUM2CHR( GetAlpha( aColor ) );
    return sf::Color( r, g, b, a );
}

VALUE rbColor::GetRed( VALUE aColor )
{
    return rb_iv_get( aColor, "@r" );
}

VALUE rbColor::GetGreen( VALUE aColor )
{
    return rb_iv_get( aColor, "@g" );
}

VALUE rbColor::GetBlue( VALUE aColor )
{
    return rb_iv_get( aColor, "@b" );
}

VALUE rbColor::GetAlpha( VALUE aColor )
{
    return rb_iv_get( aColor, "@a" );
}

void rbColor::SetRed( VALUE aColor, VALUE aValue )
{
    rb_check_frozen( aColor );
    rb_iv_set( aColor, "@r", aValue );
}

void rbColor::SetGreen( VALUE aColor, VALUE aValue )
{
    rb_check_frozen( aColor );
    rb_iv_set( aColor, "@g", aValue );
}

void rbColor::SetBlue( VALUE aColor, VALUE aValue )
{
    rb_check_frozen( aColor );
    rb_iv_set( aColor, "@b", aValue );
}

void rbColor::SetAlpha( VALUE aColor, VALUE aValue )
{
    rb_check_frozen( aColor );
    rb_iv_set( aColor, "@a", aValue );
}

#endif // GRAPHICS_COLOR_HPP
