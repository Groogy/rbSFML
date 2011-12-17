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

#ifndef AUDIO_SOUNDBUFFERRECORDER_HPP
#define AUDIO_SOUNDBUFFERRECORDER_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <Audio/SoundBuffer.hpp>
#include <Audio/SoundRecorder.hpp>

#include <SFML/Audio/SoundBufferRecorder.hpp>

namespace rbSoundBufferRecorder
{
    
    static inline void Free(void* sound_buffer_recorder);
    static inline VALUE Allocate(VALUE);
    
    static inline VALUE ToRuby(VALUE other, VALUE klass=false);
    static inline VALUE ToRuby(sf::SoundBufferRecorder* sound_buffer_recorder, VALUE klass=false);
    static inline sf::SoundBufferRecorder* ToSFML(VALUE sound_buffer_recorder, VALUE klass=false);
    
#if defined(AUDIO_SOUNDBUFFERRECORDER_CPP)
    VALUE SoundBufferRecorder;
#else
    extern VALUE SoundBufferRecorder;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML);
#endif

#if defined(AUDIO_SOUNDBUFFERRECORDER_CPP)
    // SoundBufferRecorder#buffer
    // SoundBufferRecorder#GetBuffer
    static VALUE GetBuffer(VALUE self);
    
    // SoundBufferRecorder#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif

};

void rbSoundBufferRecorder::Free(void* sound_buffer_recorder)
{
    delete (sf::SoundBufferRecorder*)sound_buffer_recorder;
}

VALUE rbSoundBufferRecorder::Allocate(VALUE self)
{
    sf::SoundBufferRecorder* sound_buffer_recorder = new(std::nothrow) sf::SoundBufferRecorder;
    if (sound_buffer_recorder == NULL) rb_memerror();
    return ToRuby(sound_buffer_recorder, self);
}

VALUE rbSoundBufferRecorder::ToRuby(VALUE other, VALUE klass)
{
    if (!klass)
        klass = SoundBufferRecorder;
    
    if (rb_obj_is_kind_of(other, SoundBufferRecorder))
        return other;
    
    rb_raise(rb_eTypeError, "can't convert %s into %s",
             rb_obj_classname(other), rb_class2name(klass));
}

VALUE rbSoundBufferRecorder::ToRuby(sf::SoundBufferRecorder* sound_buffer_recorder, VALUE klass)
{
    if (!klass)
        klass = SoundBufferRecorder;
    
    return rb_data_object_alloc(klass, sound_buffer_recorder, NULL, Free);
}

sf::SoundBufferRecorder* rbSoundBufferRecorder::ToSFML(VALUE sound_buffer_recorder, VALUE klass)
{
    sound_buffer_recorder = ToRuby(sound_buffer_recorder, klass);
    return (sf::SoundBufferRecorder*)DATA_PTR(sound_buffer_recorder);
}

#endif // AUDIO_SOUNDBUFFERRECORDER_HPP
