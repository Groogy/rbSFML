/* rbSFML
 * Copyright (c) 2012 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#include <System.hpp>

#if !defined( RBSFML_SFML )
#include <sstream>
std::stringstream globalErrorStream;
#endif

VALUE rbSFML_Seconds( VALUE aSelf, VALUE someTime )
{
	VALUE time = rbMacros::RubyAllocate( rbTime::Class );
	*rbMacros::ToSFML< sf::Time >( time, rbTime::Class ) = sf::seconds( NUM2DBL( someTime ) );
	return time;
}

VALUE rbSFML_Milliseconds( VALUE aSelf, VALUE someTime )
{
	VALUE time = rbMacros::RubyAllocate( rbTime::Class );
	*rbMacros::ToSFML< sf::Time >( time, rbTime::Class ) = sf::milliseconds( NUM2INT( someTime ) );
	return time;
}

VALUE rbSFML_Microseconds( VALUE aSelf, VALUE someTime )
{
	VALUE time = rbMacros::RubyAllocate( rbTime::Class );
	*rbMacros::ToSFML< sf::Time >( time, rbTime::Class ) = sf::milliseconds( NUM2LONG( someTime ) );
	return time;
}

void DefineTimeConstructionMethods( VALUE SFML )
{
	ext_define_module_function( SFML, "seconds",      rbSFML_Seconds, 1      );
	ext_define_module_function( SFML, "milliseconds", rbSFML_Milliseconds, 1 );
	ext_define_module_function( SFML, "microseconds", rbSFML_Microseconds, 1 );
}

extern "C"
void Init_system()
{
    VALUE SFML = rbSFML::Module();
	rb_define_const( SFML, "SYSTEM_LOADED", Qtrue );
	
	DefineTimeConstructionMethods( SFML );

    rbSFML::Init( SFML );
    rbNonCopyable::Init( SFML );
    rbTime::Init( SFML );
    rbClock::Init( SFML );
    rbVector2::Init( SFML );
    rbVector3::Init( SFML );
}
