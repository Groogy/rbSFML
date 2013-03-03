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
    ext_define_class_method( rbJoystick::Module, "connected?",      rbJoystick::IsConnected,     1 );
    ext_define_class_method( rbJoystick::Module, "button_count",    rbJoystick::GetButtonCount,  1 );
    ext_define_class_method( rbJoystick::Module, "axis?",           rbJoystick::HasAxis,         2 );
    ext_define_class_method( rbJoystick::Module, "button_pressed?", rbJoystick::IsButtonPressed, 2 );
    ext_define_class_method( rbJoystick::Module, "axis_position",   rbJoystick::GetAxisPosition, 2 );
    ext_define_class_method( rbJoystick::Module, "update",          rbJoystick::Update,          0 );
    
    // Singleton aliasses
    VALUE sJoystick = rb_singleton_class( rbJoystick::Module );
    rb_define_alias( sJoystick, "isConnected",        "connected?"      );
	rb_define_alias( sJoystick, "is_connected",       "connected?"      );
	rb_define_alias( sJoystick, "is_connected?",      "connected?"      );
    rb_define_alias( sJoystick, "getButtonCount",     "button_count"    );
	rb_define_alias( sJoystick, "get_button_count",   "button_count"    );
    rb_define_alias( sJoystick, "hasAxis",            "axis?"           );
    rb_define_alias( sJoystick, "has_axis?",          "axis?"           );
	rb_define_alias( sJoystick, "has_axis",           "axis?"           );
    rb_define_alias( sJoystick, "isButtonPressed",    "button_pressed?" );
    rb_define_alias( sJoystick, "pressed?",           "button_pressed?" );
	rb_define_alias( sJoystick, "is_button_pressed?", "button_pressed?" );
	rb_define_alias( sJoystick, "is_button_pressed",  "button_pressed?" );
    rb_define_alias( sJoystick, "getAxisPosition",    "axis_position"   );
	rb_define_alias( sJoystick, "get_axis_position",  "axis_position"   );
}

// Joystick.connected?(id)
// Joystick.isConnected(id)
// Joystick.is_connected?(id)
// Joystick.is_connected(id)
VALUE rbJoystick::IsConnected( VALUE aSelf, VALUE anID )
{
    return RBOOL( sf::Joystick::isConnected( NUM2INT( anID ) ) );
}

// Joystick.button_count(id)
// Joystick.getButtonCount(id)
// Joystick.get_button_count(id)
VALUE rbJoystick::GetButtonCount( VALUE aSelf, VALUE anID )
{
    return INT2FIX( sf::Joystick::getButtonCount( NUM2INT( anID ) ) );
}

// Joystick.axis?(id, axis)
// Joystick.HasAxis(id, axis)
// Joystick.has_axis?(id, axis)
// Joystick.has_axis(id, axis)
VALUE rbJoystick::HasAxis( VALUE aSelf, VALUE anID, VALUE anAxis )
{
    sf::Joystick::Axis a = static_cast< sf::Joystick::Axis >( NUM2INT( anAxis ) );
    return RBOOL( sf::Joystick::hasAxis( NUM2INT( anID ), a ) );
}

// Joystick.button_pressed?(id, button)
// Joystick.isButtonPressed(id, button)
// Joystick.is_button_pressed?(id, button)
// Joystick.is_button_pressed(id, button)
// Joystick.pressed?(id, button)
VALUE rbJoystick::IsButtonPressed( VALUE aSelf, VALUE anID, VALUE aButton )
{
    return RBOOL( sf::Joystick::isButtonPressed( NUM2INT( anID ), NUM2INT( aButton ) ) );
}

// Joystick.axis_position(id, axis)
// Joystick.getAxisPosition(id, axis)
// Joystick.get_axis_position(id, axis)
VALUE rbJoystick::GetAxisPosition( VALUE aSelf, VALUE anID, VALUE anAxis )
{
    sf::Joystick::Axis a = static_cast< sf::Joystick::Axis >( NUM2INT( anAxis ) );
    return rb_float_new( sf::Joystick::getAxisPosition( NUM2INT( anID ), a ) );
}

// Joystick.update
VALUE rbJoystick::Update( VALUE aSelf )
{
    sf::Joystick::update();
    return Qnil;
}
