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
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <System/Vector2.hpp>
#include <Window/Window.hpp>

#include <SFML/Window/Mouse.hpp>

namespace rbJoystick
{
    
#if defined(WINDOW_JOYSTICK_CPP)
    VALUE Joystick;
#else
    extern VALUE Joystick;
#endif
    
#if defined(RBSFML_WINDOW)
    void Init(VALUE SFML);
#endif
    
#if defined(WINDOW_JOYSTICK_CPP)
    // Joystick::connected?(id)
    // Joystick::IsConnected(id)
    static VALUE IsConnected(VALUE, VALUE id);
    
    // Joystick::button_count(id)
    // Joystick::GetButtonCount(id)
    static VALUE GetButtonCount(VALUE, VALUE id);
    
    // Joystick::axis?(id, axis)
    // Joystick::HasAxis(id, axis)
    // Joystick::has_axis(id, axis)
    static VALUE HasAxis(VALUE, VALUE id, VALUE axis);
    
    // Joystick::button_pressed?(id, button)
    // Joystick::IsButtonPressed(id, button)
    // Joystick::pressed?(id, button)
    static VALUE IsButtonPressed(VALUE, VALUE id, VALUE button);
    
    // Joystick::axis_position(id, axis)
    // Joystick::GetAxisPosition(id, axis)
    static VALUE GetAxisPosition(VALUE, VALUE id, VALUE axis);
    
    // Joystick::update
    // Joystick::Update
    static VALUE Update(VALUE);
#endif
    
}

#endif // WINDOW_JOYSTICK_HPP
