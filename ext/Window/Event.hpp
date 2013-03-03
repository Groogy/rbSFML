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

#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <Window/VideoMode.hpp>

#include <SFML/Window/Event.hpp>

namespace rbEvent
{
#if defined(WINDOW_EVENT_CPP)
    VALUE Class;
    VALUE Class_Size;
    VALUE Class_Key;
    VALUE Class_Text;
    VALUE Class_MouseMove;
    VALUE Class_MouseButton;
    VALUE Class_MouseWheel;
    VALUE Class_JoystickMove;
    VALUE Class_JoystickButton;
    VALUE Class_JoystickConnect;
#else
    extern VALUE Class;
    extern VALUE Class_Size;
    extern VALUE Class_Key;
    extern VALUE Class_Text;
    extern VALUE Class_MouseMove;
    extern VALUE Class_MouseButton;
    extern VALUE Class_MouseWheel;
    extern VALUE Class_JoystickMove;
    extern VALUE Class_JoystickButton;
    extern VALUE Class_JoystickConnect;
#endif
    
#if defined( RBSFML_WINDOW )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_EVENT_CPP )    
    // Event#initialize_copy(event)
    static VALUE InitializeCopy( VALUE aSelf, VALUE anEvent );
    
    // Event#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // Event#type
    static VALUE Type( VALUE aSelf );
    
    // Event#info
    static VALUE Info( VALUE aSelf );
    
    // Event#size
    static VALUE Size( VALUE aSelf );
    
    // Event#key
    static VALUE Key( VALUE aSelf );
    
    // Event#text
    static VALUE Text( VALUE aSelf );
    
    // Event#mouse_move
    // Event#mouseMove
    static VALUE MouseMove( VALUE aSelf );
    
    // Event#mouse_button
    // Event#mouseButton
    static VALUE MouseButton( VALUE aSelf );
    
    // Event#mouse_wheel
    // Event#mouseWheel
    static VALUE MouseWheel( VALUE aSelf );
    
    // Event#joystick_move
    // Event#joystickMove
    static VALUE JoystickMove( VALUE aSelf );
    
    // Event#joystick_button
    // Event#joystickButton
    static VALUE JoystickButton( VALUE aSelf );
    
    // Event#joystick_connect
    // Event#joystickConnect
    static VALUE JoystickConnect( VALUE aSelf );
    
    // Event#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );
    
    // Event#inspect
    static VALUE Inspect( VALUE aSelf );
    
#endif   
}

#endif // WINDOW_EVENT_HPP
