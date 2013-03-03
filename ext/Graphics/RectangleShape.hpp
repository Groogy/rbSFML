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

#ifndef GRAPHICS_RECTANGLE_SHAPE_HPP
#define GRAPHICS_RECTANGLE_SHAPE_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace rbRectangleShape
{
#if defined( GRAPHICS_RECTANGLE_SHAPE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RECTANGLE_SHAPE_CPP )
    // RectangleShape#initialize
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // RectangleShape#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// RectangleShape#size=(radius)
	// RectangleShape#set_size(radius)
	// RectangleShape#setSize(radius)
	static VALUE SetSize( VALUE aSelf, VALUE aSize );
	
	// RectangleShape#size
	// RectangleShape#get_size
	// RectangleShape#getSize
	static VALUE GetSize( VALUE aSelf );
	
	// RectangleShape#point_count
	// RectangleShape#get_point_count
	// RectangleShape#getPointCount
	static VALUE GetPointCount( VALUE aSelf );
	
	// RectangleShape#get_point(index)
	// RectangleShape#getPoint(index)
	static VALUE GetPoint( VALUE aSelf, VALUE anIndex );
	
	// RectangleShape#==(other)
	static VALUE Equal( VALUE aSelf, VALUE anOther );

    // RectangleShape#inspect
    // RectangleShape#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

#endif // GRAPHICS_RECTANGLE_SHAPE_HPP
