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

#ifndef GRAPHICS_TRANSFORM_HPP
#define GRAPHICS_TRANSFORM_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/Transform.hpp>

namespace rbTransform
{
#if defined( GRAPHICS_TRANSFORM_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_TRANSFORM_CPP )
    // Transform#initialize
	// Transform#initialize(a00, a01, a02, a10, a11, a12, a20, a21, a22)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Transform#initialize_copy(transform)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aTransform );
	
	// Transform#matrix
	// Transform#get_matrix
	// Transform#getMatrix
	static VALUE GetMatrix( VALUE aSelf );
	
	// Transform#inverse
	// Transform#get_inverse
	// Transform#getInverse
	static VALUE GetInverse( VALUE aSelf );
	
	// Transform#transform_point(x, y)
	// Transform#transform_point(vector2)
	// Transform#transformPoint(x, y)
	// Transform#transformPoint(vector2)
	static VALUE TransformPoint( int argc, VALUE* args, VALUE aSelf );
	
	// Transform#transform_rect(rect)
	// Transform#transformRect(rect)
	static VALUE TransformRect( VALUE aSelf, VALUE aRect );
	
	// Transform#combine(transform)
	static VALUE Combine( VALUE aSelf, VALUE aTransform );
	
	// Transform#translate(x, y)
	// Transform#translate(vector2)
	static VALUE Translate( int argc, VALUE* args, VALUE aSelf );
	
	// Transform#rotate(angle)
	// Transform#rotate(angle, center_x, center_y)
	// Transform#rotate(angle, vector2)
	static VALUE Rotate( int argc, VALUE* args, VALUE aSelf );
	
	// Transform#scale(scale_x, scale_y)
	// Transform#scale(scale_x, scale_y, center_x, center_y)
	// Transform#scale(factors)
	// Transform#scale(factors, center)
	static VALUE Scale( int argc, VALUE* args, VALUE aSelf );
	
	// Transform#*(transform)
	// Transform#*(vector2)
	static VALUE MultiplyOperator( VALUE aSelf, VALUE aRight );
	
    // Transform#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
	
	// Transform#marshal_load(data)
	static VALUE MarshalLoad( VALUE aSelf, VALUE someData );

    // Transform#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Transform#inspect
    // Transform#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_TRANSFORM_HPP
