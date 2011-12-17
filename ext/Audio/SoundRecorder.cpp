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

#define AUDIO_SOUNDRECORDER_CPP
#include "SoundRecorder.hpp"

void rbSoundRecorder::Init(VALUE SFML)
{
    SoundRecorder = rb_define_class_under(SFML, "SoundRecorder", rb_cObject);
    
    // Class methods
    rb_define_alloc_func(SoundRecorder, Allocate);
    rb_define_singleton_method(SoundRecorder, "available?", IsAvailable, 0);
    
    // Singleton aliasses
    VALUE sSoundRecorder = rb_singleton_class(SoundRecorder);
    rb_define_alias(sSoundRecorder, "IsAvailable", "available?");
    
    // Instance methods
    rb_define_method(SoundRecorder, "clone",        Clone,          0);
    rb_define_method(SoundRecorder, "dup",          Dup,            0);
    rb_define_method(SoundRecorder, "marshal_dump", MarshalDump,    0);
    rb_define_method(SoundRecorder, "start",        Start,         -1);
    rb_define_method(SoundRecorder, "stop",         Stop,           0);
    rb_define_method(SoundRecorder, "sample_rate",  GetSampleRate,  0);
    
    // Instance aliasses
    rb_define_alias(SoundRecorder, "Start",         "start");
    rb_define_alias(SoundRecorder, "Stop",          "stop");
    rb_define_alias(SoundRecorder, "GetSampleRate", "sample_rate");
}

// SoundRecorder#clone
VALUE rbSoundRecorder::Clone(VALUE self)
{
    rb_raise(rb_eTypeError, "can't clone instance of %s",
             rb_obj_classname(self));
    return Qnil;
}

// SoundRecorder#dup
VALUE rbSoundRecorder::Dup(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dup instance of %s",
             rb_obj_classname(self));
    return Qnil;
}

// SoundRecorder#marshal_dump
VALUE rbSoundRecorder::MarshalDump(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dump %s", rb_obj_classname(self));
    return Qnil;
}

// SoundRecorder#start(sample_rate)
// SoundRecorder#Start(sample_rate)
VALUE rbSoundRecorder::Start(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
            ToSFML(self)->Start();
            break;
        case 1:
            ToSFML(self)->Start(NUM2UINT(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
    return Qnil;
}

// SoundRecorder#stop
// SoundRecorder#Stop
VALUE rbSoundRecorder::Stop(VALUE self)
{
    ToSFML(self)->Stop();
    return Qnil;
}

// SoundRecorder#sample_rate
// SoundRecorder#GetSampleRate
VALUE rbSoundRecorder::GetSampleRate(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetSampleRate());
}

// SoundRecorder::available?
// SoundRecorder::IsAvailable
VALUE rbSoundRecorder::IsAvailable(VALUE self)
{
    return RBOOL(sf::SoundRecorder::IsAvailable());
}
