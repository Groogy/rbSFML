/* rbSFML - Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 */
 
#include "Keyboard.hpp"
#include "main.hpp"
#include <SFML/Window/Keyboard.hpp>

VALUE globalKeyboardModule;

static const char * keyNamesMisc[] =
{
	"Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", 
	"Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash", 
	"BackSlash", "Tilde", "Equal", "Dash", "Space", "Return", "Back", "Tab", "PageUp", 
	"PageDown", "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", 
	"Divide", "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", 
	"Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1", "F2", "F3", 
	"F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause",
	"Count"
};

/* Definition of key codes for keyboard events. 
 *
 * All SFML::Keyboard constants exists, I just haven't written them all so Rdoc can interpret them yet.
 */
static void DefineKeyboardEnums( void )
{
	rb_define_const( globalKeyboardModule, "A", INT2FIX( sf::Keyboard::A ) );
	rb_define_const( globalKeyboardModule, "B", INT2FIX( sf::Keyboard::B ) );
	rb_define_const( globalKeyboardModule, "C", INT2FIX( sf::Keyboard::C ) );
	rb_define_const( globalKeyboardModule, "D", INT2FIX( sf::Keyboard::D ) );
	rb_define_const( globalKeyboardModule, "E", INT2FIX( sf::Keyboard::E ) );
	rb_define_const( globalKeyboardModule, "F", INT2FIX( sf::Keyboard::F ) );
	rb_define_const( globalKeyboardModule, "G", INT2FIX( sf::Keyboard::G ) );
	rb_define_const( globalKeyboardModule, "H", INT2FIX( sf::Keyboard::H ) );
	rb_define_const( globalKeyboardModule, "I", INT2FIX( sf::Keyboard::I ) );
	rb_define_const( globalKeyboardModule, "J", INT2FIX( sf::Keyboard::J ) );
	rb_define_const( globalKeyboardModule, "K", INT2FIX( sf::Keyboard::K ) );
	rb_define_const( globalKeyboardModule, "L", INT2FIX( sf::Keyboard::L ) );
	rb_define_const( globalKeyboardModule, "M", INT2FIX( sf::Keyboard::M ) );
	rb_define_const( globalKeyboardModule, "N", INT2FIX( sf::Keyboard::N ) );
	rb_define_const( globalKeyboardModule, "O", INT2FIX( sf::Keyboard::O ) );
	rb_define_const( globalKeyboardModule, "P", INT2FIX( sf::Keyboard::P ) );
	rb_define_const( globalKeyboardModule, "Q", INT2FIX( sf::Keyboard::Q ) );
	rb_define_const( globalKeyboardModule, "R", INT2FIX( sf::Keyboard::R ) );
	rb_define_const( globalKeyboardModule, "S", INT2FIX( sf::Keyboard::S ) );
	rb_define_const( globalKeyboardModule, "T", INT2FIX( sf::Keyboard::T ) );
	rb_define_const( globalKeyboardModule, "U", INT2FIX( sf::Keyboard::U ) );
	rb_define_const( globalKeyboardModule, "W", INT2FIX( sf::Keyboard::W ) );
	rb_define_const( globalKeyboardModule, "V", INT2FIX( sf::Keyboard::V ) );
	rb_define_const( globalKeyboardModule, "X", INT2FIX( sf::Keyboard::X ) );
	rb_define_const( globalKeyboardModule, "Y", INT2FIX( sf::Keyboard::Y ) );
	rb_define_const( globalKeyboardModule, "Z", INT2FIX( sf::Keyboard::Z ) );
	
	rb_define_const( globalKeyboardModule, "Num0", INT2FIX( sf::Keyboard::Num0 ) );
	rb_define_const( globalKeyboardModule, "Num1", INT2FIX( sf::Keyboard::Num1 ) );
	rb_define_const( globalKeyboardModule, "Num2", INT2FIX( sf::Keyboard::Num2 ) );
	rb_define_const( globalKeyboardModule, "Num3", INT2FIX( sf::Keyboard::Num3 ) );
	rb_define_const( globalKeyboardModule, "Num4", INT2FIX( sf::Keyboard::Num4 ) );
	rb_define_const( globalKeyboardModule, "Num5", INT2FIX( sf::Keyboard::Num5 ) );
	rb_define_const( globalKeyboardModule, "Num6", INT2FIX( sf::Keyboard::Num6 ) );
	rb_define_const( globalKeyboardModule, "Num7", INT2FIX( sf::Keyboard::Num7 ) );
	rb_define_const( globalKeyboardModule, "Num8", INT2FIX( sf::Keyboard::Num8 ) );
	rb_define_const( globalKeyboardModule, "Num9", INT2FIX( sf::Keyboard::Num9 ) );
	
	for( int index = static_cast< int >( sf::Keyboard::Escape ); index <= sf::Keyboard::KeyCount; index++ )
	{
		rb_define_const( globalKeyboardModule, keyNamesMisc[ index - sf::Keyboard::Escape ], INT2FIX( index ) );
	}
}

/* call-seq:
 *   SFML::Keyboard.isKeyPressed( key )	-> true or false
 *
 * Check if a key is pressed. 
 */
static VALUE Keyboard_IsKeyPressed( VALUE self, VALUE aKey )
{
	if( sf::Keyboard::IsKeyPressed( static_cast< sf::Keyboard::Key >( FIX2INT( aKey ) ) ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

void Init_Keyboard( void )
{

/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Give access to the real-time state of the keyboard.
 *
 * SFML::Keyboard provides an interface to the state of the keyboard.
 *
 * It only contains static functions (a single keyboard is assumed), so it's not 
 * meant to be instanciated.
 * 
 * This class allows users to query the keyboard state at any time and directly, 
 * without having to deal with a window and its events. Compared to the KeyPressed 
 * and KeyReleased events, SFML::Keyboard can retrieve the state of a key at any time 
 * (you don't need to store and update a boolean on your side in order to know if a 
 * key is pressed or released), and you always get the real state of the keyboard, even
 * if keys are pressed or released when your window is out of focus and no event is triggered.
 *
 * Usage example:
 *
 *   if( SFML::Keyboard.is_key_pressed?( SFML::Keyboard::Left ) == true )
 *     # move left...
 *   elsif( SFML::Keyboard.is_key_pressed?( SFML::Keyboard::Right ) == true )
 *     # move right...
 *   elsif( SFML::Keyboard.is_key_pressed?( SFML::Keyboard::Escape ) == true )
 *     # quit...
 *   end
 */
	globalKeyboardModule = rb_define_module_under( sfml, "Keyboard" );
	
	DefineKeyboardEnums();
	
	// Instance methods
	rb_define_module_function( globalKeyboardModule, "isKeyPressed", Keyboard_IsKeyPressed, 1 );
	
	// Aliases
	rb_define_alias( CLASS_OF( globalKeyboardModule ), "isKeyPressed?", "isKeyPressed" );
	rb_define_alias( CLASS_OF( globalKeyboardModule ), "is_key_pressed", "isKeyPressed" );
	rb_define_alias( CLASS_OF( globalKeyboardModule ), "is_key_pressed?", "isKeyPressed" );
	rb_define_alias( CLASS_OF( globalKeyboardModule ), "key_pressed?", "isKeyPressed" );
}
