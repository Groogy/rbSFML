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

#ifndef GRAPHICS_RENDER_WINDOW_HPP
#define GRAPHICS_RENDER_WINDOW_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace rbRenderWindow
{
#if defined( GRAPHICS_RENDER_WINDOW_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RENDER_WINDOW_CPP )

    // RenderWindow#initialize
	// RenderWindow#initialize()
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );
	
	// RenderWindow#size
	// RenderWindow#get_size
	// RenderWindow#getSize
	static VALUE GetSize( VALUE aSelf );
	
	// RenderWindow#capture
	static VALUE Capture( VALUE aSelf );
	
    // RenderWindow#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // RenderWindow#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // RenderWindow#inspect
    // RenderWindow#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_RENDER_WINDOW_HPP
