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

#ifndef AUDIO_LISTENER_HPP
#define AUDIO_LISTENER_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"
#include "../System/Vector3.hpp"

#include <SFML/Audio/Listener.hpp>

namespace rbListener
{

#if defined( AUDIO_LISTENER_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif

#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML );
#endif

#if defined( AUDIO_LISTENER_CPP )
	// Listener.global_volume
    // Listener.get_global_volume
	// Listener.getGlobalVolume
    static VALUE GetGlobalVolume( VALUE aSelf );

	// Listener.global_volume=( volume )
    // Listener.set_global_volume( volume )
	// Listener.setGlobalVolume( volume )
    static VALUE SetGlobalVolume( VALUE aSelf, VALUE aVolume );

	// Listener.position
    // Listener.get_position
	// Listener.getPoistion
    static VALUE GetPosition( VALUE aSelf );

    // Listener.set_position(position)
    // Listener.set_position(x, y, z)
    // Listener.position=(position)
    // Listener.position=(x, y, z)
	// Listener.setPosition(position)
	// Listener.setPosition(x, y, z)
    static VALUE SetPosition( int argc, VALUE argv[], VALUE aSelf );

    // Listener.get_direction
    // Listener.direction
	// Listener.getDirection
    static VALUE GetDirection( VALUE aSelf );

    // Listener.set_direction(direction)
    // Listener.set_direction(x, y, z)
    // Listener.direction=(direction)
    // Listener.direction=(x, y, z)
	// Listener.setDirection(direction)
	// Listener.setDirection(x, y, z)
    static VALUE SetDirection( int argc, VALUE argv[], VALUE aSelf );

#endif

}

#endif // AUDIO_LISTENER_HPP
