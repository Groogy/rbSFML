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

#define AUDIO_SOUNDSTREAM_CPP
#include "SoundStream.hpp"
#include "Time.hpp"

void rbSoundStream::Init( VALUE SFML )
{
    rbSoundStream::Class = rb_define_class_under( SFML, "SoundStream", rbSoundSource::Class );

    // Class methods
    rb_define_alloc_func(rbSoundStream::Class, rbMacros::AbstractAllocate );

    // Instance methods
    rb_define_method( rbSoundStream::Class, "play",            rbSoundStream::Play,             0 );
    rb_define_method( rbSoundStream::Class, "pause",           rbSoundStream::Pause,            0 );
    rb_define_method( rbSoundStream::Class, "stop",            rbSoundStream::Stop,             0 );
    rb_define_method( rbSoundStream::Class, "loop=",           rbSoundStream::SetLoop,          1 );
    rb_define_method( rbSoundStream::Class, "playing_offset=", rbSoundStream::SetPlayingOffset, 1 );
    rb_define_method( rbSoundStream::Class, "loop",            rbSoundStream::GetLoop,          0 );
    rb_define_method( rbSoundStream::Class, "playing_offset",  rbSoundStream::GetPlayingOffset, 0 );
    rb_define_method( rbSoundStream::Class, "sample_rate",     rbSoundStream::GetSampleRate,    0 );
    rb_define_method( rbSoundStream::Class, "channel_count",   rbSoundStream::GetChannelCount, 0 );
    rb_define_method( rbSoundStream::Class, "status",          rbSoundStream::GetStatus,        0 );

    // Instance aliasses
    rb_define_alias( rbSoundStream::Class, "Play",             "play"            );
    rb_define_alias( rbSoundStream::Class, "Pause",            "pause"           );
    rb_define_alias( rbSoundStream::Class, "Stop",             "stop"            );
    rb_define_alias( rbSoundStream::Class, "SetLoop",          "loop="           );
    rb_define_alias( rbSoundStream::Class, "SetPlayingOffset", "playing_offset=" );
    rb_define_alias( rbSoundStream::Class, "offset=",          "playing_offset=" );
    rb_define_alias( rbSoundStream::Class, "GetLoop",          "loop"            );
    rb_define_alias( rbSoundStream::Class, "GetPlayingOffset", "playing_offset"  );
    rb_define_alias( rbSoundStream::Class, "offset",           "playing_offset"  );
    rb_define_alias( rbSoundStream::Class, "GetSampleRate",    "sample_rate"     );
    rb_define_alias( rbSoundStream::Class, "GetChannelCount", "channel_count"  );
    rb_define_alias( rbSoundStream::Class, "GetStatus",        "status"          );
}

// SoundStream#play
// SoundStream#Play
VALUE rbSoundStream::Play( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->Play();
    return Qnil;
}

// SoundStream#pause
// SoundStream#Pause
VALUE rbSoundStream::Pause( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->Pause();
    return Qnil;
}

// SoundStream#stop
// SoundStream#Stop
VALUE rbSoundStream::Stop( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->Stop();
    return Qnil;
}

// SoundStream#loop=(loop)
// SoundStream#SetLoop(loop)
VALUE rbSoundStream::SetLoop( VALUE aSelf, VALUE aLoop )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->SetLoop( RTEST( aLoop ) );
    return Qnil;
}

// SoundStream#playing_offset=(offset)
// SoundStream#SetPlayingOffset(offset)
// SoundStream#offset=(offset)
VALUE rbSoundStream::SetPlayingOffset( VALUE aSelf, VALUE anOffset )
{
	sf::Time* time = rbMacros::ToSFML< sf::Time >( anOffset, rbTime::Class );
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->SetPlayingOffset( *time );
    return Qnil;
}

// SoundStream#loop
// SoundStream#GetLoop
VALUE rbSoundStream::GetLoop( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->GetLoop() );
}

// SoundStream#playing_offset
// SoundStream#GetPlayingOffset
// SoundStream#offset
VALUE rbSoundStream::GetPlayingOffset( VALUE aSelf )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
	*time = rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->GetPlayingOffset();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// SoundStream#sample_rate
// SoundStream#GetSampleRate
VALUE rbSoundStream::GetSampleRate( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->GetSampleRate() );
}

// SoundStream#channel_count
// SoundStream#GetChannelCount
VALUE rbSoundStream::GetChannelCount( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->GetChannelCount() );
}

// SoundStream#status
// SoundStream#GetStatus
VALUE rbSoundStream::GetStatus( VALUE aSelf )
{
    return INT2FIX( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->GetStatus() );
}
