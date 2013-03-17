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

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"

#include <SFML/Audio/SoundRecorder.hpp>

namespace rbSoundRecorder
{    
#if defined( AUDIO_SOUNDRECORDER_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif
    
#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML ); 
#endif
    
#if defined( AUDIO_SOUNDRECORDER_CPP )    
    // SoundRecorder#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // SoundRecorder#start(sample_rate)
    static VALUE Start( int argc, VALUE argv[], VALUE aSelf );
    
    // SoundRecorder#stop
    static VALUE Stop( VALUE aSelf );
    
    // SoundRecorder#sample_rate
	// SoundRecorder#get_sample_rate
    // SoundRecorder#getSampleRate
    static VALUE GetSampleRate( VALUE aSelf );
    
    // SoundRecorder.available?
	// SoundRecorder.is_available?
	// SoundRecorder.is_available
    // SoundRecorder.isAvailable
    static VALUE IsAvailable( VALUE aSelf );
#endif
    
}

#endif // AUDIO_SOUNDRECORDER_HPP
