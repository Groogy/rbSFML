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

#define WINDOW_JOYSTICK_CPP
#include "Joystick.hpp"

void rbJoystick::Init( VALUE SFML )
{
    rbJoystick::Module = rb_define_module_under( SFML, "Joystick" );
    
	rb_define_const( rbJoystick::Module, "X",           INT2FIX( sf::Joystick::X           ) );
	rb_define_const( rbJoystick::Module, "Y",           INT2FIX( sf::Joystick::Y           ) );
	rb_define_const( rbJoystick::Module, "Z",           INT2FIX( sf::Joystick::Z           ) );
	rb_define_const( rbJoystick::Module, "R",           INT2FIX( sf::Joystick::R           ) );
	rb_define_const( rbJoystick::Module, "U",           INT2FIX( sf::Joystick::U           ) );
	rb_define_const( rbJoystick::Module, "V",           INT2FIX( sf::Joystick::V           ) );
	rb_define_const( rbJoystick::Module, "PovX",        INT2FIX( sf::Joystick::PovX        ) );
	rb_define_const( rbJoystick::Module, "PovY",        INT2FIX( sf::Joystick::PovY        ) );
	rb_define_const( rbJoystick::Module, "Count",       INT2FIX( sf::Joystick::Count       ) );
	rb_define_const( rbJoystick::Module, "AxisCount",   INT2FIX( sf::Joystick::AxisCount   ) );
	rb_define_const( rbJoystick::Module, "ButtonCount", INT2FIX( sf::Joystick::ButtonCount ) );
    
    // Singleton methods
    rb_define_class_method( rbJoystick::Module, "connected?",      rbJoystick::IsConnected,     1 );
    rb_define_class_method( rbJoystick::Module, "button_count",    rbJoystick::GetButtonCount,  1 );
    rb_define_class_method( rbJoystick::Module, "axis?",           rbJoystick::HasAxis,         2 );
    rb_define_class_method( rbJoystick::Module, "button_pressed?", rbJoystick::IsButtonPressed, 2 );
    rb_define_class_method( rbJoystick::Module, "axis_position",   rbJoystick::GetAxisPosition, 2 );
    rb_define_class_method( rbJoystick::Module, "update",          rbJoystick::Update,          0 );
    
    // Singleton aliasses
    VALUE sJoystick = rb_singleton_class( rbJoystick::Module );
    rb_define_alias( sJoystick, "IsConnected",     "connected?"      );
    rb_define_alias( sJoystick, "GetButtonCount",  "button_count"    );
    rb_define_alias( sJoystick, "HasAxis",         "axis?"           );
    rb_define_alias( sJoystick, "has_axis",        "axis?"           );
    rb_define_alias( sJoystick, "IsButtonPressed", "button_pressed?" );
    rb_define_alias( sJoystick, "pressed?",        "button_pressed?" );
    rb_define_alias( sJoystick, "GetAxisPosition", "axis_position"   );
    rb_define_alias( sJoystick, "Update",          "update"          );
}

// Joystick::connected?(id)
// Joystick::IsConnected(id)
VALUE rbJoystick::IsConnected( VALUE aSelf, VALUE anID )
{
    return RBOOL( sf::Joystick::IsConnected( NUM2INT( anID ) ) );
}

// Joystick::button_count(id)
// Joystick::GetButtonCount(id)
VALUE rbJoystick::GetButtonCount( VALUE aSelf, VALUE anID )
{
    return INT2FIX( sf::Joystick::GetButtonCount( NUM2INT( anID ) ) );
}

// Joystick::axis?(id, axis)
// Joystick::HasAxis(id, axis)
// Joystick::has_axis(id, axis)
VALUE rbJoystick::HasAxis( VALUE aSelf, VALUE anID, VALUE anAxis )
{
    sf::Joystick::Axis a = static_cast< sf::Joystick::Axis >( NUM2INT( anAxis ) );
    return RBOOL( sf::Joystick::HasAxis( NUM2INT( anID ), a ) );
}

// Joystick::button_pressed?(id, button)
// Joystick::IsButtonPressed(id, button)
// Joystick::pressed?(id, button)
VALUE rbJoystick::IsButtonPressed( VALUE aSelf, VALUE anID, VALUE aButton )
{
    return RBOOL( sf::Joystick::IsButtonPressed( NUM2INT( anID ), NUM2INT( aButton ) ) );
}

// Joystick::axis_position(id, axis)
// Joystick::GetAxisPosition(id, axis)
VALUE rbJoystick::GetAxisPosition( VALUE aSelf, VALUE anID, VALUE anAxis )
{
    sf::Joystick::Axis a = static_cast< sf::Joystick::Axis >( NUM2INT( anAxis ) );
    return rb_float_new( sf::Joystick::GetAxisPosition( NUM2INT( anID ), a ) );
}

// Joystick::update
// Joystick::Update
VALUE rbJoystick::Update( VALUE aSelf )
{
    sf::Joystick::Update();
    return Qnil;
}
