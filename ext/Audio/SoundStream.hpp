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

#ifndef AUDIO_SOUNDSTREAM_HPP
#define AUDIO_SOUNDSTREAM_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <Audio/SoundSource.hpp>

#include <SFML/Audio/SoundStream.hpp>

namespace rbSoundStream
{
#if defined( AUDIO_SOUNDSTREAM_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML );
#endif

#if defined( AUDIO_SOUNDSTREAM_CPP )
    // SoundStream#play
    // SoundStream#Play
    static VALUE Play( VALUE aSelf );

    // SoundStream#pause
    // SoundStream#Pause
    static VALUE Pause( VALUE aSelf );

    // SoundStream#stop
    // SoundStream#Stop
    static VALUE Stop( VALUE aSelf );

    // SoundStream#loop=(loop)
    // SoundStream#SetLoop(loop)
    static VALUE SetLoop( VALUE aSelf, VALUE aLoop );

    // SoundStream#playing_offset=(offset)
    // SoundStream#SetPlayingOffset(offset)
    // SoundStream#offset=(offset)
    static VALUE SetPlayingOffset( VALUE aSelf, VALUE anOffset );

    // SoundStream#loop
    // SoundStream#GetLoop
    static VALUE GetLoop( VALUE aSelf );

    // SoundStream#playing_offset
    // SoundStream#GetPlayingOffset
    // SoundStream#offset
    static VALUE GetPlayingOffset( VALUE aSelf );

    // SoundStream#sample_rate
    // SoundStream#GetSampleRate
    static VALUE GetSampleRate( VALUE aSelf );

    // SoundStream#channel_count
    // SoundStream#GetChannelCount
    static VALUE GetChannelCount( VALUE aSelf );

    // SoundStream#status
    // SoundStream#GetStatus
    static VALUE GetStatus( VALUE aSelf );

#endif

}

#endif // AUDIO_SOUNDSTREAM_HPP