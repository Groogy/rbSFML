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

#define GRAPHICS_CONVEX_SHAPE_CPP

#include "ConvexShape.hpp"
#include "Graphics/Shape.hpp"
#include "System/Vector2.hpp"

void rbConvexShape::Init( VALUE SFML )
{
    rbConvexShape::Class = rb_define_class_under( SFML, "ConvexShape", rbShape::Class );
	
	// Class methods
	rb_define_alloc_func( rbConvexShape::Class, rbMacros::Allocate< sf::ConvexShape > );

    // Instance methods
    ext_define_method( rbConvexShape::Class, "initialize",           rbConvexShape::Initialize,         -1 );
    ext_define_method( rbConvexShape::Class, "initialize_copy",      rbConvexShape::InitializeCopy,      1 );
	ext_define_method( rbConvexShape::Class, "set_point_count",      rbConvexShape::SetPointCount,       1 );
	ext_define_method( rbConvexShape::Class, "get_point_count",      rbConvexShape::GetPointCount,       0 );
	ext_define_method( rbConvexShape::Class, "set_point",            rbConvexShape::SetPoint,            2 );
	ext_define_method( rbConvexShape::Class, "get_point",            rbConvexShape::GetPoint,            1 );
    ext_define_method( rbConvexShape::Class, "==",                   rbConvexShape::Equal,               1 );
    ext_define_method( rbConvexShape::Class, "inspect",              rbConvexShape::Inspect,             0 );

    // Instance aliases
	rb_define_alias( rbConvexShape::Class, "to_s",                "inspect"               );
	rb_define_alias( rbConvexShape::Class, "point_count=",        "set_point_count"       );
	rb_define_alias( rbConvexShape::Class, "setPointCount",       "set_point_count"       );
	rb_define_alias( rbConvexShape::Class, "point_count",         "get_point_count"       );
	rb_define_alias( rbConvexShape::Class, "getPointCount",       "get_point_count"       );
	rb_define_alias( rbConvexShape::Class, "setPoint",            "set_point"             );
	rb_define_alias( rbConvexShape::Class, "getPoint",            "get_point"             );
}

// ConvexShape#initialize
VALUE rbConvexShape::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 1:
		rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class )->setPointCount( NUM2UINT( args[ 1 ] ) );
	case 0:
		break;
	}
	
    return rb_call_super( argc, args );
}

// ConvexShape#initialize_copy(source)
VALUE rbConvexShape::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class ) = *rbMacros::ToSFML< sf::ConvexShape >( aSource, rbConvexShape::Class );
	rb_iv_set( aSelf, "@__ref__texture", rb_iv_get( aSource, "@__ref__texture" ) );
    return aSelf;
}

// ConvexShape#point_count=(count)
// ConvexShape#set_point_count(count)
// ConvexShape#setPointCount(count)
VALUE rbConvexShape::SetPointCount( VALUE aSelf, VALUE aCount )
{
	rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class )->setPointCount( NUM2UINT( aCount ) );
	return Qnil;
}

// ConvexShape#point_count
// ConvexShape#get_point_count
// ConvexShape#getPointCount
VALUE rbConvexShape::GetPointCount( VALUE aSelf )
{
	return INT2FIX( rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class )->getPointCount() );
}

// ConvexShape#set_point(index, point)
// ConvexShape#setPoint(index, point)
VALUE rbConvexShape::SetPoint( VALUE aSelf, VALUE anIndex, VALUE aPoint )
{
	rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class )->setPoint( NUM2UINT( anIndex ), rbVector2::ToSFMLf( aPoint ) );
	return Qnil;
}

// ConvexShape#get_point(index)
// ConvexShape#getPoint(index)
VALUE rbConvexShape::GetPoint( VALUE aSelf, VALUE anIndex )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class )->getPoint( NUM2UINT( anIndex ) ) );
}

// ConvexShape#==(other)
VALUE rbConvexShape::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbConvexShape::Class ) ) return Qfalse;
    if( !RTEST( rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class ) != rbMacros::ToSFML< sf::ConvexShape >( anOther, rbConvexShape::Class ) ) ) return Qfalse;
    return Qtrue;
}

// ConvexShape#inspect
// ConvexShape#to_s
VALUE rbConvexShape::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::ConvexShape >( aSelf, rbConvexShape::Class ) );
}
