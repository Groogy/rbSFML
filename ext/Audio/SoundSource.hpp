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

#ifndef AUDIO_SOUNDSOURCE_HPP
#define AUDIO_SOUNDSOURCE_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <System/Vector3.hpp>

#include <SFML/Audio/SoundSource.hpp>

namespace rbSoundSource
{
    static inline VALUE Allocate(VALUE);
    static inline sf::SoundSource* ToSFML(VALUE sound_source);
    
#if defined(AUDIO_SOUNDSOURCE_CPP)
    VALUE SoundSource;
#else
    extern VALUE SoundSource;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML); 
#endif
    
#if defined(AUDIO_SOUNDSOURCE_CPP)
    // SoundSource#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // SoundSource#marshal_load
    static VALUE MarshalLoad(VALUE self, VALUE data);
    
    // SoundSource#pitch
    // SoundSource#pitch(pitch)
    // SoundSource#pitch=(pitch)
    static VALUE Pitch(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#GetPitch
    static VALUE GetPitch(VALUE self);
    
    // SoundSource#SetPitch(pitch)
    static VALUE SetPitch(VALUE self, VALUE pitch);
    
    // SoundSource#volume
    // SoundSource#volume(volume)
    // SoundSource#volume=(volume)
    static VALUE Volume(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#GetVolume
    static VALUE GetVolume(VALUE self);
    
    // SoundSource#SetVolume(volume)
    static VALUE SetVolume(VALUE self, VALUE volume);
    
    // SoundSource#position
    // SoundSource#position(position)
    // SoundSource#position=(position)
    // SoundSource#position(x, y, z)
    static VALUE Position(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#GetPosition
    static VALUE GetPosition(VALUE self);
    
    // SoundSource#SetPosition(position)
    // SoundSource#SetPosition(x, y, z)
    static VALUE SetPosition(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#relative_to_listener(relative)
    // SoundSource#relative_to_listener=(relative)
    // SoundSource#SetRelativeToListener(relative)
    static VALUE SetRelativeToListener(VALUE self, VALUE relative);
    
    // SoundSource#relative_to_listener?
    // SoundSource#IsRelativeToListener
    static VALUE IsRelativeToListener(VALUE self);
    
    // SoundSource#min_distance
    // SoundSource#min_distance(distance)
    // SoundSource#min_distance=(distance)
    static VALUE MinDistance(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#GetMinDistance
    static VALUE GetMinDistance(VALUE self);
    
    // SoundSource#SetMinDistance(distance)
    static VALUE SetMinDistance(VALUE self, VALUE distance);
    
    // SoundSource#attenuation
    // SoundSource#attenuation(attenuation)
    // SoundSource#attenuation=(attenuation)
    static VALUE Attenuation(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#GetAttenuation
    static VALUE GetAttenuation(VALUE self);
    
    // SoundSource#SetAttenuation(attenuation)
    static VALUE SetAttenuation(VALUE self, VALUE attenuation);
#endif
    
}

VALUE rbSoundSource::Allocate(VALUE self)
{
    rb_raise(rb_eRuntimeError, "can't allocate instance of abstract class");
    return Qnil;
}

sf::SoundSource* rbSoundSource::ToSFML(VALUE sound_source)
{
    return (sf::SoundSource*)DATA_PTR(sound_source);
}

#endif // AUDIO_SOUNDSOURCE_HPP
