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

#define AUDIO_SOUNDSOURCE_CPP
#include "SoundSource.hpp"

void rbSoundSource::Init( VALUE SFML )
{
    rbSoundSource::Class = rb_define_class_under( SFML, "SoundSource", rb_cObject );
    
	rb_define_const( rbSoundSource::Class, "Stopped", INT2FIX( sf::SoundSource::Stopped ) );
	rb_define_const( rbSoundSource::Class, "Paused",  INT2FIX( sf::SoundSource::Paused ) );
	rb_define_const( rbSoundSource::Class, "Playing", INT2FIX( sf::SoundSource::Playing ) );
    
    // Class methods
    rb_define_alloc_func( rbSoundSource::Class, rbMacros::AbstractAllocate );
    
    // Instance methods
    ext_define_method( rbSoundSource::Class, "marshal_dump",          rbSoundSource::MarshalDump,            0 );
    ext_define_method( rbSoundSource::Class, "marshal_load",          rbSoundSource::MarshalLoad,            1 );
    ext_define_method( rbSoundSource::Class, "get_pitch",             rbSoundSource::GetPitch,               0 );
    ext_define_method( rbSoundSource::Class, "set_pitch",             rbSoundSource::SetPitch,               1 );
    ext_define_method( rbSoundSource::Class, "get_volume",            rbSoundSource::GetVolume,              0 );
    ext_define_method( rbSoundSource::Class, "set_volume",            rbSoundSource::SetVolume,              1 );
    ext_define_method( rbSoundSource::Class, "get_position",          rbSoundSource::GetPosition,            0 );
    ext_define_method( rbSoundSource::Class, "set_position",          rbSoundSource::SetPosition,           -1 );
    ext_define_method( rbSoundSource::Class, "relative_to_listener=", rbSoundSource::SetRelativeToListener,  1 );
    ext_define_method( rbSoundSource::Class, "relative_to_listener?", rbSoundSource::IsRelativeToListener,   0 );
    ext_define_method( rbSoundSource::Class, "get_min_distance",      rbSoundSource::GetMinDistance,         0 );
    ext_define_method( rbSoundSource::Class, "set_min_distance",      rbSoundSource::SetMinDistance,         1 );
    ext_define_method( rbSoundSource::Class, "get_attenuation",       rbSoundSource::GetAttenuation,         0 );
    ext_define_method( rbSoundSource::Class, "set_attenuation",       rbSoundSource::SetAttenuation,         1 );
    
    // Instance aliasses
	rb_define_alias( rbSoundSource::Class, "pitch", 				"get_pitch"				);
	rb_define_alias( rbSoundSource::Class, "getPitch", 				"get_pitch"				);
    rb_define_alias( rbSoundSource::Class, "pitch=",                "set_pitch"             );
	rb_define_alias( rbSoundSource::Class, "setPitch",              "set_pitch"             );
	rb_define_alias( rbSoundSource::Class, "volume",               	"get_volume"            );
	rb_define_alias( rbSoundSource::Class, "getVolume",           	"get_volume"            );
    rb_define_alias( rbSoundSource::Class, "volume=",               "set_volume"            );
	rb_define_alias( rbSoundSource::Class, "setVolume",             "set_volume"            );
	rb_define_alias( rbSoundSource::Class, "position",            	"get_position"          );
	rb_define_alias( rbSoundSource::Class, "getPosition",           "get_position"          );
    rb_define_alias( rbSoundSource::Class, "position=",             "set_position"          );
	rb_define_alias( rbSoundSource::Class, "setPosition",           "set_position"          );
	rb_define_alias( rbSoundSource::Class, "min_distance",          "get_min_distance"      );
	rb_define_alias( rbSoundSource::Class, "getMinDistance",        "get_min_distance"      );
    rb_define_alias( rbSoundSource::Class, "min_distance=",         "set_min_distance"      );
	rb_define_alias( rbSoundSource::Class, "setMinDistance",        "set_min_distance"      );
	rb_define_alias( rbSoundSource::Class, "attenuation",           "get_attenuation"       );
	rb_define_alias( rbSoundSource::Class, "getAttenuation",        "get_attenuation"       );
    rb_define_alias( rbSoundSource::Class, "attenuation=",          "set_attenuation"       );
	rb_define_alias( rbSoundSource::Class, "setAttenuation",        "set_attenuation"       );
}

// SoundSource#marshal_dump
VALUE rbSoundSource::MarshalDump( VALUE aSelf )
{
    sf::SoundSource* soundSource = rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class );
    sf::Vector3f position = soundSource->getPosition();
    
    VALUE ptr[8];
    ptr[0] = rb_float_new( soundSource->getPitch() );
    ptr[1] = rb_float_new( soundSource->getVolume() );
    ptr[2] = rb_float_new( position.x );
    ptr[3] = rb_float_new( position.y );
    ptr[4] = rb_float_new( position.z );
    ptr[5] = RBOOL( soundSource->isRelativeToListener() );
    ptr[6] = rb_float_new( soundSource->getMinDistance() );
    ptr[7] = rb_float_new( soundSource->getAttenuation() );
    return rb_ary_new4( 8, ptr );
}

// SoundSource#marshal_load
VALUE rbSoundSource::MarshalLoad( VALUE aSelf, VALUE aData )
{
    sf::SoundSource* soundSource = rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class );
    
    VALUE* ptr = RARRAY_PTR( aData );
    soundSource->setPitch( NUM2DBL( ptr[ 0 ] ) );
    soundSource->setVolume( NUM2DBL( ptr[ 1 ] ) );
    float x = NUM2DBL( ptr[ 2 ] );
    float y = NUM2DBL( ptr[ 3 ] );
    float z = NUM2DBL( ptr[ 4 ] );
    soundSource->setPosition( x, y, z );
    soundSource->setRelativeToListener( RTEST( ptr[ 5 ] ) );
    soundSource->setMinDistance( NUM2DBL( ptr[ 6 ] ) );
    soundSource->setAttenuation( NUM2DBL( ptr[ 7 ] ) );
    return Qnil;
}

// SoundSource#pitch
// SoundSource#get_pitch
// SoundSource#getPitch
VALUE rbSoundSource::GetPitch( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->getPitch() );
}

// SoundSource#pitch=(pitch)
// SoundSource#set_pitch(pitch)
// SoundSource#setPitch(pitch)
VALUE rbSoundSource::SetPitch( VALUE aSelf, VALUE aPitch )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setPitch( NUM2DBL( aPitch ) );
    return Qnil;
}

// SoundSource#volume
// SoundSource#get_volume
// SoundSource#getVolume
VALUE rbSoundSource::GetVolume( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->getVolume() );
}

// SoundSource#volume=(volume)
// SoundSource#set_volume(volume)
// SoundSource#setVolume(volume)
VALUE rbSoundSource::SetVolume( VALUE aSelf, VALUE aVolume )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setVolume( NUM2DBL( aVolume ) );
    return Qnil;
}

// SoundSource#position
// SoundSource#get_position
// SoundSource#getPosition
VALUE rbSoundSource::GetPosition( VALUE aSelf )
{
    sf::Vector3f pos = rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->getPosition();
    return rbVector3::ToRuby( pos );
}

// SoundSource#position=(position)
// SoundSource#set_position(position)
// SoundSource#set_position(x, y, z)
// SoundSource#setPosition(position)
// SoundSource#setPosition(x, y, z)
VALUE rbSoundSource::SetPosition( int argc, VALUE argv[], VALUE aSelf )
{
    switch (argc)
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf( argv[0] );
            rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setPosition(pos);
            break;
        }
        case 3:
        {
            float x = NUM2DBL( argv[ 0 ] );
            float y = NUM2DBL( argv[ 1 ] );
            float z = NUM2DBL( argv[ 2 ] );
            rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setPosition( x, y, z );
            break;
        }
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 1 or 3)", argc );
    }
    return Qnil;
}

// SoundSource#relative_to_listener=(relative)
// SoundSource#set_relative_to_listener(relative)
// SoundSource#setRelativeToListener(relative)
VALUE rbSoundSource::SetRelativeToListener( VALUE aSelf, VALUE aRelative )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setRelativeToListener( RTEST( aRelative ) );
    return Qnil;
}

// SoundSource#relative_to_listener?
// SoundSource#is_relative_to_listener?
// SoundSource#is_relative_to_listener
// SoundSource#isRelativeToListener
VALUE rbSoundSource::IsRelativeToListener( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->isRelativeToListener() );
}

// SoundSource#min_distance
// SoundSource#get_min_distance
// SoundSource#getMinDistance
VALUE rbSoundSource::GetMinDistance( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->getMinDistance() );
}

// SoundSource#min_distance=(attenuation)
// SoundSource#set_min_distance(attenuation)
// SoundSource#setMinDistance(attenuation)
VALUE rbSoundSource::SetMinDistance( VALUE aSelf, VALUE anAttenuation )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setMinDistance( NUM2DBL( anAttenuation ) );
    return Qnil;
}

// SoundSource#attenuation
// SoundSource#get_attenuation
// SoundSource#getAttenuation
VALUE rbSoundSource::GetAttenuation( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->getAttenuation() );
}

// SoundSource#attenuation=(attenuation)
// SoundSource#set_attenuation(attenuation)
// SoundSource#setAttenuation(attenuation)
VALUE rbSoundSource::SetAttenuation( VALUE aSelf, VALUE anAttenuation )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->setAttenuation( NUM2DBL( anAttenuation ) );
    return Qnil;
}
