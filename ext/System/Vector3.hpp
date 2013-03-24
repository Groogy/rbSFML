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

#ifndef SYSTEM_VECTOR3_HPP
#define SYSTEM_VECTOR3_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "SFML.hpp"

#include <SFML/System/Vector3.hpp>

namespace rbVector3
{
    static inline int Type( VALUE aVector3 );
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( const sf::Vector3i& aVector3 );
    static inline VALUE ToRuby( const sf::Vector3f& aVector3 );
    static inline sf::Vector3i ToSFMLi( VALUE aVector3 );
    static inline sf::Vector3f ToSFMLf( VALUE aVector3 );

    static inline VALUE GetX( VALUE aVector3 );
    static inline VALUE GetY( VALUE aVector3 );
    static inline VALUE GetZ( VALUE aVector3 );
    static inline void SetX( VALUE aVector3, VALUE aValue );
    static inline void SetY( VALUE aVector3, VALUE aValue );
    static inline void SetZ( VALUE aVector3, VALUE aValue );

#if defined( SYSTEM_VECTOR3_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_SYSTEM )
    void Init( VALUE SFML );
#endif

#if defined( SYSTEM_VECTOR3_CPP )
    // Vector3#initialize
    // Vector3#initialize(vector3)
    // Vector3#initialize(x, y, z)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Vector3#initialize_copy(vector3)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aVector3 );

    // Vector3#marshal_dump
    static VALUE MarshalDump(VALUE aSelf );

    // Vector3#marshal_load(data)
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // Vector3#coerce(other)
    static VALUE Coerce( VALUE aSelf, VALUE anOther );

    // Vector3#-@
    static VALUE Negate( VALUE aSelf );

    // Vector3#+(other)
    static VALUE Add( VALUE aSelf, VALUE anOther );

    // Vector3#-(other)
    static VALUE Subtract( VALUE aSelf, VALUE anOther );

    // Vector3#*(other)
    static VALUE Multiply( VALUE aSelf, VALUE anOther );

    // Vector3#/(other)
    static VALUE Divide( VALUE aSelf, VALUE anOther );

    // Vector3#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Vector3#eql?(other)
    // Vector3#equal?(other)
    static VALUE StrictEqual( VALUE aSelf, VALUE anOther );

    // Vector3#inspect
    // Vector3#to_s
    static VALUE Inspect( VALUE aSelf );

#endif

}

int rbVector3::Type( VALUE aVector3 )
{
    // T_FIXNUM or T_FLOAT
    return rb_type( GetX( aVector3 ) );
}

VALUE rbVector3::ToRuby( VALUE anOther )
{
    if(rb_obj_is_kind_of( anOther, rbVector3::Class ) )
        return anOther;

    if( rb_obj_is_kind_of( anOther, rb_cNumeric ) )
    {
        VALUE array[] = { anOther, anOther, anOther };
        return rb_class_new_instance( 3, array, rbVector3::Class );
    }

    if( rb_type( anOther ) == T_ARRAY )
        return rb_class_new_instance( static_cast< int >( RARRAY_LEN( anOther ) ), RARRAY_PTR( anOther ),
                                      rbVector3::Class );

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbVector3::Class ));
}

VALUE rbVector3::ToRuby( const sf::Vector3i& aVector3 )
{
    VALUE x = INT2FIX( aVector3.x );
    VALUE y = INT2FIX( aVector3.y );
    VALUE z = INT2FIX( aVector3.z );
    VALUE array[] = { x, y, z };
    return rb_class_new_instance( 3, array, rbVector3::Class );
}

VALUE rbVector3::ToRuby( const sf::Vector3f& aVector3 )
{
    VALUE x = rb_float_new( aVector3.x );
    VALUE y = rb_float_new( aVector3.y );
    VALUE z = rb_float_new( aVector3.z );
    VALUE array[] = { x, y, z };
    return rb_class_new_instance( 3, array, rbVector3::Class );
}

sf::Vector3i rbVector3::ToSFMLi( VALUE aVector3 )
{
    aVector3 = ToRuby( aVector3 );
    int x = NUM2INT( GetX( aVector3 ) );
    int y = NUM2INT( GetY( aVector3 ) );
    int z = NUM2INT( GetZ( aVector3 ) );
    return sf::Vector3i( x, y, z );
}

sf::Vector3f rbVector3::ToSFMLf( VALUE aVector3 )
{
    aVector3 = ToRuby( aVector3 );
    float x = NUM2DBL( GetX( aVector3 ) );
    float y = NUM2DBL( GetY( aVector3 ) );
    float z = NUM2DBL( GetZ( aVector3 ) );
    return sf::Vector3f( x, y, z );
}

VALUE rbVector3::GetX( VALUE aVector3 )
{
    return rb_iv_get( aVector3, "@x" );
}

VALUE rbVector3::GetY( VALUE aVector3 )
{
    return rb_iv_get( aVector3, "@y" );
}

VALUE rbVector3::GetZ( VALUE  aVector3 )
{
    return rb_iv_get( aVector3, "@z" );
}

void rbVector3::SetX( VALUE aVector3, VALUE aValue )
{
    rb_check_frozen( aVector3 );
    rb_iv_set( aVector3, "@x", aValue );
}

void rbVector3::SetY( VALUE aVector3, VALUE aValue )
{
    rb_check_frozen( aVector3 );
    rb_iv_set( aVector3, "@y", aValue );
}

void rbVector3::SetZ( VALUE aVector3, VALUE aValue )
{
    rb_check_frozen( aVector3 );
    rb_iv_set( aVector3, "@z", aValue );
}

#endif // SYSTEM_VECTOR2_HPP
