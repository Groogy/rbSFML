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

#ifndef GRAPHICS_TRANSFORMABLE_HPP
#define GRAPHICS_TRANSFORMABLE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/Transformable.hpp>

namespace rbTransformable
{
	static inline sf::Transformable* ToSFML( VALUE aValue );
	
#if defined( GRAPHICS_TRANSFORMABLE_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_TRANSFORMABLE_CPP )
    // Transformable#initialize
    static VALUE Initialize( VALUE aSelf );
	
	// Transformable#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// Transformable#set_position(x, y)
	// Transformable#set_position(vector2)
	// Transformable#position=(vector2)
	// Transformable#setPosition(x, y)
	// Transformable#setPosition(vector2)
	static VALUE SetPosition( int argc, VALUE* args, VALUE aSelf );
	
	// Transformable#set_rotation(angle)
	// Transformable#setRotation(angle)
	// Transformable#rotation=(angle)
	static VALUE SetRotation( VALUE aSelf, VALUE anAngle );
	
	// Transformable#setScale(x, y)
	// Transformable#setScale(vector2)
	// Transformable#set_scale(x, y)
	// Transformable#set_scale(vector2)
	// Transformable#scale=(vector2)
	static VALUE SetScale( int argc, VALUE* args, VALUE aSelf );
	
	// Transformable#setOrigin(x, y)
	// Transformable#setOrigin(vector2)
	// Transformable#set_origin(x, y)
	// Transformable#set_origin(vector2)
	// Transformable#origin=(vector2)
	static VALUE SetOrigin( int argc, VALUE* args, VALUE aSelf );
	
	// Transformable#getPosition()
	// Transformable#get_position()
	// Transformable#position()
	static VALUE GetPosition( VALUE aSelf );
	
	// Transformable#getRotation()
	// Transformable#get_rotation()
	// Transformable#rotation()
	static VALUE GetRotation( VALUE aSelf );
	
	// Transformable#getScale()
	// Transformable#get_scale()
	// Transformable#scale()
	// Transformable#scale(x, y)
	// Transformable#scale(vector2)
	static VALUE GetScale( int argc, VALUE* args, VALUE aSelf );
	
	// Transformable#getOrigin()
	// Transformable#get_origin()
	// Transformable#origin()
	static VALUE GetOrigin( VALUE aSelf );
	
	// Transformable#move(x, y)
	// Transformable#move(vector2)
	static VALUE Move( int argc, VALUE* args, VALUE aSelf );
	
	// Transformable#rotate(angle)
	static VALUE Rotate( VALUE aSelf, VALUE anAngle );
	
	// Transformable#getTransform()
	// Transformable#get_transform()
	// Transformable#transform()
	static VALUE GetTransform( VALUE aSelf );
	
	// Transformable#getInverseTransform()
	// Transformable#get_inverse_transform()
	// Transformable#inverse_transform()
	static VALUE GetInverseTransform( VALUE aSelf );
	
    // Transformable#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Transformable#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Transformable#inspect
    // Transformable#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

sf::Transformable* rbTransformable::ToSFML( VALUE aValue )
{
	aValue = rbMacros::ToRuby( aValue, rbTransformable::Module );
	char* compensationPtr = reinterpret_cast< char* >( DATA_PTR( aValue ) );
	unsigned int ptrOffset = 0;
	VALUE offset = rb_iv_get( aValue, "@__internal__transformable_offset" );
	if( offset != Qnil )
		ptrOffset = FIX2UINT( offset );
	return reinterpret_cast< sf::Transformable* >( compensationPtr + ptrOffset );
}

#endif // GRAPHICS_TRANSFORMABLE_HPP
