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
#if defined( AUDIO_SOUNDSOURCE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif
    
#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML ); 
#endif
    
#if defined( AUDIO_SOUNDSOURCE_CPP )
    // SoundSource#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // SoundSource#marshal_load
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );
    
    // SoundSource#GetPitch
    static VALUE GetPitch( VALUE aSelf );
    
    // SoundSource#SetPitch(pitch)
    static VALUE SetPitch( VALUE aSelf, VALUE aPitch );
    
    // SoundSource#GetVolume
    static VALUE GetVolume( VALUE aSelf );
    
    // SoundSource#SetVolume(volume)
    static VALUE SetVolume( VALUE aSelf, VALUE aVolume );
    
    // SoundSource#GetPosition
    static VALUE GetPosition( VALUE aSelf );
    
    // SoundSource#SetPosition(position)
    // SoundSource#SetPosition(x, y, z)
    static VALUE SetPosition( int argc, VALUE argv[], VALUE aSelf );
    
    // SoundSource#relative_to_listener(relative)
    // SoundSource#relative_to_listener=(relative)
    // SoundSource#SetRelativeToListener(relative)
    static VALUE SetRelativeToListener( VALUE aSelf, VALUE aRelative );
    
    // SoundSource#relative_to_listener?
    // SoundSource#IsRelativeToListener
    static VALUE IsRelativeToListener( VALUE aSelf );
    
    // SoundSource#GetMinDistance
    static VALUE GetMinDistance( VALUE aSelf );
    
    // SoundSource#SetMinDistance(distance)
    static VALUE SetMinDistance( VALUE aSelf, VALUE aDistance );
    
    // SoundSource#GetAttenuation
    static VALUE GetAttenuation( VALUE aSelf );
    
    // SoundSource#SetAttenuation(attenuation)
    static VALUE SetAttenuation( VALUE aSelf, VALUE anAttenuation );
#endif   
}

#endif // AUDIO_SOUNDSOURCE_HPP
