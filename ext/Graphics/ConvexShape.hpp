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

#ifndef GRAPHICS_CONVEX_SHAPE_HPP
#define GRAPHICS_CONVEX_SHAPE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/ConvexShape.hpp>

namespace rbConvexShape
{
#if defined( GRAPHICS_CONVEX_SHAPE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_CONVEX_SHAPE_CPP )
    // ConvexShape#initialize(point_count=0)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // ConvexShape#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// ConvexShape#point_count=(count)
	// ConvexShape#set_point_count(count)
	// ConvexShape#setPointCount(count)
	static VALUE SetPointCount( VALUE aSelf, VALUE aCount );
	
	// ConvexShape#point_count
	// ConvexShape#get_point_count
	// ConvexShape#getPointCount
	static VALUE GetPointCount( VALUE aSelf );
	
	// ConvexShape#set_point(index, point)
	// ConvexShape#setPoint(index, point)
	static VALUE SetPoint( VALUE aSelf, VALUE anIndex, VALUE aPoint );
	
	// ConvexShape#get_point(index)
	// ConvexShape#getPoint(index)
	static VALUE GetPoint( VALUE aSelf, VALUE anIndex );
	
	// ConvexShape#==(other)
	static VALUE Equal( VALUE aSelf, VALUE anOther );

    // ConvexShape#inspect
    // ConvexShape#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

#endif // GRAPHICS_CONVEX_SHAPE_HPP
