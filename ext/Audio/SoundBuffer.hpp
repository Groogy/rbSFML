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

#ifndef AUDIO_SOUNDBUFFER_HPP
#define AUDIO_SOUNDBUFFER_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/Audio/SoundBuffer.hpp>

namespace rbSoundBuffer
{
    
    static inline void Free(void* sound_buffer);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::SoundBuffer* sound_buffer);
    static inline VALUE ToRuby(sf::SoundBuffer& sound_buffer);
    static inline sf::SoundBuffer* ToSFML(VALUE sound_buffer);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(AUDIO_SOUNDBUFFER_CPP)
    VALUE SoundBuffer;
#else
    extern VALUE SoundBuffer;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML);
#endif

#if defined(AUDIO_SOUNDBUFFER_CPP)
    // SoundBuffer#initialize_copy(other)
    static VALUE InitializeCopy(VALUE self, VALUE sound_buffer);
    
    // SoundBuffer#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // SoundBuffer#marshal_load
    static VALUE MarshalLoad(VALUE self, VALUE data);
    
    // SoundBuffer#load_from_file(filename)
    // SoundBuffer#LoadFromFile(filename)
    static VALUE LoadFromFile(VALUE self, VALUE filename);
    
    // SoundBuffer#load_from_memory(filename)
    // SoundBuffer#LoadFromMemory(filename)
    static VALUE LoadFromMemory(VALUE self, VALUE data);
    
    // SoundBuffer#samples
    // SoundBuffer#GetSamples
    static VALUE GetSamples(VALUE self);
    
    // SoundBuffer#samples_count
    // SoundBuffer#GetSamplesCount
    static VALUE GetSamplesCount(VALUE self);
    
    // SoundBuffer#sample_rate
    // SoundBuffer#GetSampleRate
    static VALUE GetSampleRate(VALUE self);
    
    // SoundBuffer#channels_count
    // SoundBuffer#GetChannelsCount
    static VALUE GetChannelsCount(VALUE self);
    
    // SoundBuffer#duration
    // SoundBuffer#GetDuration
    static VALUE GetDuration(VALUE self);
    
    // SoundBuffer#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif

};

void rbSoundBuffer::Free(void* sound_buffer)
{
    delete (sf::SoundBuffer*)sound_buffer;
}

VALUE rbSoundBuffer::Allocate(VALUE)
{
    sf::SoundBuffer* sound_buffer = new(std::nothrow) sf::SoundBuffer;
    if (sound_buffer == NULL) rb_memerror();
    return ToRuby(sound_buffer);
}

VALUE rbSoundBuffer::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, SoundBuffer))
        return other;
    else
        rb_raise(rb_eTypeError,
                 "can't convert %s into SoundBuffer", rb_obj_classname(other));
}

VALUE rbSoundBuffer::ToRuby(sf::SoundBuffer* sound_buffer)
{
    return rb_data_object_alloc(SoundBuffer, sound_buffer, NULL, Free);
}

VALUE rbSoundBuffer::ToRuby(sf::SoundBuffer& sound_buffer)
{
    return rb_data_object_alloc(SoundBuffer, &sound_buffer, NULL, NULL);
}

sf::SoundBuffer* rbSoundBuffer::ToSFML(VALUE sound_buffer)
{
    sound_buffer = ToRuby(sound_buffer);
    return (sf::SoundBuffer*)DATA_PTR(sound_buffer);
}

#endif // AUDIO_SOUNDBUFFER_HPP
