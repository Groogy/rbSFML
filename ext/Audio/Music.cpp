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

#define AUDIO_MUSIC_CPP

#include "Music.hpp"

void rbMusic::Init( VALUE SFML )
{
    rbMusic::Class = rb_define_class_under( SFML, "Music", rbSoundStream::Class );
    rb_include_module( rbMusic::Class, rbNonCopyable::Module );

    // Class methods
    rb_define_alloc_func( rbMusic::Class, rbMacros::Allocate< sf::Music > );

    // Instance methods
    ext_define_method( rbMusic::Class, "marshal_dump",      rbMusic::MarshalDump,      0 );
    ext_define_method( rbMusic::Class, "open_from_file",    rbMusic::OpenFromFile,     1 );
    ext_define_method( rbMusic::Class, "open_from_memory",  rbMusic::OpenFromMemory,   1 );
    ext_define_method( rbMusic::Class, "open_from_stream",  rbMusic::OpenFromStream,   1 );
    ext_define_method( rbMusic::Class, "duration",          rbMusic::GetDuration,      0 );
    ext_define_method( rbMusic::Class, "inspect",           rbMusic::Inspect,          0 );

    // Instance aliasses
    rb_define_alias( rbMusic::Class, "openFromFile",     "open_from_file"   );
    rb_define_alias( rbMusic::Class, "open_file",        "open_from_file"   );
    rb_define_alias( rbMusic::Class, "open",             "open_from_file"   );
    rb_define_alias( rbMusic::Class, "openFromMemory",   "open_from_memory" );
    rb_define_alias( rbMusic::Class, "open_memory",      "open_from_memory" );
    rb_define_alias( rbMusic::Class, "openFromStream",   "open_from_stream" );
    rb_define_alias( rbMusic::Class, "open_stream",      "open_from_stream" );
    rb_define_alias( rbMusic::Class, "getDuration",      "duration"         );
	rb_define_alias( rbMusic::Class, "get_duration",     "duration"         );
    rb_define_alias( rbMusic::Class, "to_s",             "inspect"          );
}

// Music#marshal_dump
VALUE rbMusic::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Music#open_from_file(filename)
// Music#openFromFile(filename)
// Music#open_file(filename)
// Music#open(filename)
VALUE rbMusic::OpenFromFile( VALUE aSelf, VALUE aFilename )
{
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::Music >( aSelf, rbMusic::Class )->openFromFile( StringValueCStr( aFilename ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// Music#open_from_memory(data)
// Music#openFromMemory(data)
// Music#open_memory(data)
VALUE rbMusic::OpenFromMemory( VALUE aSelf, VALUE aData )
{
    StringValue( aData );
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::Music >( aSelf, rbMusic::Class )->openFromMemory( RSTRING_PTR( aData ),
                                                             RSTRING_LEN( aData ) );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// Music#open_from_stream(stream)
// Music#openFromStream(stream)
// Music#open_stream(stream)
VALUE rbMusic::OpenFromStream( VALUE aSelf, VALUE aStream )
{
    rbInputStream stream( aStream );
    rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::Music >( aSelf, rbMusic::Class )->openFromStream( stream );
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// Music#duration
// Music#get_duration
// Music#GetDuration
VALUE rbMusic::GetDuration( VALUE aSelf )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
    *time = rbMacros::ToSFML< sf::Music >( aSelf, rbMusic::Class )->getDuration();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// Music#inspect
// Music#to_s
VALUE rbMusic::Inspect( VALUE aSelf )
{
    return rb_sprintf( "%s(%p: %fs)",
                      rb_obj_classname( aSelf ),
                      (void*)aSelf,
                      rbMacros::ToSFML< sf::Music >( aSelf, rbMusic::Class )->getDuration().asSeconds() );
}
