/* rbSFML
 * Copyright (c) 2012 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#include "../rbSFML.hpp"
#include "../InputStream.hpp"

#include <SFML/Audio/SoundBuffer.hpp>

namespace rbSoundBuffer
{

#if defined( AUDIO_SOUNDBUFFER_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML );
#endif

#if defined( AUDIO_SOUNDBUFFER_CPP )
    // SoundBuffer#initialize_copy(other)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );

    // SoundBuffer#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // SoundBuffer#marshal_load
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // SoundBuffer#load_from_file(filename)
    // SoundBuffer#loadFromFile(filename)
    // SoundBuffer#load_file(filename)
    // SoundBuffer#load(filename)
    static VALUE LoadFromFile( VALUE aSelf, VALUE aFilename );

    // SoundBuffer#load_from_memory(data)
    // SoundBuffer#loadFromMemory(data)
    // SoundBuffer#load_memory(data)
    static VALUE LoadFromMemory( VALUE aSelf, VALUE aData );

    // SoundBuffer#load_from_stream(stream)
    // SoundBuffer#loadFromStream(stream)
    // SoundBuffer#load_stream(stream)
    static VALUE LoadFromStream( VALUE aSelf, VALUE aStream );

    // SoundBuffer#load_from_samples(samples, channels_count, sample_rate)
    // SoundBuffer#loadFromSamples(samples, channels_count, sample_rate)
    // SoundBuffer#load_samples(samples, channels_count, sample_rate)
    // SoundBuffer#load_from_samples(samples, samples_count, channels_count, sample_rate)
    // SoundBuffer#loadFromSamples(samples, samples_count, channels_count, sample_rate)
    // SoundBuffer#load_samples(samples, samples_count, channels_count, sample_rate)
    static VALUE LoadFromSamples( int argc, VALUE argv[], VALUE aSelf );

    // SoundBuffer#save_to_file(filename)
    // SoundBuffer#saveToFile(filename)
    // SoundBuffer#save_file(filename)
    // SoundBuffer#save(filename)
    static VALUE SaveToFile( VALUE aSelf, VALUE aFilename );

    // SoundBuffer#samples
	// SoundBuffer#get_samples
    // SoundBuffer#getSamples
    static VALUE GetSamples( VALUE aSelf );

    // SoundBuffer#sample_count
	// SoundBuffer#get_sample_count
    // SoundBuffer#getSampleCount
    static VALUE GetSampleCount( VALUE aSelf );

    // SoundBuffer#sample_rate
	// SoundBuffer#get_sample_rate
    // SoundBuffer#getSampleRate
    static VALUE GetSampleRate( VALUE aSelf );

    // SoundBuffer#channel_count
	// SoundBuffer#get_channel_count
    // SoundBuffer#getChannelCount
    static VALUE GetChannelCount( VALUE aSelf );

    // SoundBuffer#duration
	// SoundBuffer#get_duration
    // SoundBuffer#getDuration
    static VALUE GetDuration( VALUE aSelf );

    // SoundBuffer#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // SoundBuffer#inspect
    // SoundBuffer#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

};

#endif // AUDIO_SOUNDBUFFER_HPP
