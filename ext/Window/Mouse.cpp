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

void rbMouse::Init( VALUE SFML )
{
    rbMouse::Module = rb_define_module_under( SFML, "Mouse" );
    
    rb_define_const( rbMouse::Module, "Left",        INT2FIX( sf::Mouse::Left     ) );
    rb_define_const( rbMouse::Module, "Right",       INT2FIX( sf::Mouse::Right    ) );
    rb_define_const( rbMouse::Module, "Middle",      INT2FIX( sf::Mouse::Middle   ) );
    rb_define_const( rbMouse::Module, "XButton1",    INT2FIX( sf::Mouse::XButton1 ) );
    rb_define_const( rbMouse::Module, "XButton2",    INT2FIX( sf::Mouse::XButton2 ) );
    
    // Singleton methods
    ext_define_class_method( rbMouse::Module, "button_pressed?",  rbMouse::IsButtonPressed,  1 );
    ext_define_class_method( rbMouse::Module, "get_position",     rbMouse::GetPosition,     -1 );
    ext_define_class_method( rbMouse::Module, "set_position",     rbMouse::SetPosition,     -1 );
    
    // Singleton aliasses
    VALUE sMouse = rb_singleton_class( rbMouse::Module );
    rb_define_alias( sMouse, "isButtonPressed",    "button_pressed?" );
	rb_define_alias( sMouse, "is_button_pressed?", "button_pressed?" );
	rb_define_alias( sMouse, "is_button_pressed",  "button_pressed?" );
    rb_define_alias( sMouse, "pressed?",           "button_pressed?" );
	rb_define_alias( sMouse, "position",		   "get_position"    );
	rb_define_alias( sMouse, "getPosition",		   "get_position"    );
    rb_define_alias( sMouse, "position=",          "set_position"    );
	rb_define_alias( sMouse, "setPosition",        "set_position"    );
}

// Mouse.button_pressed?(button)
// Mouse.isButtonPressed(button)
// Mouse.is_button_pressed?(button)
// Mouse.is_button_pressed(button)
// Mouse.pressed?(button)
VALUE rbMouse::IsButtonPressed( VALUE aSelf, VALUE aButton )
{
    sf::Mouse::Button btn = static_cast< sf::Mouse::Button >( NUM2INT( aButton ) );
    return RBOOL( sf::Mouse::isButtonPressed( btn ) );
}

// Mouse.position
// Mouse.getPosition
// Mouse.get_position
// Mouse.position(relative_to)
// Mouse.getPosition(relative_to)
// Mouse.get_position(relative_to)
VALUE rbMouse::GetPosition( int argc, VALUE argv[], VALUE aSelf )
{
    sf::Vector2i pos;
    switch( argc )
    {
        case 0:
            pos = sf::Mouse::getPosition();
			break;
        case 1:
            pos = sf::Mouse::getPosition( *rbMacros::ToSFML< sf::Window >( argv[0], rbWindow::Class ) );
			break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..1)", argc );
    }
    return rbVector2::ToRuby( pos );
}

// Mouse.position=(position)
// Mouse.set_position(poition)
// Mouse.setPosition(position)
// Mouse.set_position(position, relative_to)
// Mouse.setPosition(position, relative_to)
VALUE rbMouse::SetPosition( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 1:
        {
            sf::Vector2i pos = rbVector2::ToSFMLi( argv[ 0 ] );
            sf::Mouse::setPosition( pos );
            break;
        }
        case 2:
        {
            sf::Vector2i pos = rbVector2::ToSFMLi( argv[ 0 ] );
            sf::Window* window = rbMacros::ToSFML< sf::Window >( argv[ 1 ], rbWindow::Class );
            sf::Mouse::setPosition( pos, *window );
            break;
        }
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 1..2)", argc );
    }
    return Qnil;
}
