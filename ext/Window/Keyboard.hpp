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

#ifndef WINDOW_KEYBOARD_HPP
#define WINDOW_KEYBOARD_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/Window/Keyboard.hpp>

namespace rbKeyboard
{
    
#if defined(WINDOW_KEYBOARD_CPP)
    VALUE Keyboard;
#else
    extern VALUE Keyboard;
#endif
    
#if defined(RBSFML_WINDOW)
    void Init(VALUE SFML);
#endif
    
#if defined(WINDOW_KEYBOARD_CPP)
    // Keyboard::key_pressed?(button)
    // Keyboard::IsKeyPressed(button)
    // Keyboard::pressed?(button)
    static VALUE IsKeyPressed(VALUE, VALUE key);
#endif
    
}

#endif // WINDOW_KEYBOARD_HPP
