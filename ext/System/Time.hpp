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

#ifndef SYSTEM_TIME_HPP
#define SYSTEM_TIME_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "SFML.hpp"

#include <SFML/System/Time.hpp>

namespace rbTime
{    
#if defined( SYSTEM_TIME_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif
    
#if defined( RBSFML_SYSTEM )
    void Init( VALUE SFML );
#endif

#if defined( SYSTEM_TIME_CPP )	
    // Time#initialize_copy( other )
    static VALUE InitializeCopy( VALUE aSelf, VALUE aTime );
	
	// Time#as_seconds
	// Time#asSeconds
	static VALUE AsSeconds( VALUE aSelf );
	
	// Time#as_milliseconds
	// Time#asMilliseconds
	static VALUE AsMilliseconds( VALUE aSelf );
	
	// Time#as_microseconds
	// Time#asMicroseconds
	static VALUE AsMicroseconds( VALUE aSelf );
    
    // Time#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // Time#<=>( other )
    static VALUE Compare( VALUE aSelf, VALUE anOther );
	
	// Time#-@
	static VALUE Negate( VALUE aSelf );
	
	// Time#+( other )
	static VALUE Addition( VALUE aSelf, VALUE anOther );
	
	// Time#-( other )
	static VALUE Subtract( VALUE aSelf, VALUE anOther );
	
	// Time#*( other )
	static VALUE Multiply( VALUE aSelf, VALUE anOther );
	
	// Time#/( other )
	static VALUE Divide( VALUE aSElf, VALUE anOther );
    
    // Time#inspect
    // Time#to_s
    static VALUE Inspect( VALUE aSelf );
	
#endif

};

#endif // SYSTEM_TIME_HPP
