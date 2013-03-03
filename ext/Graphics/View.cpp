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
 
#define GRAPHICS_VIEW_CPP

#include "View.hpp"
#include "System/Vector2.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Transform.hpp"

void rbView::Init( VALUE SFML )
{
    rbView::Class = rb_define_class_under( SFML, "View", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( rbView::Class, rbMacros::Allocate< sf::View > );

    // Instance methods
	ext_define_method( rbView::Class, "initialize",             rbView::Initialize,          -1 );
    ext_define_method( rbView::Class, "initialize_copy",        rbView::InitializeCopy,       1 );
	ext_define_method( rbView::Class, "set_center",             rbView::SetCenter,           -1 );
	ext_define_method( rbView::Class, "set_size",               rbView::SetSize,             -1 );
	ext_define_method( rbView::Class, "set_rotation",           rbView::SetRotation,          1 );
	ext_define_method( rbView::Class, "set_viewport",           rbView::SetViewport,          1 );
	ext_define_method( rbView::Class, "reset",                  rbView::Reset,                1 );
	ext_define_method( rbView::Class, "get_center",             rbView::GetCenter,            0 );
	ext_define_method( rbView::Class, "get_size",               rbView::GetSize,              0 );
	ext_define_method( rbView::Class, "get_rotation",           rbView::GetRotation,          0 );
	ext_define_method( rbView::Class, "get_viewport",           rbView::GetViewport,          0 );
	ext_define_method( rbView::Class, "move",                   rbView::Move,                -1 );
	ext_define_method( rbView::Class, "rotate",                 rbView::Rotate,               1 );
	ext_define_method( rbView::Class, "zoom",                   rbView::Zoom,                 1 );
	ext_define_method( rbView::Class, "get_transform",          rbView::GetTransform,         0 );
	ext_define_method( rbView::Class, "get_inverse_transform",  rbView::GetInverseTransform,  0 );
	ext_define_method( rbView::Class, "marshal_dump",           rbView::MarshalDump,          0 );
    ext_define_method( rbView::Class, "==",                     rbView::Equal,                1 );
    ext_define_method( rbView::Class, "inspect",                rbView::Inspect,              0 );

    // Instance aliases
    rb_define_alias( rbView::Class, "to_s",                "inspect"               );
	rb_define_alias( rbView::Class, "center=",             "set_center"            );
	rb_define_alias( rbView::Class, "setCenter",           "set_center"            );
	rb_define_alias( rbView::Class, "rotation=",           "set_rotation"          );
	rb_define_alias( rbView::Class, "setRotation",         "set_rotation"          );
	rb_define_alias( rbView::Class, "size=",               "set_size"              );
	rb_define_alias( rbView::Class, "setSize",             "set_size"              );
	rb_define_alias( rbView::Class, "viewport=",           "set_viewport"          );
	rb_define_alias( rbView::Class, "setViewport",         "set_viewport"          );
	rb_define_alias( rbView::Class, "center",              "get_center"            );
	rb_define_alias( rbView::Class, "getCenter",           "get_center"            );
	rb_define_alias( rbView::Class, "rotation",            "get_rotation"          );
	rb_define_alias( rbView::Class, "getRotation",         "get_rotation"          );
	rb_define_alias( rbView::Class, "size",                "get_size"              );
	rb_define_alias( rbView::Class, "getSize",             "get_size"              );
	rb_define_alias( rbView::Class, "viewport",            "get_viewport"          );
	rb_define_alias( rbView::Class, "getViewport",         "get_viewport"          );
	rb_define_alias( rbView::Class, "transform",           "get_transform"         );
	rb_define_alias( rbView::Class, "getTransform",        "get_transform"         );
	rb_define_alias( rbView::Class, "inverse_transform",   "get_inverse_transform" );
	rb_define_alias( rbView::Class, "getInverseTransform", "get_inverse_transform" );
}

// View#initialize
// View#initialize(rect)
// View#initialize(center, size)
VALUE rbView::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 0:
		break;
	case 1:
		rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->reset( rbRect::ToSFMLf( args[ 0 ] ) );
		break;
	case 2:
		rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->setCenter( rbVector2::ToSFMLf( args[ 0 ] ) );
		rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->setSize( rbVector2::ToSFMLf( args[ 1 ] ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0..2" );
	}
	return Qnil;
}

// View#initialize_copy(source)
VALUE rbView::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< sf::View >( aSelf, rbView::Class ) = *rbMacros::ToSFML< sf::View >( aSource, rbView::Class );
    return aSelf;
}

// View#setCenter(x, y)
// View#setCenter(vector2)
// View#set_center(x, y)
// View#set_center(vector2)
// View#center=(vector2)
VALUE rbView::SetCenter( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f center;
	
	switch( argc )
	{
	case 1:
		center = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		center.x = NUM2DBL( args[ 0 ] );
		center.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->setCenter( center );
	return Qnil;
}

// View#setSize(width, height)
// View#setSize(vector2)
// View#set_size(width, height)
// View#set_size(vector2)
// View#size=(vector2)
VALUE rbView::SetSize( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f size;
	
	switch( argc )
	{
	case 1:
		size = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		size.x = NUM2DBL( args[ 0 ] );
		size.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->setSize( size );
	return Qnil;
}

// View#setRotation(angle)
// View#set_rotation(angle)
// View#rotation=(angle)
VALUE rbView::SetRotation( VALUE aSelf, VALUE anAngle )
{
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->setRotation( NUM2DBL( anAngle ) );
	return Qnil;
}

// View#setViewport(viewport)
// View#set_viewport(viewport)
// View#viewport=(viewport)
VALUE rbView::SetViewport( VALUE aSelf, VALUE aViewport )
{
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->setViewport( rbRect::ToSFMLf( aViewport ) );
	return Qnil;
}

// View#reset(viewport)
VALUE rbView::Reset( VALUE aSelf, VALUE aViewport )
{
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->reset( rbRect::ToSFMLf( aViewport ) );
	return Qnil;
}

// View#getCenter()
// View#get_center()
// View#center()
VALUE rbView::GetCenter( VALUE aSelf )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->getCenter() );
}

// View#getSize()
// View#get_size()
// View#size()
VALUE rbView::GetSize( VALUE aSelf )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->getSize() );
}

// View#getRotation()
// View#get_rotation()
// View#rotation()
VALUE rbView::GetRotation( VALUE aSelf )
{
	return rb_float_new( rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->getRotation() );
}

// View#getViewport()
// View#get_viewport()
// View#viewport()
VALUE rbView::GetViewport( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->getViewport() );
}

// View#move(x, y)
// View#move(vector2)
VALUE rbView::Move( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f offset;
	
	switch( argc )
	{
	case 1:
		offset = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		offset.x = NUM2DBL( args[ 0 ] );
		offset.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->move( offset );
	return Qnil;
}

// View#rotate(angle)
VALUE rbView::Rotate( VALUE aSelf, VALUE anAngle )
{
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->rotate( NUM2DBL( anAngle ) );
	return Qnil;
}

// View#zoom(factor)
VALUE rbView::Zoom( VALUE aSelf, VALUE aFactor )
{
	rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->zoom( NUM2DBL( aFactor ) );
	return Qnil;
}

// View#getTransform()
// View#get_transform()
// View#transform()
VALUE rbView::GetTransform( VALUE aSelf )
{
	const sf::Transform& transform = rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->getTransform();
	VALUE obj = rbMacros::ToRuby( const_cast< sf::Transform* >( &transform ), rbTransform::Class );
	rb_iv_set( obj, "@__ref__owner", aSelf );
	rb_obj_freeze( obj );
	return obj;
}

// View#getInverseTransform()
// View#get_inverse_transform()
// View#inverse_transform()
VALUE rbView::GetInverseTransform( VALUE aSelf )
{
	const sf::Transform& transform = rbMacros::ToSFML< sf::View >( aSelf, rbView::Class )->getInverseTransform();
	VALUE obj = rbMacros::ToRuby( const_cast< sf::Transform* >( &transform ), rbTransform::Class );
	rb_iv_set( obj, "@__ref__owner", aSelf );
	rb_obj_freeze( obj );
	return obj;
}

// View#marshal_dump
VALUE rbView::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// View#==(other)
VALUE rbView::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbView::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::View >( aSelf, rbView::Class ) == rbMacros::ToSFML< sf::View >( aSelf, rbView::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// View#inspect
// View#to_s
VALUE rbView::Inspect( VALUE aSelf )
{
	VALUE viewportString = rb_funcall( rbView::GetViewport( aSelf ), rb_intern( "insepct" ), 0 );
	return rb_sprintf( "%s(%s)",
					   rb_obj_classname( aSelf ),
					   StringValueCStr( viewportString ) );
}
