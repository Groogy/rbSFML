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

#ifndef AUDIO_SOUND_HPP
#define AUDIO_SOUND_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <Audio/SoundSource.hpp>
#include <Audio/SoundBuffer.hpp>

#include <SFML/Audio/Sound.hpp>

namespace rbSound
{
    
    static inline void Free(void* sound);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::Sound* sound);
    static inline VALUE ToRuby(sf::Sound& sound);
    static inline sf::Sound* ToSFML(VALUE sound);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(AUDIO_SOUND_CPP)
    VALUE Sound;
#else
    extern VALUE Sound;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML);
#endif

#if defined(AUDIO_SOUND_CPP)
    // Sound#initialize
    // Sound#initialize(sound_buffer)
    static VALUE Initialize(int argc, VALUE argv[], VALUE self);
    
    // Sound#initialize_copy(other)
    static VALUE InitializeCopy(VALUE self, VALUE sound);
    
    // Sound#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // Sound#play
    // Sound#Play
    static VALUE Play(VALUE self);
    
    // Sound#pause
    // Sound#Pause
    static VALUE Pause(VALUE self);
    
    // Sound#stop
    // Sound#Stop
    static VALUE Stop(VALUE self);
    
    // Sound#buffer=(buffer)
    // Sound#SetBuffer(buffer)
    static VALUE SetBuffer(VALUE self, VALUE buffer);
    
    // Sound#loop=(loop)
    // Sound#SetLoop(loop)
    static VALUE SetLoop(VALUE self, VALUE loop);
    
    // Sound#playing_offset=(offset)
    // Sound#SetPlayingOffset(offset)
    // Sound#offset=(offset)
    static VALUE SetPlayingOffset(VALUE self, VALUE offset);
    
    // Sound#buffer
    // Sound#GetBuffer
    static VALUE GetBuffer(VALUE self);
    
    // Sound#loop
    // Sound#GetLoop
    static VALUE GetLoop(VALUE self);
    
    // Sound#playing_offset
    // Sound#GetPlayingOffset
    // Sound#offset
    static VALUE GetPlayingOffset(VALUE self);
    
    // Sound#status
    // Sound#GetStatus
    static VALUE GetStatus(VALUE self);
    
    // Sound#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif

};

void rbSound::Free(void* sound)
{
    delete (sf::Sound*)sound;
}

VALUE rbSound::Allocate(VALUE)
{
    sf::Sound* sound = new(std::nothrow) sf::Sound;
    if (sound == NULL) rb_memerror();
    return ToRuby(sound);
}

VALUE rbSound::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, Sound))
        return other;
    else
        rb_raise(rb_eTypeError,
                 "can't convert %s into Sound", rb_obj_classname(other));
}

VALUE rbSound::ToRuby(sf::Sound* sound)
{
    return rb_data_object_alloc(Sound, sound, NULL, Free);
}

VALUE rbSound::ToRuby(sf::Sound& sound)
{
    return rb_data_object_alloc(Sound, &sound, NULL, NULL);
}

sf::Sound* rbSound::ToSFML(VALUE sound)
{
    sound = ToRuby(sound);
    return (sf::Sound*)DATA_PTR(sound);
}

#endif // AUDIO_SOUND_HPP
