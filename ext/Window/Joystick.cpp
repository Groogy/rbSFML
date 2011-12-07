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

void rbJoystick::Init(VALUE SFML)
{
    Joystick = rb_define_module_under(SFML, "Joystick");
    
	rb_define_const(Joystick, "X",           INT2FIX(sf::Joystick::X          ));
	rb_define_const(Joystick, "Y",           INT2FIX(sf::Joystick::Y          ));
	rb_define_const(Joystick, "Z",           INT2FIX(sf::Joystick::Z          ));
	rb_define_const(Joystick, "R",           INT2FIX(sf::Joystick::R          ));
	rb_define_const(Joystick, "U",           INT2FIX(sf::Joystick::U          ));
	rb_define_const(Joystick, "V",           INT2FIX(sf::Joystick::V          ));
	rb_define_const(Joystick, "PovX",        INT2FIX(sf::Joystick::PovX       ));
	rb_define_const(Joystick, "PovY",        INT2FIX(sf::Joystick::PovY       ));
	rb_define_const(Joystick, "Count",       INT2FIX(sf::Joystick::Count      ));
	rb_define_const(Joystick, "AxisCount",   INT2FIX(sf::Joystick::AxisCount  ));
	rb_define_const(Joystick, "ButtonCount", INT2FIX(sf::Joystick::ButtonCount));
    
    // Singleton methods
    rb_define_singleton_method(Joystick, "connected?",      IsConnected,     1);
    rb_define_singleton_method(Joystick, "button_count",    GetButtonCount,  1);
    rb_define_singleton_method(Joystick, "axis?",           HasAxis,         2);
    rb_define_singleton_method(Joystick, "button_pressed?", IsButtonPressed, 2);
    rb_define_singleton_method(Joystick, "axis_position",   GetAxisPosition, 2);
    rb_define_singleton_method(Joystick, "update",          Update,          0);
    
    // Singleton aliasses
    VALUE sJoystick = rb_singleton_class(Joystick);
    rb_define_alias(sJoystick, "IsConnected",     "connected?"     );
    rb_define_alias(sJoystick, "GetButtonCount",  "button_count"   );
    rb_define_alias(sJoystick, "HasAxis",         "axis?"          );
    rb_define_alias(sJoystick, "has_axis",        "axis?"          );
    rb_define_alias(sJoystick, "IsButtonPressed", "button_pressed?");
    rb_define_alias(sJoystick, "pressed?",        "button_pressed?");
    rb_define_alias(sJoystick, "GetAxisPosition", "axis_position"  );
    rb_define_alias(sJoystick, "Update",          "update"         );
}

// Joystick::connected?(id)
// Joystick::IsConnected(id)
VALUE rbJoystick::IsConnected(VALUE self, VALUE id)
{
    return RBOOL(sf::Joystick::IsConnected(NUM2INT(id)));
}

// Joystick::button_count(id)
// Joystick::GetButtonCount(id)
VALUE rbJoystick::GetButtonCount(VALUE self, VALUE id)
{
    return INT2FIX(sf::Joystick::GetButtonCount(NUM2INT(id)));
}

// Joystick::axis?(id, axis)
// Joystick::HasAxis(id, axis)
// Joystick::has_axis(id, axis)
VALUE rbJoystick::HasAxis(VALUE self, VALUE id, VALUE axis)
{
    sf::Joystick::Axis a = static_cast<sf::Joystick::Axis>(NUM2INT(axis));
    return RBOOL(sf::Joystick::HasAxis(NUM2INT(id), a));
}

// Joystick::button_pressed?(id, button)
// Joystick::IsButtonPressed(id, button)
// Joystick::pressed?(id, button)
VALUE rbJoystick::IsButtonPressed(VALUE self, VALUE id, VALUE button)
{
    return RBOOL(sf::Joystick::IsButtonPressed(NUM2INT(id), NUM2INT(button)));
}

// Joystick::axis_position(id, axis)
// Joystick::GetAxisPosition(id, axis)
VALUE rbJoystick::GetAxisPosition(VALUE self, VALUE id, VALUE axis)
{
    sf::Joystick::Axis a = static_cast<sf::Joystick::Axis>(NUM2INT(axis));
    return rb_float_new(sf::Joystick::GetAxisPosition(NUM2INT(id), a));
}

// Joystick::update
// Joystick::Update
VALUE rbJoystick::Update(VALUE self)
{
    sf::Joystick::Update();
    return Qnil;
}
