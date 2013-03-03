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
    static VALUE Play( VALUE aSelf );

    // Sound#pause
    static VALUE Pause( VALUE aSelf );

    // Sound#stop
    static VALUE Stop( VALUE aSelf );

    // Sound#buffer=(buffer)
	// Sound#set_buffer(buffer)
    // Sound#setBuffer(buffer)
    static VALUE SetBuffer( VALUE aSelf, VALUE aBuffer );

    // Sound#loop=(loop)
	// Sound#set_loop(loop)
    // Sound#setLoop(loop)
    static VALUE SetLoop( VALUE aSelf, VALUE aLoop );

    // Sound#playing_offset=(offset)
	// Sound#set_playing_offset(offset)
    // Sound#setPlayingOffset(offset)
    // Sound#offset=(offset)
    static VALUE SetPlayingOffset( VALUE aSelf, VALUE anOffset );

    // Sound#buffer
	// Sound#get_buffer
    // Sound#getBuffer
    static VALUE GetBuffer( VALUE aSelf );

    // Sound#loop
	// Sound#get_loop
    // Sound#getLoop
    static VALUE GetLoop( VALUE aSelf );

    // Sound#playing_offset
	// Sound#get_playing_offset
    // Sound#getPlayingOffset
    // Sound#offset
    static VALUE GetPlayingOffset( VALUE aSelf );

    // Sound#status
	// Sound#get_status
    // Sound#GetStatus
    static VALUE GetStatus( VALUE aSelf );

    // Sound#inspect
	// Sound#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

};

#endif // AUDIO_SOUND_HPP
