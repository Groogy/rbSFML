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

#ifndef AUDIO_SOUNDRECORDER_HPP
#define AUDIO_SOUNDRECORDER_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/Audio/SoundRecorder.hpp>

namespace rbSoundRecorder
{
    static inline VALUE Allocate(VALUE);
    static inline sf::SoundRecorder* ToSFML(VALUE sound_recorder);
    
#if defined(AUDIO_SOUNDRECORDER_CPP)
    VALUE SoundRecorder;
#else
    extern VALUE SoundRecorder;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML); 
#endif
    
#if defined(AUDIO_SOUNDRECORDER_CPP)
    // SoundRecorder#clone
    static VALUE Clone(VALUE self);
    
    // SoundRecorder#dup
    static VALUE Dup(VALUE self);
    
    // SoundRecorder#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // SoundRecorder#start(sample_rate)
    // SoundRecorder#Start(sample_rate)
    static VALUE Start(int argc, VALUE argv[], VALUE self);
    
    // SoundRecorder#stop
    // SoundRecorder#Stop
    static VALUE Stop(VALUE self);
    
    // SoundRecorder#sample_rate
    // SoundRecorder#GetSampleRate
    static VALUE GetSampleRate(VALUE self);
    
    // SoundRecorder::available?
    // SoundRecorder::IsAvailable
    static VALUE IsAvailable(VALUE self);
#endif
    
}

VALUE rbSoundRecorder::Allocate(VALUE self)
{
    rb_raise(rb_eRuntimeError, "can't allocate instance of abstract class");
    return Qnil;
}

sf::SoundRecorder* rbSoundRecorder::ToSFML(VALUE sound_recorder)
{
    return (sf::SoundRecorder*)DATA_PTR(sound_recorder);
}

#endif // AUDIO_SOUNDRECORDER_HPP
