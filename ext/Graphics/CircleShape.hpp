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

#ifndef GRAPHICS_CIRCLE_SHAPE_HPP
#define GRAPHICS_CIRCLE_SHAPE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/CircleShape.hpp>

namespace rbCircleShape
{
#if defined( GRAPHICS_CIRCLE_SHAPE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_CIRCLE_SHAPE_CPP )
    // CircleShape#initialize
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // CircleShape#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// CircleShape#radius=(radius)
	// CircleShape#set_radius(radius)
	// CircleShape#setRadius(radius)
	static VALUE SetRadius( VALUE aSelf, VALUE aRadius );
	
	// CircleShape#radius
	// CircleShape#get_radius
	// CircleShape#getRadius
	static VALUE GetRadius( VALUE aSelf );
	
	// CircleShape#point_count=(count)
	// CircleShape#set_point_count(count)
	// CircleShape#setPointCount(count)
	static VALUE SetPointCount( VALUE aSelf, VALUE aCount );
	
	// CircleShape#point_count
	// CircleShape#get_point_count
	// CircleShape#getPointCount
	static VALUE GetPointCount( VALUE aSelf );
	
	// CircleShape#get_point(index)
	// CircleShape#getPoint(index)
	static VALUE GetPoint( VALUE aSelf, VALUE anIndex );
	
	// CircleShape#==(other)
	static VALUE Equal( VALUE aSelf, VALUE anOther );

    // CircleShape#inspect
    // CircleShape#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

#endif // GRAPHICS_CIRCLE_SHAPE_HPP
