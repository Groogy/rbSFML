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

#ifndef AUDIO_SOUND_HPP
#define AUDIO_SOUND_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <Audio/SoundSource.hpp>
#include <Audio/SoundBuffer.hpp>
#include <System/Time.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace rbSound
{

#if defined( AUDIO_SOUND_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML );
#endif

#if defined( AUDIO_SOUND_CPP )
    // Sound#initialize
    // Sound#initialize(sound_buffer)
    static VALUE Initialize( int argc, VALUE argv[], VALUE aSelf );

    // Sound#initialize_copy(other)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSound );

    // Sound#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Sound#play
    // Sound#Play
    static VALUE Play( VALUE aSelf );

    // Sound#pause
    // Sound#Pause
    static VALUE Pause( VALUE aSelf );

    // Sound#stop
    // Sound#Stop
    static VALUE Stop( VALUE aSelf );

    // Sound#buffer=(buffer)
    // Sound#SetBuffer(buffer)
    static VALUE SetBuffer( VALUE aSelf, VALUE aBuffer );

    // Sound#loop=(loop)
    // Sound#SetLoop(loop)
    static VALUE SetLoop( VALUE aSelf, VALUE aLoop );

    // Sound#playing_offset=(offset)
    // Sound#SetPlayingOffset(offset)
    // Sound#offset=(offset)
    static VALUE SetPlayingOffset( VALUE aSelf, VALUE anOffset );

    // Sound#buffer
    // Sound#GetBuffer
    static VALUE GetBuffer( VALUE aSelf );

    // Sound#loop
    // Sound#GetLoop
    static VALUE GetLoop( VALUE aSelf );

    // Sound#playing_offset
    // Sound#GetPlayingOffset
    // Sound#offset
    static VALUE GetPlayingOffset( VALUE aSelf );

    // Sound#status
    // Sound#GetStatus
    static VALUE GetStatus( VALUE aSelf );

    // Sound#inspect
    static VALUE Inspect( VALUE aSelf );

    // Sound#memory_usage
    static VALUE GetMemoryUsage( VALUE aSelf );
#endif

};

#endif // AUDIO_SOUND_HPP
