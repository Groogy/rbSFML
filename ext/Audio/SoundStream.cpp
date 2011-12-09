/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

void rbSoundStream::Init(VALUE SFML)
{
    SoundStream = rb_define_class_under(SFML, "SoundStream", rbSoundSource::SoundSource);
    
    // Class methods
    rb_define_alloc_func(SoundStream, Allocate);
    
    // Instance methods
    rb_define_method(SoundStream, "play",            Play,             0);
    rb_define_method(SoundStream, "pause",           Pause,            0);
    rb_define_method(SoundStream, "stop",            Stop,             0);
    rb_define_method(SoundStream, "loop=",           SetLoop,          1);
    rb_define_method(SoundStream, "playing_offset=", SetPlayingOffset, 1);
    rb_define_method(SoundStream, "loop",            GetLoop,          0);
    rb_define_method(SoundStream, "playing_offset",  GetPlayingOffset, 0);
    rb_define_method(SoundStream, "sample_rate",     GetSampleRate,    0);
    rb_define_method(SoundStream, "channels_count",  GetChannelsCount, 0);
    rb_define_method(SoundStream, "status",          GetStatus,        0);
    
    // Instance aliasses
    rb_define_alias(SoundStream, "Play",             "play"           );
    rb_define_alias(SoundStream, "Pause",            "pause"          );
    rb_define_alias(SoundStream, "Stop",             "stop"           );
    rb_define_alias(SoundStream, "SetLoop",          "loop="          );
    rb_define_alias(SoundStream, "SetPlayingOffset", "playing_offset=");
    rb_define_alias(SoundStream, "offset=",          "playing_offset=");
    rb_define_alias(SoundStream, "GetLoop",          "loop"           );
    rb_define_alias(SoundStream, "GetPlayingOffset", "playing_offset" );
    rb_define_alias(SoundStream, "offset",           "playing_offset" );
    rb_define_alias(SoundStream, "GetSampleRate",    "sample_rate"    );
    rb_define_alias(SoundStream, "GetChannelsCount", "channels_count" );
    rb_define_alias(SoundStream, "channels",         "channels_count" );
    rb_define_alias(SoundStream, "GetStatus",        "status"         );
}

// SoundStream#play
// SoundStream#Play
VALUE rbSoundStream::Play(VALUE self)
{
    ToSFML(self)->Play();
    return Qnil;
}

// SoundStream#pause
// SoundStream#Pause
VALUE rbSoundStream::Pause(VALUE self)
{
    ToSFML(self)->Pause();
    return Qnil;
}

// SoundStream#stop
// SoundStream#Stop
VALUE rbSoundStream::Stop(VALUE self)
{
    ToSFML(self)->Stop();
    return Qnil;
}

// SoundStream#loop=(loop)
// SoundStream#SetLoop(loop)
VALUE rbSoundStream::SetLoop(VALUE self, VALUE loop)
{
    ToSFML(self)->SetLoop(RTEST(loop));
    return Qnil;
}

// SoundStream#playing_offset=(offset)
// SoundStream#SetPlayingOffset(offset)
// SoundStream#offset=(offset)
VALUE rbSoundStream::SetPlayingOffset(VALUE self, VALUE offset)
{
    ToSFML(self)->SetPlayingOffset(NUM2UINT(offset));
    return Qnil;
}

// SoundStream#loop
// SoundStream#GetLoop
VALUE rbSoundStream::GetLoop(VALUE self)
{
    return RBOOL(ToSFML(self)->GetLoop());
}

// SoundStream#playing_offset
// SoundStream#GetPlayingOffset
// SoundStream#offset
VALUE rbSoundStream::GetPlayingOffset(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetPlayingOffset());
}

// SoundStream#sample_rate
// SoundStream#GetSampleRate
VALUE rbSoundStream::GetSampleRate(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetSampleRate());
}

// SoundStream#channels_count
// SoundStream#GetChannelsCount
// SoundStream#channels
VALUE rbSoundStream::GetChannelsCount(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetChannelsCount());
}

// SoundStream#status
// SoundStream#GetStatus
VALUE rbSoundStream::GetStatus(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetStatus());
}
