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

#define WINDOW_MOUSE_CPP
#include "Mouse.hpp"

void rbMouse::Init(VALUE SFML)
{
    Mouse = rb_define_module_under(SFML, "Mouse");
    
	rb_define_const(Mouse, "Left",        INT2FIX(sf::Mouse::Left    ));
	rb_define_const(Mouse, "Right",       INT2FIX(sf::Mouse::Right   ));
	rb_define_const(Mouse, "Middle",      INT2FIX(sf::Mouse::Middle  ));
	rb_define_const(Mouse, "XButton1",    INT2FIX(sf::Mouse::XButton1));
	rb_define_const(Mouse, "XButton2",    INT2FIX(sf::Mouse::XButton2));
    
    rb_define_module_function(Mouse, "button_pressed?", IsButtonPressed, 1);
    rb_define_module_function(Mouse, "IsButtonPressed", IsButtonPressed, 1);
    rb_define_module_function(Mouse, "pressed?",        IsButtonPressed, 1);
    
    rb_define_module_function(Mouse, "position",    Position, -1);
    rb_define_module_function(Mouse, "GetPosition", Position, -1);
    rb_define_module_function(Mouse, "SetPosition", Position, -1);
    rb_define_module_function(Mouse, "position=",   Position, -1);
}

// Mouse::button_pressed?(button)
// Mouse::IsButtonPressed(button)
// Mouse::pressed?(button)
VALUE rbMouse::IsButtonPressed(VALUE, VALUE button)
{
    sf::Mouse::Button btn = static_cast<sf::Mouse::Button>(NUM2INT(button));
    return RBOOL(sf::Mouse::IsButtonPressed(btn));
}

// Mouse::position
// Mouse::GetPosition
// Mouse::position(relative_to)
// Mouse::GetPosition(relative_to)
// Mouse::position(position)
// Mouse::SetPosition(position)
// Mouse::position=(position)
// Mouse::position(position, relative_to)
// Mouse::SetPosition(position, relative_to)
// Mouse::position(x, y)
VALUE rbMouse::Position(int argc, VALUE argv[], VALUE)
{
    switch (argc)
    {
        case 0:
        {
            sf::Vector2i pos = sf::Mouse::GetPosition();
            return rbVector2::ToRuby(pos);
        }
        case 1:
            if (rb_obj_is_instance_of(argv[0], rbWindow::Window))
            {
                sf::Window* window = rbWindow::ToSFML(argv[0]);
                sf::Vector2i pos = sf::Mouse::GetPosition(*window);
                return rbVector2::ToRuby(pos);
            }
            else
            {
                sf::Vector2i vector2 = rbVector2::ToSFMLi(argv[0]);
                sf::Mouse::SetPosition(vector2);
            }
            break;
        case 2:
            if (rb_obj_is_instance_of(argv[1], rbWindow::Window))
            {
                sf::Vector2i vector2 = rbVector2::ToSFMLi(argv[0]);
                sf::Window* window = rbWindow::ToSFML(argv[1]);
                sf::Mouse::SetPosition(vector2, *window);
            }
            else
            {
                VALUE ary = rb_ary_new4(argc, argv);
                sf::Vector2i vector2 = rbVector2::ToSFMLi(ary);
                sf::Mouse::SetPosition(vector2);
            }
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..2)", argc);
    }
    
    return Qnil;
}
