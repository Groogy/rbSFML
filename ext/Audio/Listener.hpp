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
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <System/Vector3.hpp>

#include <SFML/Audio/Listener.hpp>

namespace rbListener
{

#if defined( AUDIO_LISTENER_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_AUDIO )
    void Init(VALUE SFML);
#endif

#if defined( AUDIO_LISTENER_CPP )
    // Listener::global_volume
    // Listener::global_volume(volume)
    // Listener::global_volume=(volume)
    static VALUE GlobalVolume(int argc, VALUE argv[], VALUE self);

    // Listener::GetGlobalVolume
    static VALUE GetGlobalVolume(VALUE self);

    // Listener::SetGlobalVolume(volume)
    static VALUE SetGlobalVolume(VALUE self, VALUE volume);

    // Listener::position
    // Listener::position(position)
    // Listener::position=(position)
    // Listener::position(x, y, z)
    static VALUE Position(int argc, VALUE argv[], VALUE self);

    // Listener::GetPosition
    static VALUE GetPosition(VALUE self);

    // Listener::SetPosition(position)
    // Listener::SetPosition(x, y, z)
    static VALUE SetPosition(int argc, VALUE argv[], VALUE self);

    // Listener::direction
    // Listener::direction(direction)
    // Listener::direction=(direction)
    // Listener::direction(x, y, z)
    static VALUE Direction(int argc, VALUE argv[], VALUE self);

    // Listener::GetDirection
    static VALUE GetDirection(VALUE self);

    // Listener::SetDirection(direction)
    // Listener::SetDirection(x, y, z)
    static VALUE SetDirection(int argc, VALUE argv[], VALUE self);
#endif

}

#endif // AUDIO_LISTENER_HPP
