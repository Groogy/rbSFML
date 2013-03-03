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

void rbKeyboard::Init( VALUE SFML )
{
    rbKeyboard::Module = rb_define_module_under( SFML, "Keyboard" );
    
    rb_define_const( rbKeyboard::Module, "A",         INT2FIX( sf::Keyboard::A        ) );
    rb_define_const( rbKeyboard::Module, "B",         INT2FIX( sf::Keyboard::B        ) );
    rb_define_const( rbKeyboard::Module, "C",         INT2FIX( sf::Keyboard::C        ) );
    rb_define_const( rbKeyboard::Module, "D",         INT2FIX( sf::Keyboard::D        ) );
    rb_define_const( rbKeyboard::Module, "E",         INT2FIX( sf::Keyboard::E        ) );
    rb_define_const( rbKeyboard::Module, "F",         INT2FIX( sf::Keyboard::F        ) );
    rb_define_const( rbKeyboard::Module, "G",         INT2FIX( sf::Keyboard::G        ) );
    rb_define_const( rbKeyboard::Module, "H",         INT2FIX( sf::Keyboard::H        ) );
    rb_define_const( rbKeyboard::Module, "I",         INT2FIX( sf::Keyboard::I        ) );
    rb_define_const( rbKeyboard::Module, "J",         INT2FIX( sf::Keyboard::J        ) );
    rb_define_const( rbKeyboard::Module, "K",         INT2FIX( sf::Keyboard::K        ) );
    rb_define_const( rbKeyboard::Module, "L",         INT2FIX( sf::Keyboard::L        ) );
    rb_define_const( rbKeyboard::Module, "M",         INT2FIX( sf::Keyboard::M        ) );
    rb_define_const( rbKeyboard::Module, "N",         INT2FIX( sf::Keyboard::N        ) );
    rb_define_const( rbKeyboard::Module, "O",         INT2FIX( sf::Keyboard::O        ) );
    rb_define_const( rbKeyboard::Module, "P",         INT2FIX( sf::Keyboard::P        ) );
    rb_define_const( rbKeyboard::Module, "Q",         INT2FIX( sf::Keyboard::Q        ) );
    rb_define_const( rbKeyboard::Module, "R",         INT2FIX( sf::Keyboard::R        ) );
    rb_define_const( rbKeyboard::Module, "S",         INT2FIX( sf::Keyboard::S        ) );
    rb_define_const( rbKeyboard::Module, "T",         INT2FIX( sf::Keyboard::T        ) );
    rb_define_const( rbKeyboard::Module, "U",         INT2FIX( sf::Keyboard::U        ) );
    rb_define_const( rbKeyboard::Module, "V",         INT2FIX( sf::Keyboard::V        ) );
    rb_define_const( rbKeyboard::Module, "W",         INT2FIX( sf::Keyboard::W        ) );
    rb_define_const( rbKeyboard::Module, "X",         INT2FIX( sf::Keyboard::X        ) );
    rb_define_const( rbKeyboard::Module, "Y",         INT2FIX( sf::Keyboard::Y        ) );
    rb_define_const( rbKeyboard::Module, "Z",         INT2FIX( sf::Keyboard::Z        ) );
    rb_define_const( rbKeyboard::Module, "Num0",      INT2FIX( sf::Keyboard::Num0     ) );
    rb_define_const( rbKeyboard::Module, "Num1",      INT2FIX( sf::Keyboard::Num1     ) );
    rb_define_const( rbKeyboard::Module, "Num2",      INT2FIX( sf::Keyboard::Num2     ) );
    rb_define_const( rbKeyboard::Module, "Num3",      INT2FIX( sf::Keyboard::Num3     ) );
    rb_define_const( rbKeyboard::Module, "Num4",      INT2FIX( sf::Keyboard::Num4     ) );
    rb_define_const( rbKeyboard::Module, "Num5",      INT2FIX( sf::Keyboard::Num5     ) );
    rb_define_const( rbKeyboard::Module, "Num6",      INT2FIX( sf::Keyboard::Num6     ) );
    rb_define_const( rbKeyboard::Module, "Num7",      INT2FIX( sf::Keyboard::Num7     ) );
    rb_define_const( rbKeyboard::Module, "Num8",      INT2FIX( sf::Keyboard::Num8     ) );
    rb_define_const( rbKeyboard::Module, "Num9",      INT2FIX( sf::Keyboard::Num9     ) );
    rb_define_const( rbKeyboard::Module, "Escape",    INT2FIX( sf::Keyboard::Escape   ) );
    rb_define_const( rbKeyboard::Module, "LControl",  INT2FIX( sf::Keyboard::LControl ) );
    rb_define_const( rbKeyboard::Module, "LShift",    INT2FIX( sf::Keyboard::LShift   ) );
    rb_define_const( rbKeyboard::Module, "LAlt",      INT2FIX( sf::Keyboard::LAlt     ) );
    rb_define_const( rbKeyboard::Module, "LSystem",   INT2FIX( sf::Keyboard::LSystem  ) );
    rb_define_const( rbKeyboard::Module, "RControl",  INT2FIX( sf::Keyboard::RControl ) );
    rb_define_const( rbKeyboard::Module, "RShift",    INT2FIX( sf::Keyboard::RShift   ) );
    rb_define_const( rbKeyboard::Module, "RAlt",      INT2FIX( sf::Keyboard::RAlt     ) );
    rb_define_const( rbKeyboard::Module, "RSystem",   INT2FIX( sf::Keyboard::RSystem  ) );
    rb_define_const( rbKeyboard::Module, "Menu",      INT2FIX( sf::Keyboard::Menu     ) );
    rb_define_const( rbKeyboard::Module, "LBracket",  INT2FIX( sf::Keyboard::LBracket ) );
    rb_define_const( rbKeyboard::Module, "RBracket",  INT2FIX( sf::Keyboard::RBracket ) );
    rb_define_const( rbKeyboard::Module, "SemiColon", INT2FIX( sf::Keyboard::SemiColon) );
    rb_define_const( rbKeyboard::Module, "Comma",     INT2FIX( sf::Keyboard::Comma    ) );
    rb_define_const( rbKeyboard::Module, "Period",    INT2FIX( sf::Keyboard::Period   ) );
    rb_define_const( rbKeyboard::Module, "Quote",     INT2FIX( sf::Keyboard::Quote    ) );
    rb_define_const( rbKeyboard::Module, "Slash",     INT2FIX( sf::Keyboard::Slash    ) );
    rb_define_const( rbKeyboard::Module, "BackSlash", INT2FIX( sf::Keyboard::BackSlash) );
    rb_define_const( rbKeyboard::Module, "Tilde",     INT2FIX( sf::Keyboard::Tilde    ) );
    rb_define_const( rbKeyboard::Module, "Equal",     INT2FIX( sf::Keyboard::Equal    ) );
    rb_define_const( rbKeyboard::Module, "Dash",      INT2FIX( sf::Keyboard::Dash     ) );
    rb_define_const( rbKeyboard::Module, "Space",     INT2FIX( sf::Keyboard::Space    ) );
    rb_define_const( rbKeyboard::Module, "Return",    INT2FIX( sf::Keyboard::Return   ) );
    rb_define_const( rbKeyboard::Module, "BackSpace", INT2FIX( sf::Keyboard::BackSpace) );
    rb_define_const( rbKeyboard::Module, "Tab",       INT2FIX( sf::Keyboard::Tab      ) );
    rb_define_const( rbKeyboard::Module, "PageUp",    INT2FIX( sf::Keyboard::PageUp   ) );
    rb_define_const( rbKeyboard::Module, "PageDown",  INT2FIX( sf::Keyboard::PageDown ) );
    rb_define_const( rbKeyboard::Module, "End",       INT2FIX( sf::Keyboard::End      ) );
    rb_define_const( rbKeyboard::Module, "Home",      INT2FIX( sf::Keyboard::Home     ) );
    rb_define_const( rbKeyboard::Module, "Insert",    INT2FIX( sf::Keyboard::Insert   ) );
    rb_define_const( rbKeyboard::Module, "Delete",    INT2FIX( sf::Keyboard::Delete   ) );
    rb_define_const( rbKeyboard::Module, "Add",       INT2FIX( sf::Keyboard::Add      ) );
    rb_define_const( rbKeyboard::Module, "Subtract",  INT2FIX( sf::Keyboard::Subtract ) );
    rb_define_const( rbKeyboard::Module, "Multiply",  INT2FIX( sf::Keyboard::Multiply ) );
    rb_define_const( rbKeyboard::Module, "Divide",    INT2FIX( sf::Keyboard::Divide   ) );
    rb_define_const( rbKeyboard::Module, "Left",      INT2FIX( sf::Keyboard::Left     ) );
    rb_define_const( rbKeyboard::Module, "Right",     INT2FIX( sf::Keyboard::Right    ) );
    rb_define_const( rbKeyboard::Module, "Up",        INT2FIX( sf::Keyboard::Up       ) );
    rb_define_const( rbKeyboard::Module, "Down",      INT2FIX( sf::Keyboard::Down     ) );
    rb_define_const( rbKeyboard::Module, "Numpad0",   INT2FIX( sf::Keyboard::Numpad0  ) );
    rb_define_const( rbKeyboard::Module, "Numpad1",   INT2FIX( sf::Keyboard::Numpad1  ) );
    rb_define_const( rbKeyboard::Module, "Numpad2",   INT2FIX( sf::Keyboard::Numpad2  ) );
    rb_define_const( rbKeyboard::Module, "Numpad3",   INT2FIX( sf::Keyboard::Numpad3  ) );
    rb_define_const( rbKeyboard::Module, "Numpad4",   INT2FIX( sf::Keyboard::Numpad4  ) );
    rb_define_const( rbKeyboard::Module, "Numpad5",   INT2FIX( sf::Keyboard::Numpad5  ) );
    rb_define_const( rbKeyboard::Module, "Numpad6",   INT2FIX( sf::Keyboard::Numpad6  ) );
    rb_define_const( rbKeyboard::Module, "Numpad7",   INT2FIX( sf::Keyboard::Numpad7  ) );
    rb_define_const( rbKeyboard::Module, "Numpad8",   INT2FIX( sf::Keyboard::Numpad8  ) );
    rb_define_const( rbKeyboard::Module, "Numpad9",   INT2FIX( sf::Keyboard::Numpad9  ) );
    rb_define_const( rbKeyboard::Module, "F1",        INT2FIX( sf::Keyboard::F1       ) );
    rb_define_const( rbKeyboard::Module, "F2",        INT2FIX( sf::Keyboard::F2       ) );
    rb_define_const( rbKeyboard::Module, "F3",        INT2FIX( sf::Keyboard::F3       ) );
    rb_define_const( rbKeyboard::Module, "F4",        INT2FIX( sf::Keyboard::F4       ) );
    rb_define_const( rbKeyboard::Module, "F5",        INT2FIX( sf::Keyboard::F5       ) );
    rb_define_const( rbKeyboard::Module, "F6",        INT2FIX( sf::Keyboard::F6       ) );
    rb_define_const( rbKeyboard::Module, "F7",        INT2FIX( sf::Keyboard::F7       ) );
    rb_define_const( rbKeyboard::Module, "F8",        INT2FIX( sf::Keyboard::F8       ) );
    rb_define_const( rbKeyboard::Module, "F9",        INT2FIX( sf::Keyboard::F9       ) );
    rb_define_const( rbKeyboard::Module, "F10",       INT2FIX( sf::Keyboard::F10      ) );
    rb_define_const( rbKeyboard::Module, "F11",       INT2FIX( sf::Keyboard::F11      ) );
    rb_define_const( rbKeyboard::Module, "F12",       INT2FIX( sf::Keyboard::F12      ) );
    rb_define_const( rbKeyboard::Module, "F13",       INT2FIX( sf::Keyboard::F13      ) );
    rb_define_const( rbKeyboard::Module, "F14",       INT2FIX( sf::Keyboard::F14      ) );
    rb_define_const( rbKeyboard::Module, "F15",       INT2FIX( sf::Keyboard::F15      ) );
    rb_define_const( rbKeyboard::Module, "Pause",     INT2FIX( sf::Keyboard::Pause    ) );
    
    // Singleton methods
    ext_define_class_method( rbKeyboard::Module, "key_pressed?", rbKeyboard::IsKeyPressed, 1 );
    
    // Singleton aliasses
    VALUE sKeyboard = rb_singleton_class( rbKeyboard::Module );
    rb_define_alias( sKeyboard, "isKeyPressed",    "key_pressed?" );
	rb_define_alias( sKeyboard, "is_key_pressed?", "key_pressed?" );
	rb_define_alias( sKeyboard, "is_key_pressed",  "key_pressed?" );
    rb_define_alias( sKeyboard, "pressed?",        "key_pressed?" );
}

// Keyboard.key_pressed?(button)
// Keyboard.isKeyPressed(button)
// Keyboard.is_key_pressed?(button)
// Keyboard.is_key_pressed(button)
// Keyboard.pressed?(button)
VALUE rbKeyboard::IsKeyPressed( VALUE self, VALUE key )
{
    sf::Keyboard::Key k = static_cast< sf::Keyboard::Key >( NUM2INT( key ) );
    return RBOOL( sf::Keyboard::isKeyPressed( k ) );
}
