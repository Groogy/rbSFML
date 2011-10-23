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
#include "global.hpp"
#include "Clock.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Error.hpp"
#include "NonCopyable.hpp"
#include "InputStream.hpp"
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>

extern VALUE globalErrorClass;

bool localRaiseExceptionFlag = true;
std::stringstream localErrorStream;

VALUE RaiseError( VALUE self )
{
	if( localRaiseExceptionFlag == true )
	{
		rb_raise( globalErrorClass, localErrorStream.str().c_str() );
	}
	return Qnil;
}
	
static VALUE GetRaiseExceptions( VALUE self )
{
	return localRaiseExceptionFlag == true ? Qtrue : Qfalse;
}

static VALUE SetRaiseExceptions( VALUE self, VALUE aFlag )
{
	localRaiseExceptionFlag = ( aFlag == Qfalse || aFlag == Qnil ) ? false : true;
	if( localRaiseExceptionFlag == true )
	{
		sf::Err().rdbuf( localErrorStream.rdbuf() );
	}
	else
	{
		sf::Err().rdbuf( std::cerr.rdbuf() );
	}
	return aFlag;
}

void Init_ErrorSystem( void )
{
	sf::Err().rdbuf( localErrorStream.rdbuf() );
	rb_define_module_function( globalSFMLNamespace, "raise_exceptions", GetRaiseExceptions, 0 );
	rb_define_module_function( globalSFMLNamespace, "raise_exceptions=", SetRaiseExceptions, 1 );
	rb_define_module_function( globalSFMLNamespace, "raise_error", RaiseError, 0 );
}

void Init_system( void )
{
	/* SFML namespace which contains the classes of this module. */
	globalSFMLNamespace = rb_define_module( "SFML" );
	rb_define_const(globalSFMLNamespace, "SystemLoaded", Qtrue);
	rb_define_const(globalSFMLNamespace, "Version", rb_str_new2(LIB_VERSION));
	rb_define_const(globalSFMLNamespace, "BindingVersion", rb_str_new2(BINDING_VERSION));
	Init_ErrorSystem();
	Init_Error();
	Init_Clock();
	Init_Vector2();
	Init_Vector3();
	Init_NonCopyable();
}
