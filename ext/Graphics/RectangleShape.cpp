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

#define GRAPHICS_RECTANGLE_SHAPE_CPP

#include "RectangleShape.hpp"
#include "Shape.hpp"
#include "../System/Vector2.hpp"

void rbRectangleShape::Init( VALUE SFML )
{
    rbRectangleShape::Class = rb_define_class_under( SFML, "RectangleShape", rbShape::Class );
	
	// Class methods
	rb_define_alloc_func( rbRectangleShape::Class, rbMacros::Allocate< sf::RectangleShape > );

    // Instance methods
    ext_define_method( rbRectangleShape::Class, "initialize",           rbRectangleShape::Initialize,         -1 );
    ext_define_method( rbRectangleShape::Class, "initialize_copy",      rbRectangleShape::InitializeCopy,      1 );
	ext_define_method( rbRectangleShape::Class, "set_size",             rbRectangleShape::SetSize,             1 );
	ext_define_method( rbRectangleShape::Class, "get_size",             rbRectangleShape::GetSize,             0 );
	ext_define_method( rbRectangleShape::Class, "get_point_count",      rbRectangleShape::GetPointCount,       0 );
	ext_define_method( rbRectangleShape::Class, "get_point",            rbRectangleShape::GetPoint,            1 );
    ext_define_method( rbRectangleShape::Class, "==",                   rbRectangleShape::Equal,               1 );
    ext_define_method( rbRectangleShape::Class, "inspect",              rbRectangleShape::Inspect,             0 );

    // Instance aliases
	rb_define_alias( rbRectangleShape::Class, "to_s",                "inspect"               );
	rb_define_alias( rbRectangleShape::Class, "size=",               "set_size"              );
	rb_define_alias( rbRectangleShape::Class, "setSize",             "set_size"              );
	rb_define_alias( rbRectangleShape::Class, "size",                "get_size"              );
	rb_define_alias( rbRectangleShape::Class, "getSize",             "get_size"              );
	rb_define_alias( rbRectangleShape::Class, "point_count",         "get_point_count"       );
	rb_define_alias( rbRectangleShape::Class, "getPointCount",       "get_point_count"       );
	rb_define_alias( rbRectangleShape::Class, "getPoint",            "get_point"             );
}

// RectangleShape#initialize
VALUE rbRectangleShape::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 1:
		rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class )->setSize( rbVector2::ToSFMLf( args[ 0 ] ) );
	case 0:
		break;
	}
	
    return rb_call_super( argc, args );
}

// RectangleShape#initialize_copy(source)
VALUE rbRectangleShape::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class ) = *rbMacros::ToSFML< sf::RectangleShape >( aSource, rbRectangleShape::Class );
	rb_iv_set( aSelf, "@__ref__texture", rb_iv_get( aSource, "@__ref__texture" ) );
    return aSelf;
}

// RectangleShape#size=(size)
// RectangleShape#set_size(size)
// RectangleShape#setSize(size)
VALUE rbRectangleShape::SetSize( VALUE aSelf, VALUE aSize )
{
	rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class )->setSize( rbVector2::ToSFMLf( aSize ) );
	return Qnil;
}

// RectangleShape#size
// RectangleShape#get_size
// RectangleShape#getSize
VALUE rbRectangleShape::GetSize( VALUE aSelf )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class )->getSize() );
}

// RectangleShape#point_count
// RectangleShape#get_point_count
// RectangleShape#getPointCount
VALUE rbRectangleShape::GetPointCount( VALUE aSelf )
{
	return INT2FIX( rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class )->getPointCount() );
}

// RectangleShape#get_point(index)
// RectangleShape#getPoint(index)
VALUE rbRectangleShape::GetPoint( VALUE aSelf, VALUE anIndex )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class )->getPoint( NUM2UINT( anIndex ) ) );
}

// RectangleShape#==(other)
VALUE rbRectangleShape::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRectangleShape::Class ) ) return Qfalse;
    if( !RTEST( rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class ) != rbMacros::ToSFML< sf::RectangleShape >( anOther, rbRectangleShape::Class ) ) ) return Qfalse;
    return Qtrue;
}

// RectangleShape#inspect
// RectangleShape#to_s
VALUE rbRectangleShape::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::RectangleShape >( aSelf, rbRectangleShape::Class ) );
}
