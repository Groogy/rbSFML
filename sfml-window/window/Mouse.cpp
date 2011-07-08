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
 
#include "Mouse.hpp"
#include "Vector2.hpp"
#include "main.hpp"
#include <SFML/Window/Mouse.hpp>

VALUE globalMouseModule;

/* External classes */
extern VALUE globalVector2Class;
extern VALUE globalWindowClass;

/* Definition of button codes for mouse events. */
static void DefineMouseEnums( void )
{
	rb_define_const( globalMouseModule, "Left", INT2FIX( sf::Mouse::Left ) );
	rb_define_const( globalMouseModule, "Right", INT2FIX( sf::Mouse::Right ) );
	rb_define_const( globalMouseModule, "Middle", INT2FIX( sf::Mouse::Middle ) );
	rb_define_const( globalMouseModule, "XButton1", INT2FIX( sf::Mouse::XButton1 ) );
	rb_define_const( globalMouseModule, "XButton2", INT2FIX( sf::Mouse::XButton2 ) );
	rb_define_const( globalMouseModule, "ButtonCount", INT2FIX( sf::Mouse::ButtonCount ) );
}

/* call-seq:
 *   SFML::Mouse.isMousePressed( button )	-> true or false
 *
 * Check if a mouse button is pressed. 
 */
static VALUE Mouse_IsButtonPressed( VALUE self, VALUE aButton )
{
	if( sf::Mouse::IsButtonPressed( static_cast< sf::Mouse::Button >( FIX2INT( aButton ) ) ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   SFML::Mouse.getPosition()			-> vector2
 *   SFML::Mouse.getPosition( window ) 	-> vector2
 *
 * Get the current position of the mouse.
 *
 * This function returns the current position of the mouse cursor. 
 * If a window is passed as argument then the coordinates will be
 * relative to that window.
 */
static VALUE Mouse_GetPosition( int argc, VALUE *args, VALUE self )
{
	sf::Vector2i position;
	sf::Window *window = NULL;
	switch( argc )
	{
	case 0:
		position = sf::Mouse::GetPosition();
		break;
	case 1:
		VALIDATE_CLASS( args[ 0 ], globalWindowClass, "window" );
		Data_Get_Struct( args[ 0 ], sf::Window, window );
		position = sf::Mouse::GetPosition( *window );
		break;
	default:
		rb_raise( rb_eArgError, "Expected 0 or 1 arguments but was given %d", argc );
		break;
	}
	return rb_funcall( globalVector2Class, rb_intern( "new" ), 2, INT2FIX( position.x ), INT2FIX( position.y ) );
}

/* call-seq:
 *   SFML::Mouse.setPosition( position )
 *   SFML::Mouse.setPosition( position, window )
 *
 * Set the current position of the mouse.
 *
 * This function sets the current position of the mouse cursor. 
 * If a window is passed as argument then the coordinates will be
 * relative to that window.
 */
static VALUE Mouse_SetPosition( int argc, VALUE *args, VALUE self )
{
	sf::Vector2i position;
	sf::Window *window = NULL;
	switch( argc )
	{
	case 1:
		VALIDATE_CLASS( args[ 0 ], globalVector2Class, "position" );
		position.x = NUM2INT( Vector2_GetX( args[ 0 ] ) );
		position.y = NUM2INT( Vector2_GetY( args[ 0 ] ) );
		sf::Mouse::SetPosition( position );
		break;
	case 2:
		VALIDATE_CLASS( args[ 0 ], globalVector2Class, "position" );
		position.x = NUM2INT( Vector2_GetX( args[ 0 ] ) );
		position.y = NUM2INT( Vector2_GetY( args[ 0 ] ) );
		VALIDATE_CLASS( args[ 0 ], globalWindowClass, "window" );
		Data_Get_Struct( args[ 0 ], sf::Window, window );
		sf::Mouse::SetPosition( position, *window );
	default:
		rb_raise( rb_eArgError, "Expected 1 or 2 arguments but was given %d", argc );
		break;
	}
	return Qnil;
}

/* call-seq:
 *   SFML::Mouse.position=( position )
 *
 * Set the current position of the mouse.
 */
static VALUE Mouse_SetPosition2( VALUE self, VALUE aPosition )
{
	sf::Vector2i position;
	VALIDATE_CLASS( aPosition, globalVector2Class, "position" );
	position.x = NUM2INT( Vector2_GetX( aPosition ) );
	position.y = NUM2INT( Vector2_GetY( aPosition ) );
	sf::Mouse::SetPosition( position );
	return Qnil;
}

void Init_Mouse( void )
{

/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Give access to the real-time state of the mouse.
 *
 * SFML::Mouse provides an interface to the state of the mouse.
 *
 * It only contains static functions (a single mouse is assumed), 
 * so it's not meant to be instanciated.
 *
 * This class allows users to query the mouse state at any time and 
 * directly, without having to deal with a window and its events. Compared 
 * to the MouseMoved, MouseButtonPressed and MouseButtonReleased events, 
 * SFML::Mouse can retrieve the state of the cursor and the buttons at any time 
 * (you don't need to store and update a boolean on your side in order to know 
 * if a button is pressed or released), and you always get the real state of the 
 * mouse, even if it is moved, pressed or released when your window is out of 
 * focus and no event is triggered.
 *
 * Note that the SFML::Mouse::getPosition function has a special behaviour: it 
 * returns the cursor position relative to the window which has the mouse focus 
 * (ie. the window on which the cursor is).
 * 
 * Usage example:
 *
 *   if( SFML::Mouse.is_button_pressed?( SFML::Mouse::Left ) == true)
 *     # left click...
 *   elsif( SFML::Mouse.is_button_pressed?( SFML::Mouse::Right ) == true )
 *       right click...
 *   end
 *   
 *   position = SFML::Mouse.position
 */
	globalMouseModule = rb_define_module_under( sfml, "Mouse" );
	
	DefineMouseEnums();
	
	// Instance methods
	rb_define_module_function( globalMouseModule, "isButtonPressed", Mouse_IsButtonPressed, 1 );
	rb_define_module_function( globalMouseModule, "getPosition", Mouse_GetPosition, -1 );
	rb_define_module_function( globalMouseModule, "setPosition", Mouse_SetPosition, -1 );
	rb_define_module_function( globalMouseModule, "position=", Mouse_SetPosition2, 1 );
	
	// Aliases
	rb_define_alias( CLASS_OF( globalMouseModule ), "isButtonPressed?", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalMouseModule ), "is_button_pressed", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalMouseModule ), "is_button_pressed?", "isButtonPressed" );
	rb_define_alias( CLASS_OF( globalMouseModule ), "button_pressed?", "isButtonPressed" );
	
	rb_define_alias( CLASS_OF( globalMouseModule ), "get_position", "getPosition" );
	rb_define_alias( CLASS_OF( globalMouseModule ), "position", "getPosition" );
	
	rb_define_alias( CLASS_OF( globalMouseModule ), "set_position", "setPosition" );
}
