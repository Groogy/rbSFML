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

#include "main.hpp"
#include "Vector2.hpp"
#include "NonCopyable.hpp"
#include "Context.hpp"
#include "ContextSettings.hpp"
#include "Event.hpp"
#include "VideoMode.hpp"
#include "Window.hpp"
#include "Joystick.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

#include <SFML/Window.hpp>

#include <iostream>

VALUE globalStyleNamespace;
extern VALUE globalVector2Class;
extern VALUE globalNonCopyableModule;

/* Enumeration of the window styles. */
static void CreateStyleEnum( void )
{
	globalStyleNamespace = rb_define_module_under( globalSFMLNamespace, "Style" );
	rb_define_const( globalStyleNamespace, "None", INT2FIX( sf::Style::None ) );
	rb_define_const( globalStyleNamespace, "Titlebar", INT2FIX( sf::Style::Titlebar ) );
	rb_define_const( globalStyleNamespace, "Resize", INT2FIX( sf::Style::Resize ) );
	rb_define_const( globalStyleNamespace, "Close", INT2FIX( sf::Style::Close ) );
	rb_define_const( globalStyleNamespace, "Fullscreen", INT2FIX( sf::Style::Fullscreen ) );
	rb_define_const( globalStyleNamespace, "Default", INT2FIX( sf::Style::Default ) );
}

static bool CheckDependencies( void )
{
	if( rb_cvar_defined( globalSFMLNamespace, rb_intern( "SystemLoaded" ) ) == Qtrue )
	{
		return true;
	}

	return false;
}

void Init_window( void )
{
	/* SFML namespace which contains the classes of this module. */
	globalSFMLNamespace = rb_define_module( "SFML" );
	if( CheckDependencies() == false )
	{
		rb_raise( rb_eRuntimeError, "This module depends on sfml-system" );
	}
	
	globalVector2Class = rb_define_class_under(globalSFMLNamespace, "Vector2", rb_cObject );
	globalNonCopyableModule = rb_define_module_under(globalSFMLNamespace, "NonCopyable");
	
	rb_define_const( globalSFMLNamespace, "WindowLoaded", Qtrue );
	
	CreateStyleEnum();
	
	Init_Joystick();
	Init_Keyboard();
	Init_Mouse();
	Init_Context();
	Init_ContextSettings();
	Init_Event();
	Init_VideoMode();
	Init_Window();
}

