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

#ifndef AUDIO_MUSIC_HPP
#define AUDIO_MUSIC_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"
#include "../InputStream.hpp"
#include "SoundStream.hpp"
#include "../System/NonCopyable.hpp"
#include "../System/Time.hpp"

#include <SFML/Audio/Music.hpp>

namespace rbMusic
{

#if defined( AUDIO_MUSIC_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_AUDIO )
    void Init( VALUE SFML );
#endif

#if defined( AUDIO_MUSIC_CPP )
    // Music#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Music#open_from_file(filename)
    // Music#openFromFile(filename)
    // Music#open_file(filename)
    // Music#open(filename)
    static VALUE OpenFromFile( VALUE aaSelf, VALUE aFilename );

    // Music#open_from_memory(data)
    // Music#openFromMemory(data)
    // Music#open_memory(data)
    static VALUE OpenFromMemory( VALUE aSelf, VALUE aData );

    // Music#open_from_stream(stream)
    // Music#openFromStream(stream)
    // Music#open_stream(stream)
    static VALUE OpenFromStream( VALUE aSelf, VALUE aStream );

    // Music#duration
	// Music#get_duration
    // Music#getDuration
    static VALUE GetDuration( VALUE aSelf );

    // Music#inspect
    // Music#to_s
    static VALUE Inspect( VALUE aSelf );

#endif

};

#endif // AUDIO_MUSIC_HPP
