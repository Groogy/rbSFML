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

#ifndef WINDOW_JOYSTICK_HPP
#define WINDOW_JOYSTICK_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"

#include <SFML/Window/Joystick.hpp>

namespace rbJoystick
{
#if defined( WINDOW_JOYSTICK_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif
    
#if defined( RBSFML_WINDOW )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_JOYSTICK_CPP )
    // Joystick.connected?(id)
	// Joystick.isConnected(id)
	// Joystick.is_connected?(id)
	// Joystick.is_connected(id)
    static VALUE IsConnected( VALUE aSelf, VALUE anID );
    
    // Joystick.button_count(id)
	// Joystick.getButtonCount(id)
	// Joystick.get_button_count(id)
    static VALUE GetButtonCount( VALUE aSelf, VALUE anID );
    
    // Joystick.axis?(id, axis)
	// Joystick.HasAxis(id, axis)
	// Joystick.has_axis?(id, axis)
	// Joystick.has_axis(id, axis)
    static VALUE HasAxis( VALUE aSelf, VALUE anID, VALUE anAxis );
    
    // Joystick.button_pressed?(id, button)
	// Joystick.isButtonPressed(id, button)
	// Joystick.is_button_pressed?(id, button)
	// Joystick.is_button_pressed(id, button)
	// Joystick.pressed?(id, button)
    static VALUE IsButtonPressed( VALUE aSelf, VALUE anID, VALUE aButton );
    
    // Joystick.axis_position(id, axis)
    // Joystick.getAxisPosition(id, axis)
	// Joystick.get_axis_position(id, axis)
    static VALUE GetAxisPosition( VALUE aself, VALUE anID, VALUE anAxis );
    
    // Joystick.update
    static VALUE Update( VALUE aSelf );
#endif
}

#endif // WINDOW_JOYSTICK_HPP
