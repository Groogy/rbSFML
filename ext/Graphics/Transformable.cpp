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
 
#define GRAPHICS_TRANSFORMABLE_CPP

#include "Transformable.hpp"
#include "System/Vector2.hpp"
#include "Graphics/Transform.hpp"

static VALUE rbInternalIncludedTransformable( VALUE aModule, VALUE aBase )
{
	rb_define_alloc_func( aBase, rbMacros::Allocate< sf::Transformable > );
	return Qnil;
}

void rbTransformable::Init( VALUE SFML )
{
    rbTransformable::Module = rb_define_module_under( SFML, "Transformable" );
	
	// Class methods
	ext_define_module_function( rbTransformable::Module, "included", rbInternalIncludedTransformable, 1 );

    // Instance methods
	//rb_define_method( rbTransformable::Module, "initialize",             rbTransformable::Initialize,           0 );
    ext_define_method( rbTransformable::Module, "initialize_copy",        rbTransformable::InitializeCopy,       1 );
	ext_define_method( rbTransformable::Module, "set_position",           rbTransformable::SetPosition,         -1 );
	ext_define_method( rbTransformable::Module, "set_rotation",           rbTransformable::SetRotation,          1 );
	ext_define_method( rbTransformable::Module, "set_scale",              rbTransformable::SetScale,            -1 );
	ext_define_method( rbTransformable::Module, "set_origin",             rbTransformable::SetOrigin,           -1 );
	ext_define_method( rbTransformable::Module, "get_position",           rbTransformable::GetPosition,          0 );
	ext_define_method( rbTransformable::Module, "get_rotation",           rbTransformable::GetRotation,          0 );
	ext_define_method( rbTransformable::Module, "get_scale",              rbTransformable::GetScale,            -1 );
	ext_define_method( rbTransformable::Module, "get_origin",             rbTransformable::GetOrigin,            0 );
	ext_define_method( rbTransformable::Module, "move",                   rbTransformable::Move,                -1 );
	ext_define_method( rbTransformable::Module, "rotate",                 rbTransformable::Rotate,               1 );
	ext_define_method( rbTransformable::Module, "get_transform",          rbTransformable::GetTransform,         0 );
	ext_define_method( rbTransformable::Module, "get_inverse_transform",  rbTransformable::GetInverseTransform,  0 );
	ext_define_method( rbTransformable::Module, "marshal_dump",           rbTransformable::MarshalDump,          0 );
    ext_define_method( rbTransformable::Module, "==",                     rbTransformable::Equal,                1 );
    ext_define_method( rbTransformable::Module, "inspect",                rbTransformable::Inspect,              0 );

    // Instance aliases
    rb_define_alias( rbTransformable::Module, "to_s",                "inspect"               );
	rb_define_alias( rbTransformable::Module, "position=",           "set_position"          );
	rb_define_alias( rbTransformable::Module, "setPosition",         "set_position"          );
	rb_define_alias( rbTransformable::Module, "rotation=",           "set_rotation"          );
	rb_define_alias( rbTransformable::Module, "setRotation",         "set_rotation"          );
	rb_define_alias( rbTransformable::Module, "scale=",              "set_scale"             );
	rb_define_alias( rbTransformable::Module, "setScale",            "set_scale"             );
	rb_define_alias( rbTransformable::Module, "origin=",             "set_origin"            );
	rb_define_alias( rbTransformable::Module, "setOrigin",           "set_origin"            );
	rb_define_alias( rbTransformable::Module, "position",            "get_position"          );
	rb_define_alias( rbTransformable::Module, "getPosition",         "get_position"          );
	rb_define_alias( rbTransformable::Module, "rotation",            "get_rotation"          );
	rb_define_alias( rbTransformable::Module, "getRotation",         "get_rotation"          );
	rb_define_alias( rbTransformable::Module, "scale",               "get_scale"             );
	rb_define_alias( rbTransformable::Module, "getScale",            "get_scale"             );
	rb_define_alias( rbTransformable::Module, "origin",              "get_origin"            );
	rb_define_alias( rbTransformable::Module, "get_origin",          "get_origin"            );
	rb_define_alias( rbTransformable::Module, "getOrigin",           "get_origin"            );
	rb_define_alias( rbTransformable::Module, "transform",           "get_transform"         );
	rb_define_alias( rbTransformable::Module, "getTransform",        "get_transform"         );
	rb_define_alias( rbTransformable::Module, "inverse_transform",   "get_inverse_transform" );
	rb_define_alias( rbTransformable::Module, "getInverseTransform", "get_inverse_transform" );
}

// Transformable#initialize
VALUE rbTransformable::Initialize( VALUE aSelf )
{
	if( rb_iv_get( aSelf, "@__internal__transformable_offset" ) == Qnil )
	{
		rb_iv_set( aSelf, "@__internal__transformable_offset", INT2FIX( 0 ) );
	}
	rb_call_super( 0, NULL );
	return Qnil;
}

// Transformable#initialize_copy(source)
VALUE rbTransformable::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbTransformable::ToSFML( aSelf ) = *rbTransformable::ToSFML( aSource );
	rb_iv_set( aSelf, "@__internal__transformable_offset", rb_iv_get( aSource, "@__internal__transformable_offset" ) );
    return rb_call_super( 1, &aSource );
}

// Transformable#setPosition(x, y)
// Transformable#setPosition(vector2)
// Transformable#set_position(x, y)
// Transformable#set_position(vector2)
// Transformable#position=(vector2)
VALUE rbTransformable::SetPosition( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f position;
	
	switch( argc )
	{
	case 1:
		position = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		position.x = NUM2DBL( args[ 0 ] );
		position.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbTransformable::ToSFML( aSelf )->setPosition( position );
	return Qnil;
}

// Transformable#setRotation(angle)
// Transformable#set_rotation(angle)
// Transformable#rotation=(angle)
VALUE rbTransformable::SetRotation( VALUE aSelf, VALUE anAngle )
{
	rbTransformable::ToSFML( aSelf )->setRotation( NUM2DBL( anAngle ) );
	return Qnil;
}

// Transformable#setScale(x, y)
// Transformable#setScale(vector2)
// Transformable#set_scale(x, y)
// Transformable#set_scale(vector2)
// Transformable#scale=(vector2)
VALUE rbTransformable::SetScale( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f scale;
	
	switch( argc )
	{
	case 1:
		scale = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		scale.x = NUM2DBL( args[ 0 ] );
		scale.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbTransformable::ToSFML( aSelf )->setScale( scale );
	return Qnil;
}

// Transformable#setOrigin(x, y)
// Transformable#setOrigin(vector2)
// Transformable#set_origin(x, y)
// Transformable#set_origin(vector2)
// Transformable#origin=(vector2)
VALUE rbTransformable::SetOrigin( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f origin;
	
	switch( argc )
	{
	case 1:
		origin = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		origin.x = NUM2DBL( args[ 0 ] );
		origin.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbTransformable::ToSFML( aSelf )->setOrigin( origin );
	return Qnil;
}

// Transformable#getPosition()
// Transformable#get_position()
// Transformable#position()
VALUE rbTransformable::GetPosition( VALUE aSelf )
{
	return rbVector2::ToRuby( rbTransformable::ToSFML( aSelf )->getPosition() );
}

// Transformable#getRotation()
// Transformable#get_rotation()
// Transformable#rotation()
VALUE rbTransformable::GetRotation( VALUE aSelf )
{
	return rb_float_new( rbTransformable::ToSFML( aSelf )->getRotation() );
}

// Transformable#getScale()
// Transformable#get_scale()
// Transformable#scale()
// Transformable#scale(x, y)
// Transformable#scale(vector2)
VALUE rbTransformable::GetScale( int argc, VALUE* args, VALUE aSelf )
{
	sf::Vector2f scale;
	switch( argc )
	{
	case 0:
		return rbVector2::ToRuby( rbTransformable::ToSFML( aSelf )->getScale() );
	case 1:
		scale = rbVector2::ToSFMLf( args[ 0 ] );
		break;
	case 2:
		scale.x = NUM2DBL( args[ 0 ] );
		scale.y = NUM2DBL( args[ 1 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0..2" );
	}
	
	rbTransformable::ToSFML( aSelf )->scale( scale );
	return Qnil;
}

// Transformable#getOrigin()
// Transformable#get_origin()
// Transformable#origin()
VALUE rbTransformable::GetOrigin( VALUE aSelf )
{
	return rbVector2::ToRuby( rbTransformable::ToSFML( aSelf )->getOrigin() );
}

// Transformable#move(x, y)
// Transformable#move(vector2)
VALUE rbTransformable::Move( int argc, VALUE* args, VALUE aSelf )
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
	
	rbTransformable::ToSFML( aSelf )->move( offset );
	return Qnil;
}

// Transformable#rotate(angle)
VALUE rbTransformable::Rotate( VALUE aSelf, VALUE anAngle )
{
	rbTransformable::ToSFML( aSelf )->rotate( NUM2DBL( anAngle ) );
	return Qnil;
}

// Transformable#getTransform()
// Transformable#get_transform()
// Transformable#transform()
VALUE rbTransformable::GetTransform( VALUE aSelf )
{
	const sf::Transform& transform = rbTransformable::ToSFML( aSelf )->getTransform();
	VALUE obj = rbMacros::ToRuby( const_cast< sf::Transform* >( &transform ), rbTransform::Class );
	rb_iv_set( obj, "@__ref__owner", aSelf );
	rb_obj_freeze( obj );
	return obj;
}

// Transformable#getInverseTransform()
// Transformable#get_inverse_transform()
// Transformable#inverse_transform()
VALUE rbTransformable::GetInverseTransform( VALUE aSelf )
{
	const sf::Transform& transform = rbTransformable::ToSFML( aSelf )->getInverseTransform();
	VALUE obj = rbMacros::ToRuby( const_cast< sf::Transform* >( &transform ), rbTransform::Class );
	rb_iv_set( obj, "@__ref__owner", aSelf );
	rb_obj_freeze( obj );
	return obj;
}

// Transformable#marshal_dump
VALUE rbTransformable::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Transformable#==(other)
VALUE rbTransformable::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbTransformable::Module ) )
		return Qfalse;
    else if( rbTransformable::ToSFML( aSelf ) == rbTransformable::ToSFML( anOther ) )
		return Qtrue;
	else
		return Qfalse;
}

// Transformable#inspect
// Transformable#to_s
VALUE rbTransformable::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbTransformable::ToSFML( aSelf ) );
}
