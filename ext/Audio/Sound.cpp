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

#define AUDIO_SOUND_CPP

#include "Sound.hpp"

void rbSound::Init( VALUE SFML )
{
    rbSound::Class = rb_define_class_under( SFML, "Sound", rbSoundSource::Class );

    // Class methods
    rb_define_alloc_func( rbSound::Class, rbMacros::Allocate< sf::Sound > );

    // Instance methods
    rb_define_method( rbSound::Class, "initialize",      rbSound::Initialize,       -1 );
    rb_define_method( rbSound::Class, "initialize_copy", rbSound::InitializeCopy,    1 );
    rb_define_method( rbSound::Class, "marshal_dump",    rbSound::MarshalDump,       0 );
    rb_define_method( rbSound::Class, "play",            rbSound::Play,              0 );
    rb_define_method( rbSound::Class, "pause",           rbSound::Pause,             0 );
    rb_define_method( rbSound::Class, "stop",            rbSound::Stop,              0 );
    rb_define_method( rbSound::Class, "buffer=",         rbSound::SetBuffer,         1 );
    rb_define_method( rbSound::Class, "loop=",           rbSound::SetLoop,           1 );
    rb_define_method( rbSound::Class, "playing_offset=", rbSound::SetPlayingOffset,  1 );
    rb_define_method( rbSound::Class, "buffer",          rbSound::GetBuffer,         0 );
    rb_define_method( rbSound::Class, "loop",            rbSound::GetLoop,           0 );
    rb_define_method( rbSound::Class, "playing_offset",  rbSound::GetPlayingOffset,  0 );
    rb_define_method( rbSound::Class, "status",          rbSound::GetStatus,         0 );
    rb_define_method( rbSound::Class, "inspect",         rbSound::Inspect,           0 );
    rb_define_method( rbSound::Class, "memory_usage",    rbSound::GetMemoryUsage,    0 );

    // Instance aliasses
    rb_define_alias( rbSound::Class, "Play",             "play"            );
    rb_define_alias( rbSound::Class, "Pause",            "pause"           );
    rb_define_alias( rbSound::Class, "Stop",             "stop"            );
    rb_define_alias( rbSound::Class, "SetBuffer",        "buffer="         );
    rb_define_alias( rbSound::Class, "SetLoop",          "loop="           );
    rb_define_alias( rbSound::Class, "SetPlayingOffset", "playing_offset=" );
    rb_define_alias( rbSound::Class, "offset=",          "playing_offset=" );
    rb_define_alias( rbSound::Class, "GetBuffer",        "buffer"          );
    rb_define_alias( rbSound::Class, "GetLoop",          "loop"            );
    rb_define_alias( rbSound::Class, "GetPlayingOffset", "playing_offset"  );
    rb_define_alias( rbSound::Class, "offset",           "playing_offset"  );
    rb_define_alias( rbSound::Class, "GetStatus",        "status"          );
    rb_define_alias( rbSound::Class, "to_s",             "inspect"         );
}

// Sound#initialize
// Sound#initialize(sound_buffer)
VALUE rbSound::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
            break;
        case 1:
            SetBuffer( aSelf, argv[ 0 ] );
            break;
        default:
            INVALID_ARGUMENT_LIST( argc, "0..1" );
    }

    return Qnil;
}

// Sound#initialize_copy(sound)
VALUE rbSound::InitializeCopy( VALUE aSelf, VALUE aSound )
{
    *rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class ) = *rbMacros::ToSFML< sf::Sound >( aSound, rbSound::Class );
    rb_iv_set( aSelf, "@__ref__sound_buffer", rb_iv_get( aSound, "@__ref__sound_buffer" ) );
    return aSelf;
}

// Sound#marshal_dump
VALUE rbSound::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Sound#play
// Sound#Play
VALUE rbSound::Play( VALUE aSelf )
{
    rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->Play();
    return Qnil;
}

// Sound#pause
// Sound#Pause
VALUE rbSound::Pause( VALUE aSelf )
{
    rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->Pause();
    return Qnil;
}

// Sound#stop
// Sound#Stop
VALUE rbSound::Stop( VALUE aSelf )
{
    rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->Stop();
    return Qnil;
}

// Sound#buffer=(buffer)
// Sound#SetBuffer(buffer)
VALUE rbSound::SetBuffer( VALUE aSelf, VALUE aBuffer )
{
    rb_iv_set( aSelf, "@__ref__sound_buffer", aBuffer );
    rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->SetBuffer( *rbMacros::ToSFML< sf::SoundBuffer >( aBuffer, rbSoundBuffer::Class ) );
    return Qnil;
}

// Sound#loop=(loop)
// Sound#SetLoop(loop)
VALUE rbSound::SetLoop( VALUE aSelf, VALUE aLoop )
{
    rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->SetLoop( RTEST( aLoop ) );
    return Qnil;
}

// Sound#playing_offset=(offset)
// Sound#SetPlayingOffset(offset)
// Sound#offset=(offset)
VALUE rbSound::SetPlayingOffset( VALUE aSelf, VALUE anOffset )
{
    rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->SetPlayingOffset( *rbMacros::ToSFML< sf::Time >( anOffset, rbTime::Class ) );
    return Qnil;
}

// Sound#buffer
// Sound#GetBuffer
VALUE rbSound::GetBuffer( VALUE aSelf )
{
    return rb_iv_get( aSelf, "@__ref__sound_buffer" );
}

// Sound#loop
// Sound#GetLoop
VALUE rbSound::GetLoop( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->GetLoop() );
}

// Sound#playing_offset
// Sound#GetPlayingOffset
// Sound#offset
VALUE rbSound::GetPlayingOffset( VALUE aSelf )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
    *time = rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->GetPlayingOffset();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// Sound#status
// Sound#GetStatus
VALUE rbSound::GetStatus( VALUE aSelf )
{
    return INT2FIX( rbMacros::ToSFML< sf::Sound >( aSelf, rbSound::Class )->GetStatus() );
}

// Sound#inspect
// Sound#to_s
VALUE rbSound::Inspect( VALUE aSelf )
{
    return rb_sprintf( "%s(%p)",
                       rb_obj_classname( aSelf ),
                       reinterpret_cast< void* >( aSelf ) );
}

// Sound#memory_usage
VALUE rbSound::GetMemoryUsage( VALUE aSelf )
{
    return SIZET2NUM( sizeof( sf::Sound ) );
}
