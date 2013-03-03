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

#define GRAPHICS_CIRCLE_SHAPE_CPP

#include "CircleShape.hpp"
#include "Shape.hpp"
#include "System/Vector2.hpp"

void rbCircleShape::Init( VALUE SFML )
{
    rbCircleShape::Class = rb_define_class_under( SFML, "CircleShape", rbShape::Class );
	
	// Class methods
	rb_define_alloc_func( rbCircleShape::Class, rbMacros::Allocate< sf::CircleShape > );

    // Instance methods
    ext_define_method( rbCircleShape::Class, "initialize",           rbCircleShape::Initialize,         -1 );
    ext_define_method( rbCircleShape::Class, "initialize_copy",      rbCircleShape::InitializeCopy,      1 );
	ext_define_method( rbCircleShape::Class, "set_radius",           rbCircleShape::SetRadius,           1 );
	ext_define_method( rbCircleShape::Class, "get_radius",           rbCircleShape::GetRadius,           0 );
	ext_define_method( rbCircleShape::Class, "set_point_count",      rbCircleShape::SetPointCount,       1 );
	ext_define_method( rbCircleShape::Class, "get_point_count",      rbCircleShape::GetPointCount,       0 );
	ext_define_method( rbCircleShape::Class, "get_point",            rbCircleShape::GetPoint,            1 );
    ext_define_method( rbCircleShape::Class, "==",                   rbCircleShape::Equal,               1 );
    ext_define_method( rbCircleShape::Class, "inspect",              rbCircleShape::Inspect,             0 );

    // Instance aliases
	rb_define_alias( rbCircleShape::Class, "to_s",                "inspect"               );
	rb_define_alias( rbCircleShape::Class, "radius=",             "set_radius"            );
	rb_define_alias( rbCircleShape::Class, "setRadius",           "set_radius"            );
	rb_define_alias( rbCircleShape::Class, "radius",              "get_radius"            );
	rb_define_alias( rbCircleShape::Class, "getRadius",           "get_radius"            );
	rb_define_alias( rbCircleShape::Class, "point_count=",        "set_point_count"       );
	rb_define_alias( rbCircleShape::Class, "setPointCount",       "set_point_count"       );
	rb_define_alias( rbCircleShape::Class, "point_count",         "get_point_count"       );
	rb_define_alias( rbCircleShape::Class, "getPointCount",       "get_point_count"       );
	rb_define_alias( rbCircleShape::Class, "getPoint",            "get_point"             );
}

// CircleShape#initialize
VALUE rbCircleShape::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 2:
		rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->setPointCount( NUM2UINT( args[ 1 ] ) );
	case 1:
		rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->setRadius( NUM2DBL( args[ 0 ] ) );
	case 0:
		break;
	}
	
    return rb_call_super( argc, args );
}

// CircleShape#initialize_copy(source)
VALUE rbCircleShape::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class ) = *rbMacros::ToSFML< sf::CircleShape >( aSource, rbCircleShape::Class );
	rb_iv_set( aSelf, "@__ref__texture", rb_iv_get( aSource, "@__ref__texture" ) );
    return aSelf;
}

// CircleShape#radius=(radius)
// CircleShape#set_radius(radius)
// CircleShape#setRadius(radius)
VALUE rbCircleShape::SetRadius( VALUE aSelf, VALUE aRadius )
{
	rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->setRadius( NUM2DBL( aRadius ) );
	return Qnil;
}

// CircleShape#radius
// CircleShape#get_radius
// CircleShape#getRadius
VALUE rbCircleShape::GetRadius( VALUE aSelf )
{
	return rb_float_new( rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->getRadius() );
}

// CircleShape#point_count=(count)
// CircleShape#set_point_count(count)
// CircleShape#setPointCount(count)
VALUE rbCircleShape::SetPointCount( VALUE aSelf, VALUE aCount )
{
	rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->setPointCount( NUM2UINT( aCount ) );
	return Qnil;
}

// CircleShape#point_count
// CircleShape#get_point_count
// CircleShape#getPointCount
VALUE rbCircleShape::GetPointCount( VALUE aSelf )
{
	return INT2FIX( rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->getPointCount() );
}

// CircleShape#get_point(index)
// CircleShape#getPoint(index)
VALUE rbCircleShape::GetPoint( VALUE aSelf, VALUE anIndex )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class )->getPoint( NUM2UINT( anIndex ) ) );
}

// CircleShape#==(other)
VALUE rbCircleShape::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbCircleShape::Class ) ) return Qfalse;
    if( !RTEST( rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class ) != rbMacros::ToSFML< sf::CircleShape >( anOther, rbCircleShape::Class ) ) ) return Qfalse;
    return Qtrue;
}

// CircleShape#inspect
// CircleShape#to_s
VALUE rbCircleShape::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::CircleShape >( aSelf, rbCircleShape::Class ) );
}
