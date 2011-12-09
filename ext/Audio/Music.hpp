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

#ifndef AUDIO_MUSIC_HPP
#define AUDIO_MUSIC_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <InputStream.hpp>
#include <Audio/SoundStream.hpp>

#include <SFML/Audio/Music.hpp>

namespace rbMusic
{
    
    static inline void Free(void* music);
    static inline VALUE Allocate(VALUE);
    
    static inline VALUE ToRuby(VALUE other, VALUE klass=false);
    static inline VALUE ToRuby(sf::Music* music, VALUE klass=false);
    static inline sf::Music* ToSFML(VALUE music, VALUE klass=false);
    
#if defined(AUDIO_MUSIC_CPP)
    VALUE Music;
#else
    extern VALUE Music;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML);
#endif

#if defined(AUDIO_MUSIC_CPP)
    // Music#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // Music#clone
    static VALUE Clone(VALUE self);
    
    // Music#dup
    static VALUE Dup(VALUE self);
    
    // Music#open_from_file(filename)
    // Music#OpenFromFile(filename)
    // Music#open_file(filename)
    // Music#open(filename)
    static VALUE OpenFromFile(VALUE self, VALUE filename);
    
    // Music#open_from_memory(data)
    // Music#OpenFromMemory(data)
    // Music#open_memory(data)
    static VALUE OpenFromMemory(VALUE self, VALUE data);
    
    // Music#open_from_stream(stream)
    // Music#OpenFromStream(stream)
    // Music#open_stream(stream)
    static VALUE OpenFromStream(VALUE self, VALUE stream);
    
    // Music#duration
    // Music#GetDuration
    static VALUE GetDuration(VALUE self);
    
    // Music#inspect
    // Music#to_s
    static VALUE Inspect(VALUE self);
    
    // Music#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif

};

void rbMusic::Free(void* music)
{
    delete (sf::Music*)music;
}

VALUE rbMusic::Allocate(VALUE self)
{
    sf::Music* music = new(std::nothrow) sf::Music;
    if (music == NULL) rb_memerror();
    return ToRuby(music, self);
}

VALUE rbMusic::ToRuby(VALUE other, VALUE klass)
{
    if (!klass)
        klass = Music;
    
    if (rb_obj_is_kind_of(other, Music))
        return other;
    
    rb_raise(rb_eTypeError, "can't convert %s into %s",
             rb_obj_classname(other), rb_class2name(klass));
}

VALUE rbMusic::ToRuby(sf::Music* music, VALUE klass)
{
    if (!klass)
        klass = Music;
    
    return rb_data_object_alloc(klass, music, NULL, Free);
}

sf::Music* rbMusic::ToSFML(VALUE music, VALUE klass)
{
    music = ToRuby(music, klass);
    return (sf::Music*)DATA_PTR(music);
}

#endif // AUDIO_MUSIC_HPP
