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

#define AUDIO_SOUNDRECORDER_CPP
#include "SoundRecorder.hpp"
#include "../System/Time.hpp"
#include "../System/NonCopyable.hpp"

void rbSoundRecorder::Init(VALUE SFML)
{
    rbSoundRecorder::Class = rb_define_class_under( SFML, "SoundRecorder", rb_cObject );
	rb_include_module( rbSoundRecorder::Class, rbNonCopyable::Module );
    
    // Class methods
    rb_define_alloc_func( rbSoundRecorder::Class, rbMacros::AbstractAllocate );
    ext_define_class_method( rbSoundRecorder::Class, "available?", rbSoundRecorder::IsAvailable, 0 );
	
	// Class aliases
	VALUE sListener = rb_singleton_class( rbSoundRecorder::Class );
	rb_define_alias( sListener, "is_available?", "available?" );
	rb_define_alias( sListener, "is_available",  "available?" );
	rb_define_alias( sListener, "isAvailable",   "available?" );

    
    // Instance methods
    ext_define_method( rbSoundRecorder::Class, "marshal_dump", rbSoundRecorder::MarshalDump,    0 );
    ext_define_method( rbSoundRecorder::Class, "start",        rbSoundRecorder::Start,         -1 );
    ext_define_method( rbSoundRecorder::Class, "stop",         rbSoundRecorder::Stop,           0 );
    ext_define_method( rbSoundRecorder::Class, "sample_rate",  rbSoundRecorder::GetSampleRate,  0 );
	
	// Instance aliasses
    rb_define_alias( rbSoundRecorder::Class, "getSampleRate",      "sample_rate"    );
	rb_define_alias( rbSoundRecorder::Class, "get_sample_rate",    "sample_rate"    );
}

// SoundRecorder#marshal_dump
VALUE rbSoundRecorder::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// SoundRecorder#start(sample_rate)
VALUE rbSoundRecorder::Start( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
            rbMacros::ToSFML< sf::SoundRecorder >( aSelf, rbSoundRecorder::Class )->start();
            break;
        case 1:
            rbMacros::ToSFML< sf::SoundRecorder >( aSelf, rbSoundRecorder::Class )->start( NUM2UINT( argv[ 0 ] ) );
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..1)", argc );
    }
    return Qnil;
}

// SoundRecorder#stop
VALUE rbSoundRecorder::Stop( VALUE aSelf )
{
    rbMacros::ToSFML< sf::SoundRecorder >( aSelf, rbSoundRecorder::Class )->stop();
    return Qnil;
}

// SoundRecorder#sample_rate
// SoundRecorder#get_sample_rate
// SoundRecorder#getSampleRate
VALUE rbSoundRecorder::GetSampleRate( VALUE aSelf )
{
    return UINT2NUM( rbMacros::ToSFML< sf::SoundRecorder >( aSelf, rbSoundRecorder::Class )->getSampleRate() );
}

// SoundRecorder.available?
// SoundRecorder.is_available?
// SoundRecorder.is_available
// SoundRecorder.isAvailable
VALUE rbSoundRecorder::IsAvailable( VALUE aSelf )
{
    return RBOOL( sf::SoundRecorder::isAvailable() );
}
