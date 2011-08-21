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
 
#include "Joystick.hpp"
#include "main.hpp"
#include <SFML/Window/Joystick.hpp>

VALUE globalJoystickModule;

/* Definition of joystick enums. */
static void DefineJoystickEnums( void )
{
	rb_define_const( globalJoystickModule, "X", INT2FIX( sf::Joystick::X ) );
	rb_define_const( globalJoystickModule, "Y", INT2FIX( sf::Joystick::Y ) );
	rb_define_const( globalJoystickModule, "Z", INT2FIX( sf::Joystick::Z ) );
	rb_define_const( globalJoystickModule, "R", INT2FIX( sf::Joystick::R ) );
	rb_define_const( globalJoystickModule, "U", INT2FIX( sf::Joystick::U ) );
	rb_define_const( globalJoystickModule, "V", INT2FIX( sf::Joystick::V ) );
	rb_define_const( globalJoystickModule, "PovX", INT2FIX( sf::Joystick::PovX ) );
	rb_define_const( globalJoystickModule, "PovY", INT2FIX( sf::Joystick::PovY ) );
	rb_define_const( globalJoystickModule, "Count", INT2FIX( sf::Joystick::Count ) );
	rb_define_const( globalJoystickModule, "AxisCount", INT2FIX( sf::Joystick::AxisCount ) );
	rb_define_const( globalJoystickModule, "ButtonCount", INT2FIX( sf::Joystick::ButtonCount ) );
}

/* call-seq:
 *   Joystick.isConnected( joystickId )	-> true or false
 *
 * Check if a joystick is connected.
 */
static VALUE Joystick_IsConnected( VALUE self, VALUE anID )
{
	if( sf::Joystick::IsConnected( FIX2UINT( anID ) ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   Joystick.getButtonCount( joystickId )	-> fixnum
 *
 * Return the number of buttons supported by a joystick.
 *
 * If the joystick is not connected, this function returns 0.
 */
static VALUE Joystick_GetButtonCount( VALUE self, VALUE anID )
{
	return FIX2UINT( sf::Joystick::GetButtonCount( FIX2UINT( anID ) ) );
}

/* call-seq:
 *   Joystick.hasAxis( joystickId, axis )	-> true or false
 *
 * Check if a joystick supports a given axis.
 *
 * If the joystick is not connected, this function returns false.
 */
static VALUE Joystick_HasAxis( VALUE self, VALUE anID, VALUE anAxis )
{
	if( sf::Joystick::HasAxis( FIX2UINT( anID ), static_cast< sf::Joystick::Axis >( FIX2INT( anAxis ) ) ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   Joystick.isButtonPressed( joystickId, button )	-> true or false
 *
 * Check if a joystick button is pressed. 
 *
 * If the joystick is not connected, this function returns false.
 */
static VALUE Joystick_IsButtonPressed( VALUE self, VALUE anID, VALUE aButton )
{
	if( sf::Joystick::IsButtonPressed( FIX2UINT( anID ), FIX2UINT( aButton ) ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   Joystick.getAxisPosition( joystickId, axis )	-> float
 *
 * Get the current position of a joystick axis. 
 *
 * If the joystick is not connected, this function returns 0.
 */
static VALUE Joystick_GetAxisPosition( VALUE self, VALUE anID, VALUE anAxis )
{
	return rb_float_new( sf::Joystick::GetAxisPosition( FIX2UINT( anID ), static_cast< sf::Joystick::Axis >( FIX2INT( anAxis ) ) ) );
}

/* call-seq:
 *   Joystick.update()
 *
 * Update the states of all joysticks.
 *
 * This function is used internally by SFML, so you normally don't have to call it explicitely. 
 * However, you may need to call it if you have no window yet (or no window at all): in this 
 * case the joysticks states are not updated automatically.
 */
static VALUE Joystick_Update( VALUE self )
{
	sf::Joystick::Update();
	return Qnil;
}

void Init_Joystick( void )
{

/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Give access to the real-time state of the joysticks.
*
 * SFML::Joystick provides an interface to the state of the joysticks.
 *
 * It only contains static functions, so it's not meant to be instanciated. 
 * Instead, each joystick is identified by an index that is passed to the functions of this class.
 *
 * This class allows users to query the state of joysticks at any time and directly, without 
 * having to deal with a window and its events. Compared to the SFML::JoystickMoved, 
 * SFML::JoystickButtonPressed and SFML::JoystickButtonReleased events, SFML::Joystick can 
 * retrieve the state of axes and buttons of joysticks at any time (you don't need to store and 
 * update a boolean on your side in order to know if a button is pressed or released), and you 
 * always get the real state of joysticks, even if they are moved, pressed or released when your 
 * window is out of focus and no event is triggered.
 *
 * SFML supports:
 *
 *	8 joysticks (SFML::Joystick::Count)
 *	32 buttons per joystick (SFML::Joystick::ButtonCount)
 *	8 axes per joystick (SFML::Joystick::AxisCount)
 *
 * Unlike the keyboard or mouse, the state of joysticks is sometimes not directly available 
 * (depending on the OS), therefore an Update() function must be called in order to update the 
 * current state of joysticks. When you have a window with event handling, this is done 
 * automatically, you don't need to call anything. But if you have no window, or if you want to 
 * check joysticks state before creating one, you must call SFML::Joystick::Update explicitely.
 *
 * Usage example:
 *
 *   # Is joystick #0 connected?
 *   connected = SFML::Joystick.is_connected?( 0 )
 *   
 *   # How many buttons does joystick #0 support?
 *   buttons = SFML::Joystick.get_button_count( 0 )
 *
 *   # Does joystick #0 define a X axis?
 *   hasX = SFML::Joystick.has_axis( 0, SFML::Joystick::X )
 *   
 *   # Is button #2 pressed on joystick #0?
 *   pressed = SFML::Joystick.is_button_pressed?( 0, 2 )
 *   
 *   # What's the current position of the Y axis on joystick #0?
 *   position = SFML::Joystick.get_axis_position( 0, SFML::Joystick::Y );
 */
	globalJoystickModule = rb_define_module_under( sfml, "Joystick" );
	
	DefineJoystickEnums();
	
	// Instance methods
	rb_define_module_function( globalJoystickModule, "isConnected", Joystick_IsConnected, 1 );
	rb_define_module_function( globalJoystickModule, "getButtonCount", Joystick_GetButtonCount, 1 );
	rb_define_module_function( globalJoystickModule, "hasAxis", Joystick_HasAxis, 2 );
	rb_define_module_function( globalJoystickModule, "isButtonPressed", Joystick_IsButtonPressed, 2 );
	rb_define_module_function( globalJoystickModule, "getAxisPosition", Joystick_GetAxisPosition, 2 );
	rb_define_module_function( globalJoystickModule, "update", Joystick_Update, 0 );
	
	// Aliases
	rb_define_alias( CLASS_OF( globalJoystickModule ), "isConnected?", "isConnected" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "is_connected", "isConnected" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "is_connected?", "isConnected" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "connected?", "isConnected" );
	
	rb_define_alias( CLASS_OF( globalJoystickModule ), "buttonCount", "getButtonCount" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "get_button_count", "getButtonCount" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "button_count", "getButtonCount" );
	
	rb_define_alias( CLASS_OF( globalJoystickModule ), "hasAxis?", "hasAxis" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "has_axis", "hasAxis" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "has_axis?", "hasAxis" );
	
	rb_define_alias( CLASS_OF( globalJoystickModule ), "isButtonPressed?", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "buttonPressed?", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "buttonPressed", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "is_button_pressed", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "is_button_pressed?", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "button_pressed?", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "button_pressed", "isButtonPressed" );
	
	rb_define_alias( CLASS_OF( globalJoystickModule ), "axisPosition", "getAxisPosition" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "get_axis_position", "getAxisPosition" );
	rb_define_alias( CLASS_OF( globalJoystickModule ), "axis_position", "getAxisPosition" ); 
}
