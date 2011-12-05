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

#define AUDIO_SOUND_CPP
#include "Sound.hpp"

void rbSound::Init(VALUE SFML)
{
    Sound = rb_define_class_under(SFML, "Sound", rbSoundSource::SoundSource);
    
    // Class methods
    rb_define_alloc_func(Sound, Allocate);
    
    // Instance methods
    rb_define_method(Sound, "initialize",      Initialize,       -1);
    rb_define_method(Sound, "initialize_copy", InitializeCopy,    1);
    rb_define_method(Sound, "marshal_dump",    MarshalDump,       0);
    rb_define_method(Sound, "play",            Play,              0);
    rb_define_method(Sound, "pause",           Pause,             0);
    rb_define_method(Sound, "stop",            Stop,              0);
    rb_define_method(Sound, "buffer=",         SetBuffer,         1);
    rb_define_method(Sound, "loop=",           SetLoop,           1);
    rb_define_method(Sound, "playing_offset=", SetPlayingOffset,  1);
    rb_define_method(Sound, "buffer",          GetBuffer,         0);
    rb_define_method(Sound, "loop",            GetLoop,           0);
    rb_define_method(Sound, "playing_offset",  GetPlayingOffset,  0);
    rb_define_method(Sound, "status",          GetStatus,         0);
    rb_define_method(Sound, "memory_usage",    GetMemoryUsage,    0);
    
    // Instance aliasses
    rb_define_alias(Sound, "Play",             "play"           );
    rb_define_alias(Sound, "Pause",            "pause"          );
    rb_define_alias(Sound, "Stop",             "stop"           );
    rb_define_alias(Sound, "SetBuffer",        "buffer="        );
    rb_define_alias(Sound, "SetLoop",          "loop="          );
    rb_define_alias(Sound, "SetPlayingOffset", "playing_offset=");
    rb_define_alias(Sound, "offset=",          "playing_offset=");
    rb_define_alias(Sound, "GetBuffer",        "buffer"         );
    rb_define_alias(Sound, "GetLoop",          "loop"           );
    rb_define_alias(Sound, "GetPlayingOffset", "playing_offset" );
    rb_define_alias(Sound, "offset",           "playing_offset" );
    rb_define_alias(Sound, "GetStatus",        "status"         );
}

// Sound#initialize
// Sound#initialize(sound_buffer)
VALUE rbSound::Initialize(int argc, VALUE* argv, VALUE self)
{
    switch (argc)
    {
        case 0:
            break;
        case 1:
            SetBuffer(self, argv[0]);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
    
    return Qnil;
}

// Sound#initialize_copy(sound)
VALUE rbSound::InitializeCopy(VALUE self, VALUE sound)
{
    *ToSFML(self) = *ToSFML(sound);
    rb_iv_set(self, "@sound_buffer", rb_iv_get(sound, "@sound_buffer"));
    return self;
}

// Sound#marshal_dump
VALUE rbSound::MarshalDump(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dump Sound");
    return Qnil;
}

// Sound#play
// Sound#Play
VALUE rbSound::Play(VALUE self)
{
    ToSFML(self)->Play();
    return Qnil;
}

// Sound#pause
// Sound#Pause
VALUE rbSound::Pause(VALUE self)
{
    ToSFML(self)->Pause();
    return Qnil;
}

// Sound#stop
// Sound#Stop
VALUE rbSound::Stop(VALUE self)
{
    ToSFML(self)->Stop();
    return Qnil;
}

// Sound#buffer=(buffer)
// Sound#SetBuffer(buffer)
VALUE rbSound::SetBuffer(VALUE self, VALUE buffer)
{
    rb_iv_set(self, "@sound_buffer", buffer);
    ToSFML(self)->SetBuffer(*rbSoundBuffer::ToSFML(buffer));
    return Qnil;
}

// Sound#loop=(loop)
// Sound#SetLoop(loop)
VALUE rbSound::SetLoop(VALUE self, VALUE loop)
{
    ToSFML(self)->SetLoop(RTEST(loop));
    return Qnil;
}

// Sound#playing_offset=(offset)
// Sound#SetPlayingOffset(offset)
// Sound#offset=(offset)
VALUE rbSound::SetPlayingOffset(VALUE self, VALUE offset)
{
    ToSFML(self)->SetPlayingOffset(NUM2UINT(offset));
    return Qnil;
}

// Sound#buffer
// Sound#GetBuffer
VALUE rbSound::GetBuffer(VALUE self)
{
    return rb_iv_get(self, "@sound_buffer");
}

// Sound#loop
// Sound#GetLoop
VALUE rbSound::GetLoop(VALUE self)
{
    return RBOOL(ToSFML(self)->GetLoop());
}

// Sound#playing_offset
// Sound#GetPlayingOffset
// Sound#offset
VALUE rbSound::GetPlayingOffset(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetPlayingOffset());
}

// Sound#status
// Sound#GetStatus
VALUE rbSound::GetStatus(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetStatus());
}

// Sound#memory_usage
VALUE rbSound::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::Sound));
}
