/* rbSFML
 * Copyright (c) 2015 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#include "rbkeyboard.hpp"
#include "error.hpp"
#include "macros.hpp"

rbKeyboardModule rbKeyboard::ourDefinition;

void rbKeyboard::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbKeyboardModule::defineModuleUnder("Keyboard", sfml);
	ourDefinition.defineFunction<0>("key_pressed?", &sf::Keyboard::isKeyPressed);
	ourDefinition.defineFunction<1>("virtual_keyboard_visible=", &sf::Keyboard::setVirtualKeyboardVisible);

	ourDefinition.defineConstant("Unknown", rb::Value(sf::Keyboard::Unknown));
	ourDefinition.defineConstant("A", rb::Value(sf::Keyboard::A));
	ourDefinition.defineConstant("B", rb::Value(sf::Keyboard::B));
	ourDefinition.defineConstant("C", rb::Value(sf::Keyboard::C));
	ourDefinition.defineConstant("D", rb::Value(sf::Keyboard::D));
	ourDefinition.defineConstant("E", rb::Value(sf::Keyboard::E));
	ourDefinition.defineConstant("F", rb::Value(sf::Keyboard::F));
	ourDefinition.defineConstant("G", rb::Value(sf::Keyboard::G));
	ourDefinition.defineConstant("H", rb::Value(sf::Keyboard::H));
	ourDefinition.defineConstant("I", rb::Value(sf::Keyboard::I));
	ourDefinition.defineConstant("J", rb::Value(sf::Keyboard::J));
	ourDefinition.defineConstant("K", rb::Value(sf::Keyboard::K));
	ourDefinition.defineConstant("L", rb::Value(sf::Keyboard::L));
	ourDefinition.defineConstant("M", rb::Value(sf::Keyboard::M));
	ourDefinition.defineConstant("N", rb::Value(sf::Keyboard::N));
	ourDefinition.defineConstant("O", rb::Value(sf::Keyboard::O));
	ourDefinition.defineConstant("P", rb::Value(sf::Keyboard::P));
	ourDefinition.defineConstant("Q", rb::Value(sf::Keyboard::Q));
	ourDefinition.defineConstant("R", rb::Value(sf::Keyboard::R));
	ourDefinition.defineConstant("S", rb::Value(sf::Keyboard::S));
	ourDefinition.defineConstant("T", rb::Value(sf::Keyboard::T));
	ourDefinition.defineConstant("U", rb::Value(sf::Keyboard::U));
	ourDefinition.defineConstant("V", rb::Value(sf::Keyboard::V));
	ourDefinition.defineConstant("W", rb::Value(sf::Keyboard::W));
	ourDefinition.defineConstant("X", rb::Value(sf::Keyboard::X));
	ourDefinition.defineConstant("Y", rb::Value(sf::Keyboard::Y));
	ourDefinition.defineConstant("Z", rb::Value(sf::Keyboard::Z));
	ourDefinition.defineConstant("Num0", rb::Value(sf::Keyboard::Num0));
	ourDefinition.defineConstant("Num1", rb::Value(sf::Keyboard::Num1));
	ourDefinition.defineConstant("Num2", rb::Value(sf::Keyboard::Num2));
	ourDefinition.defineConstant("Num3", rb::Value(sf::Keyboard::Num3));
	ourDefinition.defineConstant("Num4", rb::Value(sf::Keyboard::Num4));
	ourDefinition.defineConstant("Num5", rb::Value(sf::Keyboard::Num5));
	ourDefinition.defineConstant("Num6", rb::Value(sf::Keyboard::Num6));
	ourDefinition.defineConstant("Num7", rb::Value(sf::Keyboard::Num7));
	ourDefinition.defineConstant("Num8", rb::Value(sf::Keyboard::Num8));
	ourDefinition.defineConstant("Num9", rb::Value(sf::Keyboard::Num9));
	ourDefinition.defineConstant("Escape", rb::Value(sf::Keyboard::Escape));
	ourDefinition.defineConstant("LControl", rb::Value(sf::Keyboard::LControl));
	ourDefinition.defineConstant("LShift", rb::Value(sf::Keyboard::LShift));
	ourDefinition.defineConstant("LAlt", rb::Value(sf::Keyboard::LAlt));
	ourDefinition.defineConstant("LSystem", rb::Value(sf::Keyboard::LSystem));
	ourDefinition.defineConstant("RControl", rb::Value(sf::Keyboard::RControl));
	ourDefinition.defineConstant("RShift", rb::Value(sf::Keyboard::RShift));
	ourDefinition.defineConstant("RAlt", rb::Value(sf::Keyboard::RAlt));
	ourDefinition.defineConstant("RSystem", rb::Value(sf::Keyboard::RSystem));
	ourDefinition.defineConstant("Menu", rb::Value(sf::Keyboard::Menu));
	ourDefinition.defineConstant("LBracket", rb::Value(sf::Keyboard::LBracket));
	ourDefinition.defineConstant("RBracket", rb::Value(sf::Keyboard::RBracket));
	ourDefinition.defineConstant("SemiColon", rb::Value(sf::Keyboard::SemiColon));
	ourDefinition.defineConstant("Comma", rb::Value(sf::Keyboard::Comma));
	ourDefinition.defineConstant("Period", rb::Value(sf::Keyboard::Period));
	ourDefinition.defineConstant("Quote", rb::Value(sf::Keyboard::Quote));
	ourDefinition.defineConstant("Slash", rb::Value(sf::Keyboard::Slash));
	ourDefinition.defineConstant("BackSlash", rb::Value(sf::Keyboard::BackSlash));
	ourDefinition.defineConstant("Tilde", rb::Value(sf::Keyboard::Tilde));
	ourDefinition.defineConstant("Equal", rb::Value(sf::Keyboard::Equal));
	ourDefinition.defineConstant("Dash", rb::Value(sf::Keyboard::Dash));
	ourDefinition.defineConstant("Space", rb::Value(sf::Keyboard::Space));
	ourDefinition.defineConstant("Return", rb::Value(sf::Keyboard::Return));
	ourDefinition.defineConstant("BackSpace", rb::Value(sf::Keyboard::BackSpace));
	ourDefinition.defineConstant("Tab", rb::Value(sf::Keyboard::Tab));
	ourDefinition.defineConstant("PageUp", rb::Value(sf::Keyboard::PageUp));
	ourDefinition.defineConstant("PageDown", rb::Value(sf::Keyboard::PageDown));
	ourDefinition.defineConstant("End", rb::Value(sf::Keyboard::End));
	ourDefinition.defineConstant("Home", rb::Value(sf::Keyboard::Home));
	ourDefinition.defineConstant("Insert", rb::Value(sf::Keyboard::Insert));
	ourDefinition.defineConstant("Delete", rb::Value(sf::Keyboard::Delete));
	ourDefinition.defineConstant("Add", rb::Value(sf::Keyboard::Add));
	ourDefinition.defineConstant("Subtract", rb::Value(sf::Keyboard::Subtract));
	ourDefinition.defineConstant("Multiply", rb::Value(sf::Keyboard::Multiply));
	ourDefinition.defineConstant("Divide", rb::Value(sf::Keyboard::Divide));
	ourDefinition.defineConstant("Left", rb::Value(sf::Keyboard::Left));
	ourDefinition.defineConstant("Right", rb::Value(sf::Keyboard::Right));
	ourDefinition.defineConstant("Up", rb::Value(sf::Keyboard::Up));
	ourDefinition.defineConstant("Down", rb::Value(sf::Keyboard::Down));
	ourDefinition.defineConstant("Numpad0", rb::Value(sf::Keyboard::Numpad0));
	ourDefinition.defineConstant("Numpad1", rb::Value(sf::Keyboard::Numpad1));
	ourDefinition.defineConstant("Numpad2", rb::Value(sf::Keyboard::Numpad2));
	ourDefinition.defineConstant("Numpad3", rb::Value(sf::Keyboard::Numpad3));
	ourDefinition.defineConstant("Numpad4", rb::Value(sf::Keyboard::Numpad4));
	ourDefinition.defineConstant("Numpad5", rb::Value(sf::Keyboard::Numpad5));
	ourDefinition.defineConstant("Numpad6", rb::Value(sf::Keyboard::Numpad6));
	ourDefinition.defineConstant("Numpad7", rb::Value(sf::Keyboard::Numpad7));
	ourDefinition.defineConstant("Numpad8", rb::Value(sf::Keyboard::Numpad8));
	ourDefinition.defineConstant("Numpad9", rb::Value(sf::Keyboard::Numpad9));
	ourDefinition.defineConstant("F1", rb::Value(sf::Keyboard::F1));
	ourDefinition.defineConstant("F2", rb::Value(sf::Keyboard::F2));
	ourDefinition.defineConstant("F3", rb::Value(sf::Keyboard::F3));
	ourDefinition.defineConstant("F4", rb::Value(sf::Keyboard::F4));
	ourDefinition.defineConstant("F5", rb::Value(sf::Keyboard::F5));
	ourDefinition.defineConstant("F6", rb::Value(sf::Keyboard::F6));
	ourDefinition.defineConstant("F7", rb::Value(sf::Keyboard::F7));
	ourDefinition.defineConstant("F8", rb::Value(sf::Keyboard::F8));
	ourDefinition.defineConstant("F9", rb::Value(sf::Keyboard::F9));
	ourDefinition.defineConstant("F10", rb::Value(sf::Keyboard::F10));
	ourDefinition.defineConstant("F11", rb::Value(sf::Keyboard::F11));
	ourDefinition.defineConstant("F12", rb::Value(sf::Keyboard::F12));
	ourDefinition.defineConstant("F13", rb::Value(sf::Keyboard::F13));
	ourDefinition.defineConstant("F14", rb::Value(sf::Keyboard::F14));
	ourDefinition.defineConstant("F15", rb::Value(sf::Keyboard::F15));
	ourDefinition.defineConstant("Pause", rb::Value(sf::Keyboard::Pause));
	ourDefinition.defineConstant("KeyCount", rb::Value(sf::Keyboard::KeyCount));
}

namespace rb
{
template<>
sf::Keyboard::Key Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::Keyboard::Key>(value);
}

template<>
Value Value::create( sf::Keyboard::Key value )
{
	return create(static_cast<unsigned int>(value));
}

}