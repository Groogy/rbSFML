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

#ifndef SYSTEM_VECTOR2_HPP
#define SYSTEM_VECTOR2_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "SFML.hpp"

#include <SFML/System/Vector2.hpp>

namespace rbVector2
{
    static inline int Type( VALUE aVector2 );
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( const sf::Vector2i& aVector2 );
	static inline VALUE ToRuby( const sf::Vector2u& aVector2 );
    static inline VALUE ToRuby( const sf::Vector2f& aVector2 );
    static inline sf::Vector2i ToSFMLi( VALUE aVector2 );
	static inline sf::Vector2u ToSFMLu( VALUE aVector2 );
    static inline sf::Vector2f ToSFMLf( VALUE aVector2 );

    static inline VALUE GetX( VALUE aVector2 );
    static inline VALUE GetY( VALUE aVector2 );
    static inline void SetX( VALUE aVector2, VALUE aValue );
    static inline void SetY( VALUE aVector2, VALUE aValue );

#if defined( SYSTEM_VECTOR2_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_SYSTEM )
    void Init( VALUE SFML );
#endif

#if defined( SYSTEM_VECTOR2_CPP )
    // Vector2#initialize
    // Vector2#initialize( vector2 )
    // Vector2#initialize( x, y )
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Vector2#initialize_copy( vector2 )
    static VALUE InitializeCopy( VALUE aSelf, VALUE aVector2 );

    // Vector2#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Vector2#marshal_load( data )
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // Vector2#coerce( other )
    static VALUE Coerce( VALUE aSelf, VALUE anOther );

    // Vector2#-@
    static VALUE Negate( VALUE aSelf );

    // Vector2#+(other)
    static VALUE Add( VALUE aSelf, VALUE anOther );

    // Vector2#-(other)
    static VALUE Subtract( VALUE aSelf, VALUE anOther );

    // Vector2#*(other)
    static VALUE Multiply( VALUE aSelf, VALUE anOther );

    // Vector2#/(other)
    static VALUE Divide( VALUE aSelf, VALUE anOther );

    // Vector2#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Vector2#eql?(other)
    // Vector2#equal?(other)
    static VALUE StrictEqual( VALUE aSelf, VALUE anOther );

    // Vector2#inspect
    // Vector2#to_s
    static VALUE Inspect( VALUE aSelf );

#endif

}

int rbVector2::Type( VALUE aVector2 )
{
    // T_FIXNUM or T_FLOAT
    return rb_type( GetX( aVector2 ) );
}

VALUE rbVector2::ToRuby( VALUE anOther )
{
    if( rb_obj_is_kind_of( anOther, rbVector2::Class ) )
        return anOther;

    if( rb_obj_is_kind_of( anOther, rb_cNumeric ) )
    {
        VALUE array[] = { anOther, anOther };
        return rb_class_new_instance( 2, array, rbVector2::Class );
    }

    if(rb_type( anOther ) == T_ARRAY)
        return rb_class_new_instance( static_cast< int >( RARRAY_LEN( anOther ) ), RARRAY_PTR( anOther ),
                                      rbVector2::Class );

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbVector2::Class ) );
}

VALUE rbVector2::ToRuby( const sf::Vector2i& aVector2 )
{
    VALUE x = INT2FIX( aVector2.x );
    VALUE y = INT2FIX( aVector2.y );
    VALUE array[] = { x, y };
    return rb_class_new_instance( 2, array, rbVector2::Class );
}

VALUE rbVector2::ToRuby( const sf::Vector2u& aVector2 )
{
    VALUE x = INT2FIX( aVector2.x );
    VALUE y = INT2FIX( aVector2.y );
    VALUE array[] = { x, y };
    return rb_class_new_instance( 2, array, rbVector2::Class );
}

VALUE rbVector2::ToRuby( const sf::Vector2f& aVector2 )
{
    VALUE x = rb_float_new( aVector2.x );
    VALUE y = rb_float_new( aVector2.y );
    VALUE array[] = { x, y };
    return rb_class_new_instance( 2, array, rbVector2::Class );
}

sf::Vector2i rbVector2::ToSFMLi( VALUE aVector2 )
{
    aVector2 = ToRuby( aVector2 );
    int x = NUM2INT( GetX( aVector2 ) );
    int y = NUM2INT( GetY( aVector2 ) );
    return sf::Vector2i( x, y );
}

sf::Vector2u rbVector2::ToSFMLu( VALUE aVector2 )
{
    aVector2 = ToRuby( aVector2 );
    unsigned int x = NUM2UINT( GetX( aVector2 ) );
    unsigned int y = NUM2UINT( GetY( aVector2 ) );
    return sf::Vector2u( x, y );
}

sf::Vector2f rbVector2::ToSFMLf( VALUE aVector2 )
{
    aVector2 = ToRuby( aVector2 );
    float x = NUM2DBL( GetX( aVector2 ) );
    float y = NUM2DBL( GetY( aVector2 ) );
    return sf::Vector2f( x, y );
}

VALUE rbVector2::GetX( VALUE aVector2 )
{
    return rb_iv_get( aVector2, "@x" );
}

VALUE rbVector2::GetY( VALUE aVector2 )
{
    return rb_iv_get( aVector2, "@y" );
}

void rbVector2::SetX(VALUE aVector2, VALUE aValue )
{
    rb_check_frozen( aVector2 );
    rb_iv_set( aVector2, "@x", aValue );
}

void rbVector2::SetY( VALUE aVector2, VALUE aValue )
{
    rb_check_frozen( aVector2 );
    rb_iv_set( aVector2, "@y", aValue );
}

#endif // SYSTEM_VECTOR2_HPP
