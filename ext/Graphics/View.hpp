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

#ifndef GRAPHICS_VIEW_HPP
#define GRAPHICS_VIEW_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/View.hpp>

namespace rbView
{	
#if defined( GRAPHICS_VIEW_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_VIEW_CPP )
    // View#initialize
	// View#initialize(rect)
	// View#initialize(center, size)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );
	
	// View#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// View#set_center(x, y)
	// View#set_center(vector2)
	// View#center=(vector2)
	// View#setCenter(x, y)
	// View#setCenter(vector2)
	static VALUE SetCenter( int argc, VALUE* args, VALUE aSelf );
	
	// View#set_size(width, height)
	// View#set_size(vector2)
	// View#size=(vector2)
	// View#setSize(width, height)
	// View#setSize(vector2)
	static VALUE SetSize( int argc, VALUE* args, VALUE aSelf );
	
	// View#set_rotation(angle)
	// View#setRotation(angle)
	// View#rotation=(angle)
	static VALUE SetRotation( VALUE aSelf, VALUE anAngle );
	
	// View#set_viewport(rect)
	// View#viewport=(rect)
	// View#setViewport(rect)
	static VALUE SetViewport( VALUE aSelf, VALUE aViewport );
	
	// View#reset
	static VALUE Reset( VALUE aSelf, VALUE aViewport );
	
	// View#getCenter()
	// View#get_center()
	// View#center()
	static VALUE GetCenter( VALUE aSelf );
	
	// View#getSize()
	// View#get_size()
	// View#size()
	static VALUE GetSize( VALUE aSelf );
	
	// View#getRotation()
	// View#get_rotation()
	// View#rotation()
	static VALUE GetRotation( VALUE aSelf );
	
	// View#getViewport()
	// View#get_viewport()
	// View#viewport()
	static VALUE GetViewport( VALUE aSelf );
	
	// View#move(x, y)
	// View#move(vector2)
	static VALUE Move( int argc, VALUE* args, VALUE aSelf );
	
	// View#rotate(angle)
	static VALUE Rotate( VALUE aSelf, VALUE anAngle );
	
	// View#zoom(factor)
	static VALUE Zoom( VALUE aSelf, VALUE aFactor );
	
	// View#getTransform()
	// View#get_transform()
	// View#transform()
	static VALUE GetTransform( VALUE aSelf );
	
	// View#getInverseTransform()
	// View#get_inverse_transform()
	// View#inverse_transform()
	static VALUE GetInverseTransform( VALUE aSelf );
	
    // View#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // View#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // View#inspect
    // View#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_TRANSFORMABLE_HPP
