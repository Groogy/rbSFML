/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#ifndef WINDOW_MOUSE_HPP
#define WINDOW_MOUSE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"
#include "../System/Vector2.hpp"
#include "Window.hpp"

#include <SFML/Window/Mouse.hpp>

namespace rbMouse
{
    
#if defined( WINDOW_MOUSE_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif
    
#if defined( RBSFML_WINDOW )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_MOUSE_CPP )
    // Mouse.button_pressed?(button)
    // Mouse.isButtonPressed(button)
	// Mouse.is_button_pressed?(button)
	// Mouse.is_button_pressed(button)
    // Mouse.pressed?(button)
    static VALUE IsButtonPressed( VALUE aSelf, VALUE aButton );
    
	// Mouse.position
    // Mouse.getPosition
	// Mouse.get_position
	// Mouse.position(relative_to)
    // Mouse.getPosition(relative_to)
    // Mouse.get_position(relative_to)
    static VALUE GetPosition( int argc, VALUE argv[], VALUE aSelf );
    
	// Mouse.position=(position)
	// Mouse.set_position(poition)
	// Mouse.setPosition(position)
	// Mouse.set_position(position, relative_to)
    // Mouse.setPosition(position, relative_to)
    static VALUE SetPosition( int argc, VALUE argv[], VALUE aSelf );
#endif
    
}

#endif // WINDOW_MOUSE_HPP
