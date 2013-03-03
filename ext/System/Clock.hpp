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

#ifndef SYSTEM_CLOCK_HPP
#define SYSTEM_CLOCK_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/System/Clock.hpp>

namespace rbClock
{
#if defined( SYSTEM_CLOCK_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_SYSTEM )
    void Init( VALUE SFML );
#endif

#if defined( SYSTEM_CLOCK_CPP )
    // Clock#initialize_copy(other)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aClock );

    // Clock#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Clock#elapsed_time
	// Clock#elapsedTime
    // Clock#getElapsedTime
	// Clock#get_elapsed_time
    // Clock#time
    static VALUE GetElapsedTime( VALUE aSelf );

    // Clock#restart
    static VALUE Restart( VALUE aSelf );

    // Clock#inspect
    // Clock#to_s
    static VALUE Inspect( VALUE aSelf );
    
#endif

};

#endif // SYSTEM_CLOCK_HPP
