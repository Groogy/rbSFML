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
    static inline sf::SoundSource* ToSFML(VALUE sound_source);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(AUDIO_SOUNDSOURCE_CPP)
    VALUE SoundSource;
#else
    extern VALUE SoundSource;
#endif
    
#if defined(RBSFML_AUDIO)
    void Init(VALUE SFML); 
#endif
    
#if defined(AUDIO_SOUNDSOURCE_CPP)
    // SoundSource#pitch(pitch)
    // SoundSource#pitch=(pitch)
    // SoundSource#SetPitch(pitch)
    // SoundSource#GetPitch
    // SoundSource#pitch
    static VALUE Pitch(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#volume(volume)
    // SoundSource#volume=(volume)
    // SoundSource#SetVolume(volume)
    // SoundSource#GetVolume
    // SoundSource#volume
    static VALUE Volume(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#position(position)
    // SoundSource#position=(v)
    // SoundSource#SetPosition(position)
    // SoundSource#SetPosition(x, y, z)
    // SoundSource#GetPosition
    // SoundSource#position(x, y, z)
    // SoundSource#position
    static VALUE Position(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#relative_to_listener=(relative)
    // SoundSource#SetRelativeToListener(relative)
    // SoundSource#relative_to_listener(relative)
    static VALUE SetRelativeToListener(VALUE self, VALUE relative);
    
    // SoundSource#IsRelativeToListener
    // SoundSource#relative_to_listener?
    static VALUE IsRelativeToListener(VALUE self);
    
    // SoundSource#min_distance(distance)
    // SoundSource#min_distance=(distance)
    // SoundSource#SetMinDistance(distance)
    // SoundSource#GetMinDistance
    // SoundSource#min_distance
    static VALUE MinDistance(int argc, VALUE argv[], VALUE self);
    
    // SoundSource#attenuation(attenuation)
    // SoundSource#attenuation=(attenuation)
    // SoundSource#SetAttenuation(attenuation)
    // SoundSource#GetAttenuation
    // SoundSource#attenuation
    static VALUE Attenuation(int argc, VALUE argv[], VALUE self);
#endif
    
}

VALUE rbSoundSource::Allocate(VALUE)
{
	rb_raise(rb_eNotImpError, "can't allocate instance of abstract class");
    return Qnil;
}

sf::SoundSource* rbSoundSource::ToSFML(VALUE sound_source)
{
    return (sf::SoundSource*)DATA_PTR(sound_source);
}

#endif // AUDIO_SOUNDSOURCE_HPP
