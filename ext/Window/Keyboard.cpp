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
 * 1. The origin of this software must not be misrepresented;you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#define WINDOW_KEYBOARD_CPP
#include "Keyboard.hpp"

void rbKeyboard::Init(VALUE SFML)
{
    Keyboard = rb_define_module_under(SFML, "Keyboard");
    
    rb_define_const(Keyboard, "A",         INT2FIX(sf::Keyboard::A        ));
    rb_define_const(Keyboard, "B",         INT2FIX(sf::Keyboard::B        ));
    rb_define_const(Keyboard, "C",         INT2FIX(sf::Keyboard::C        ));
    rb_define_const(Keyboard, "D",         INT2FIX(sf::Keyboard::D        ));
    rb_define_const(Keyboard, "E",         INT2FIX(sf::Keyboard::E        ));
    rb_define_const(Keyboard, "F",         INT2FIX(sf::Keyboard::F        ));
    rb_define_const(Keyboard, "G",         INT2FIX(sf::Keyboard::G        ));
    rb_define_const(Keyboard, "H",         INT2FIX(sf::Keyboard::H        ));
    rb_define_const(Keyboard, "I",         INT2FIX(sf::Keyboard::I        ));
    rb_define_const(Keyboard, "J",         INT2FIX(sf::Keyboard::J        ));
    rb_define_const(Keyboard, "K",         INT2FIX(sf::Keyboard::K        ));
    rb_define_const(Keyboard, "L",         INT2FIX(sf::Keyboard::L        ));
    rb_define_const(Keyboard, "M",         INT2FIX(sf::Keyboard::M        ));
    rb_define_const(Keyboard, "N",         INT2FIX(sf::Keyboard::N        ));
    rb_define_const(Keyboard, "O",         INT2FIX(sf::Keyboard::O        ));
    rb_define_const(Keyboard, "P",         INT2FIX(sf::Keyboard::P        ));
    rb_define_const(Keyboard, "Q",         INT2FIX(sf::Keyboard::Q        ));
    rb_define_const(Keyboard, "R",         INT2FIX(sf::Keyboard::R        ));
    rb_define_const(Keyboard, "S",         INT2FIX(sf::Keyboard::S        ));
    rb_define_const(Keyboard, "T",         INT2FIX(sf::Keyboard::T        ));
    rb_define_const(Keyboard, "U",         INT2FIX(sf::Keyboard::U        ));
    rb_define_const(Keyboard, "V",         INT2FIX(sf::Keyboard::V        ));
    rb_define_const(Keyboard, "W",         INT2FIX(sf::Keyboard::W        ));
    rb_define_const(Keyboard, "X",         INT2FIX(sf::Keyboard::X        ));
    rb_define_const(Keyboard, "Y",         INT2FIX(sf::Keyboard::Y        ));
    rb_define_const(Keyboard, "Z",         INT2FIX(sf::Keyboard::Z        ));
    rb_define_const(Keyboard, "Num0",      INT2FIX(sf::Keyboard::Num0     ));
    rb_define_const(Keyboard, "Num1",      INT2FIX(sf::Keyboard::Num1     ));
    rb_define_const(Keyboard, "Num2",      INT2FIX(sf::Keyboard::Num2     ));
    rb_define_const(Keyboard, "Num3",      INT2FIX(sf::Keyboard::Num3     ));
    rb_define_const(Keyboard, "Num4",      INT2FIX(sf::Keyboard::Num4     ));
    rb_define_const(Keyboard, "Num5",      INT2FIX(sf::Keyboard::Num5     ));
    rb_define_const(Keyboard, "Num6",      INT2FIX(sf::Keyboard::Num6     ));
    rb_define_const(Keyboard, "Num7",      INT2FIX(sf::Keyboard::Num7     ));
    rb_define_const(Keyboard, "Num8",      INT2FIX(sf::Keyboard::Num8     ));
    rb_define_const(Keyboard, "Num9",      INT2FIX(sf::Keyboard::Num9     ));
    rb_define_const(Keyboard, "Escape",    INT2FIX(sf::Keyboard::Escape   ));
    rb_define_const(Keyboard, "LControl",  INT2FIX(sf::Keyboard::LControl ));
    rb_define_const(Keyboard, "LShift",    INT2FIX(sf::Keyboard::LShift   ));
    rb_define_const(Keyboard, "LAlt",      INT2FIX(sf::Keyboard::LAlt     ));
    rb_define_const(Keyboard, "LSystem",   INT2FIX(sf::Keyboard::LSystem  ));
    rb_define_const(Keyboard, "RControl",  INT2FIX(sf::Keyboard::RControl ));
    rb_define_const(Keyboard, "RShift",    INT2FIX(sf::Keyboard::RShift   ));
    rb_define_const(Keyboard, "RAlt",      INT2FIX(sf::Keyboard::RAlt     ));
    rb_define_const(Keyboard, "RSystem",   INT2FIX(sf::Keyboard::RSystem  ));
    rb_define_const(Keyboard, "Menu",      INT2FIX(sf::Keyboard::Menu     ));
    rb_define_const(Keyboard, "LBracket",  INT2FIX(sf::Keyboard::LBracket ));
    rb_define_const(Keyboard, "RBracket",  INT2FIX(sf::Keyboard::RBracket ));
    rb_define_const(Keyboard, "SemiColon", INT2FIX(sf::Keyboard::SemiColon));
    rb_define_const(Keyboard, "Comma",     INT2FIX(sf::Keyboard::Comma    ));
    rb_define_const(Keyboard, "Period",    INT2FIX(sf::Keyboard::Period   ));
    rb_define_const(Keyboard, "Quote",     INT2FIX(sf::Keyboard::Quote    ));
    rb_define_const(Keyboard, "Slash",     INT2FIX(sf::Keyboard::Slash    ));
    rb_define_const(Keyboard, "BackSlash", INT2FIX(sf::Keyboard::BackSlash));
    rb_define_const(Keyboard, "Tilde",     INT2FIX(sf::Keyboard::Tilde    ));
    rb_define_const(Keyboard, "Equal",     INT2FIX(sf::Keyboard::Equal    ));
    rb_define_const(Keyboard, "Dash",      INT2FIX(sf::Keyboard::Dash     ));
    rb_define_const(Keyboard, "Space",     INT2FIX(sf::Keyboard::Space    ));
    rb_define_const(Keyboard, "Return",    INT2FIX(sf::Keyboard::Return   ));
    rb_define_const(Keyboard, "Back",      INT2FIX(sf::Keyboard::Back     ));
    rb_define_const(Keyboard, "Tab",       INT2FIX(sf::Keyboard::Tab      ));
    rb_define_const(Keyboard, "PageUp",    INT2FIX(sf::Keyboard::PageUp   ));
    rb_define_const(Keyboard, "PageDown",  INT2FIX(sf::Keyboard::PageDown ));
    rb_define_const(Keyboard, "End",       INT2FIX(sf::Keyboard::End      ));
    rb_define_const(Keyboard, "Home",      INT2FIX(sf::Keyboard::Home     ));
    rb_define_const(Keyboard, "Insert",    INT2FIX(sf::Keyboard::Insert   ));
    rb_define_const(Keyboard, "Delete",    INT2FIX(sf::Keyboard::Delete   ));
    rb_define_const(Keyboard, "Add",       INT2FIX(sf::Keyboard::Add      ));
    rb_define_const(Keyboard, "Subtract",  INT2FIX(sf::Keyboard::Subtract ));
    rb_define_const(Keyboard, "Multiply",  INT2FIX(sf::Keyboard::Multiply ));
    rb_define_const(Keyboard, "Divide",    INT2FIX(sf::Keyboard::Divide   ));
    rb_define_const(Keyboard, "Left",      INT2FIX(sf::Keyboard::Left     ));
    rb_define_const(Keyboard, "Right",     INT2FIX(sf::Keyboard::Right    ));
    rb_define_const(Keyboard, "Up",        INT2FIX(sf::Keyboard::Up       ));
    rb_define_const(Keyboard, "Down",      INT2FIX(sf::Keyboard::Down     ));
    rb_define_const(Keyboard, "Numpad0",   INT2FIX(sf::Keyboard::Numpad0  ));
    rb_define_const(Keyboard, "Numpad1",   INT2FIX(sf::Keyboard::Numpad1  ));
    rb_define_const(Keyboard, "Numpad2",   INT2FIX(sf::Keyboard::Numpad2  ));
    rb_define_const(Keyboard, "Numpad3",   INT2FIX(sf::Keyboard::Numpad3  ));
    rb_define_const(Keyboard, "Numpad4",   INT2FIX(sf::Keyboard::Numpad4  ));
    rb_define_const(Keyboard, "Numpad5",   INT2FIX(sf::Keyboard::Numpad5  ));
    rb_define_const(Keyboard, "Numpad6",   INT2FIX(sf::Keyboard::Numpad6  ));
    rb_define_const(Keyboard, "Numpad7",   INT2FIX(sf::Keyboard::Numpad7  ));
    rb_define_const(Keyboard, "Numpad8",   INT2FIX(sf::Keyboard::Numpad8  ));
    rb_define_const(Keyboard, "Numpad9",   INT2FIX(sf::Keyboard::Numpad9  ));
    rb_define_const(Keyboard, "F1",        INT2FIX(sf::Keyboard::F1       ));
    rb_define_const(Keyboard, "F2",        INT2FIX(sf::Keyboard::F2       ));
    rb_define_const(Keyboard, "F3",        INT2FIX(sf::Keyboard::F3       ));
    rb_define_const(Keyboard, "F4",        INT2FIX(sf::Keyboard::F4       ));
    rb_define_const(Keyboard, "F5",        INT2FIX(sf::Keyboard::F5       ));
    rb_define_const(Keyboard, "F6",        INT2FIX(sf::Keyboard::F6       ));
    rb_define_const(Keyboard, "F7",        INT2FIX(sf::Keyboard::F7       ));
    rb_define_const(Keyboard, "F8",        INT2FIX(sf::Keyboard::F8       ));
    rb_define_const(Keyboard, "F9",        INT2FIX(sf::Keyboard::F9       ));
    rb_define_const(Keyboard, "F10",       INT2FIX(sf::Keyboard::F10      ));
    rb_define_const(Keyboard, "F11",       INT2FIX(sf::Keyboard::F11      ));
    rb_define_const(Keyboard, "F12",       INT2FIX(sf::Keyboard::F12      ));
    rb_define_const(Keyboard, "F13",       INT2FIX(sf::Keyboard::F13      ));
    rb_define_const(Keyboard, "F14",       INT2FIX(sf::Keyboard::F14      ));
    rb_define_const(Keyboard, "F15",       INT2FIX(sf::Keyboard::F15      ));
    rb_define_const(Keyboard, "Pause",     INT2FIX(sf::Keyboard::Pause    ));
    
    // Singleton methods
    rb_define_singleton_method(Keyboard, "key_pressed?", IsKeyPressed, 1);
    
    // Singleton aliasses
    VALUE sKeyboard = rb_singleton_class(Keyboard);
    rb_define_alias(sKeyboard, "IsKeyPressed", "key_pressed?");
    rb_define_alias(sKeyboard, "pressed?",     "key_pressed?");
}

// Keyboard::key_pressed?(button)
// Keyboard::IsKeyPressed(button)
// Keyboard::pressed?(button)
VALUE rbKeyboard::IsKeyPressed(VALUE self, VALUE key)
{
    sf::Keyboard::Key k = static_cast<sf::Keyboard::Key>(NUM2INT(key));
    return RBOOL(sf::Keyboard::IsKeyPressed(k));
}
