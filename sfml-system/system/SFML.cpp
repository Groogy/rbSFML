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
 
#include "SFML.hpp"
#include <iostream>

static VALUE mSFML;
static VALUE cError;
static std::stringstream ErrorStream;
static bool RaiseExceptionFlag;

// SFML.raise
static VALUE SFML_Raise( VALUE self )
{
	if( RaiseExceptionFlag )
	{
		std::string message = ErrorStream.str();
		if ( message.size() == 0 ) return Qnil;
		ErrorStream.str( "" );
		rb_raise( cError, message.c_str() );
	}
	return Qnil;
}

// SFML.raise_exceptions
static VALUE SFML_GetRaiseExceptions( VALUE self )
{
	return RaiseExceptionFlag ? Qtrue : Qfalse;
}

// SFML.raise_exceptions=
static VALUE SFML_SetRaiseExceptions( VALUE self, VALUE aFlag )
{
	RaiseExceptionFlag = RTEST( aFlag );
	if( RaiseExceptionFlag )
	{
		sf::Err().rdbuf( ErrorStream.rdbuf() );
	}
	else
	{
		sf::Err().rdbuf( std::cerr.rdbuf() );
	}
}

void Init_SFML( void )
{
	mSFML = rb_define_module( "SFML" );
	cError = rb_define_class_under( mSFML, "Error", rb_eRuntimeError );
  
	rb_define_const( mSFML, "VERSION", rb_str_new2( LIB_VERSION ) );
	rb_define_const( mSFML, "BINDING_VERSION", rb_str_new2( BINDING_VERSION ) );
	
	RaiseExceptionFlag = true;
	sf::Err().rdbuf( ErrorStream.rdbuf() );
	rb_define_module_function( mSFML, "raise",             SFML_Raise,              0 );
	rb_define_module_function( mSFML, "raise_exceptions",  SFML_GetRaiseExceptions, 0 );
	rb_define_module_function( mSFML, "raise_exceptions=", SFML_SetRaiseExceptions, 1 );
}
