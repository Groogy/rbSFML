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
#include <System/Time.hpp>

void rbSoundStream::Init( VALUE SFML )
{
    rbSoundStream::Class = rb_define_class_under( SFML, "SoundStream", rbSoundSource::Class );

    // Class methods
    rb_define_alloc_func(rbSoundStream::Class, rbMacros::AbstractAllocate );

    // Instance methods
    ext_define_method( rbSoundStream::Class, "play",            rbSoundStream::Play,             0 );
    ext_define_method( rbSoundStream::Class, "pause",           rbSoundStream::Pause,            0 );
    ext_define_method( rbSoundStream::Class, "stop",            rbSoundStream::Stop,             0 );
    ext_define_method( rbSoundStream::Class, "loop=",           rbSoundStream::SetLoop,          1 );
    ext_define_method( rbSoundStream::Class, "playing_offset=", rbSoundStream::SetPlayingOffset, 1 );
    ext_define_method( rbSoundStream::Class, "loop",            rbSoundStream::GetLoop,          0 );
    ext_define_method( rbSoundStream::Class, "playing_offset",  rbSoundStream::GetPlayingOffset, 0 );
    ext_define_method( rbSoundStream::Class, "sample_rate",     rbSoundStream::GetSampleRate,    0 );
    ext_define_method( rbSoundStream::Class, "channel_count",   rbSoundStream::GetChannelCount,  0 );
    ext_define_method( rbSoundStream::Class, "status",          rbSoundStream::GetStatus,        0 );

    // Instance aliasses
    rb_define_alias( rbSoundStream::Class, "setLoop",            "loop="           );
	rb_define_alias( rbSoundStream::Class, "set_loop",           "loop="           );
    rb_define_alias( rbSoundStream::Class, "setPlayingOffset",   "playing_offset=" );
	rb_define_alias( rbSoundStream::Class, "set_playing_offset", "playing_offset=" );
    rb_define_alias( rbSoundStream::Class, "offset=",            "playing_offset=" );
    rb_define_alias( rbSoundStream::Class, "getLoop",            "loop"            );
	rb_define_alias( rbSoundStream::Class, "get_loop",           "loop"            );
    rb_define_alias( rbSoundStream::Class, "getPlayingOffset",   "playing_offset"  );
	rb_define_alias( rbSoundStream::Class, "get_playing_offset", "playing_offset"  );
    rb_define_alias( rbSoundStream::Class, "offset",             "playing_offset"  );
    rb_define_alias( rbSoundStream::Class, "getSampleRate",      "sample_rate"     );
	rb_define_alias( rbSoundStream::Class, "get_sample_rate",    "sample_rate"     );
    rb_define_alias( rbSoundStream::Class, "getChannelCount",    "channel_count"   );
	rb_define_alias( rbSoundStream::Class, "get_channel_count",  "channel_count"   );
    rb_define_alias( rbSoundStream::Class, "getStatus",          "status"          );
	rb_define_alias( rbSoundStream::Class, "get_status",         "status"          );
}

// SoundStream#play
VALUE rbSoundStream::Play( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->play();
    return Qnil;
}

// SoundStream#pause
VALUE rbSoundStream::Pause( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->pause();
    return Qnil;
}

// SoundStream#stop
VALUE rbSoundStream::Stop( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->stop();
    return Qnil;
}

// SoundStream#loop=(loop)
// SoundStream#set_loop(loop)
// SoundStream#setLoop(loop)
VALUE rbSoundStream::SetLoop( VALUE aSelf, VALUE aLoop )
{
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->setLoop( RTEST( aLoop ) );
    return Qnil;
}

// SoundStream#playing_offset=(offset)
// SoundStream#set_playing_offset(offset)
// SoundStream#setPlayingOffset(offset)
// SoundStream#offset=(offset)
VALUE rbSoundStream::SetPlayingOffset( VALUE aSelf, VALUE anOffset )
{
	sf::Time* time = rbMacros::ToSFML< sf::Time >( anOffset, rbTime::Class );
    rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->setPlayingOffset( *time );
    return Qnil;
}

// SoundStream#loop
// SoundStream#get_loop
// SoundStream#getLoop
VALUE rbSoundStream::GetLoop( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->getLoop() );
}

// SoundStream#playing_offset
// SoundStream#get_playing_offset
// SoundStream#getPlayingOffset
// SoundStream#offset
VALUE rbSoundStream::GetPlayingOffset( VALUE aSelf )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
	*time = rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->getPlayingOffset();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// SoundStream#sample_rate
// SoundStream#get_sample_rate
// SoundStream#getSampleRate
VALUE rbSoundStream::GetSampleRate( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->getSampleRate() );
}

// SoundStream#channel_count
// SoundStream#get_channel_count
// SoundStream#getChannelCount
VALUE rbSoundStream::GetChannelCount( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->getChannelCount() );
}

// SoundStream#status
// SoundStream#get_status
// SoundStream#getStatus
VALUE rbSoundStream::GetStatus( VALUE aSelf )
{
    return INT2FIX( rbMacros::ToSFML< sf::SoundStream >( aSelf, rbSoundStream::Class )->getStatus() );
}
