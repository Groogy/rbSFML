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
    rb_define_method( rbSoundSource::Class, "marshal_dump",          rbSoundSource::MarshalDump,            0 );
    rb_define_method( rbSoundSource::Class, "marshal_load",          rbSoundSource::MarshalLoad,            1 );
    rb_define_method( rbSoundSource::Class, "get_pitch",             rbSoundSource::GetPitch,               0 );
    rb_define_method( rbSoundSource::Class, "set_pitch",             rbSoundSource::SetPitch,               1 );
    rb_define_method( rbSoundSource::Class, "get_volume",            rbSoundSource::GetVolume,              0 );
    rb_define_method( rbSoundSource::Class, "set_volume",            rbSoundSource::SetVolume,              1 );
    rb_define_method( rbSoundSource::Class, "get_position",          rbSoundSource::GetPosition,            0 );
    rb_define_method( rbSoundSource::Class, "set_position",          rbSoundSource::SetPosition,           -1 );
    rb_define_method( rbSoundSource::Class, "relative_to_listener=", rbSoundSource::SetRelativeToListener,  1 );
    rb_define_method( rbSoundSource::Class, "relative_to_listener?", rbSoundSource::IsRelativeToListener,   0 );
    rb_define_method( rbSoundSource::Class, "get_min_distance",      rbSoundSource::GetMinDistance,         0 );
    rb_define_method( rbSoundSource::Class, "set_min_distance",      rbSoundSource::SetMinDistance,         1 );
    rb_define_method( rbSoundSource::Class, "get_attenuation",       rbSoundSource::GetAttenuation,         0 );
    rb_define_method( rbSoundSource::Class, "set_attenuation",       rbSoundSource::SetAttenuation,         1 );
    
    // Instance aliasses
	rb_define_alias( rbSoundSource::Class, "pitch", 				"get_pitch"				);
    rb_define_alias( rbSoundSource::Class, "pitch=",                "set_pitch"             );
	rb_define_alias( rbSoundSource::Class, "volume",               	"get_volume"            );
    rb_define_alias( rbSoundSource::Class, "volume=",               "set_volume"            );
	rb_define_alias( rbSoundSource::Class, "position",            	"get_position"          );
    rb_define_alias( rbSoundSource::Class, "position=",             "set_position"          );
	rb_define_alias( rbSoundSource::Class, "min_distance",          "get_min_distance"      );
    rb_define_alias( rbSoundSource::Class, "min_distance=",         "set_min_distance"      );
	rb_define_alias( rbSoundSource::Class, "attenuation",           "get_attenuation"       );
    rb_define_alias( rbSoundSource::Class, "attenuation=",          "set_attenuation"       );
}

// SoundSource#marshal_dump
VALUE rbSoundSource::MarshalDump( VALUE aSelf )
{
    sf::SoundSource* soundSource = rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class );
    sf::Vector3f position = soundSource->GetPosition();
    
    VALUE ptr[8];
    ptr[0] = rb_float_new( soundSource->GetPitch() );
    ptr[1] = rb_float_new( soundSource->GetVolume() );
    ptr[2] = rb_float_new( position.x );
    ptr[3] = rb_float_new( position.y );
    ptr[4] = rb_float_new( position.z );
    ptr[5] = RBOOL( soundSource->IsRelativeToListener() );
    ptr[6] = rb_float_new( soundSource->GetMinDistance() );
    ptr[7] = rb_float_new( soundSource->GetAttenuation() );
    return rb_ary_new4( 8, ptr );
}

// SoundSource#marshal_load
VALUE rbSoundSource::MarshalLoad( VALUE aSelf, VALUE aData )
{
    sf::SoundSource* soundSource = rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class );
    
    VALUE* ptr = RARRAY_PTR( aData );
    soundSource->SetPitch( NUM2DBL( ptr[ 0 ] ) );
    soundSource->SetVolume( NUM2DBL( ptr[ 1 ] ) );
    float x = NUM2DBL( ptr[ 2 ] );
    float y = NUM2DBL( ptr[ 3 ] );
    float z = NUM2DBL( ptr[ 4 ] );
    soundSource->SetPosition( x, y, z );
    soundSource->SetRelativeToListener( RTEST( ptr[ 5 ] ) );
    soundSource->SetMinDistance( NUM2DBL( ptr[ 6 ] ) );
    soundSource->SetAttenuation( NUM2DBL( ptr[ 7 ] ) );
    return Qnil;
}

// SoundSource#GetPitch
VALUE rbSoundSource::GetPitch( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->GetPitch() );
}

// SoundSource#SetPitch(pitch)
VALUE rbSoundSource::SetPitch( VALUE aSelf, VALUE aPitch )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetPitch( NUM2DBL( aPitch ) );
    return Qnil;
}

// SoundSource#GetVolume
VALUE rbSoundSource::GetVolume( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->GetVolume() );
}

// SoundSource#SetVolume(volume)
VALUE rbSoundSource::SetVolume( VALUE aSelf, VALUE aVolume )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetVolume( NUM2DBL( aVolume ) );
    return Qnil;
}

// SoundSource#GetPosition
VALUE rbSoundSource::GetPosition( VALUE aSelf )
{
    sf::Vector3f pos = rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->GetPosition();
    return rbVector3::ToRuby( pos );
}

// SoundSource#SetPosition(position)
// SoundSource#SetPosition(x, y, z)
VALUE rbSoundSource::SetPosition( int argc, VALUE argv[], VALUE aSelf )
{
    switch (argc)
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf( argv[0] );
            rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetPosition(pos);
            break;
        }
        case 3:
        {
            float x = NUM2DBL( argv[ 0 ] );
            float y = NUM2DBL( argv[ 1 ] );
            float z = NUM2DBL( argv[ 2 ] );
            rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetPosition( x, y, z );
            break;
        }
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 1 or 3)", argc );
    }
    return Qnil;
}

// SoundSource#relative_to_listener(relative)
// SoundSource#relative_to_listener=(relative)
// SoundSource#SetRelativeToListener(relative)
VALUE rbSoundSource::SetRelativeToListener( VALUE aSelf, VALUE aRelative )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetRelativeToListener( RTEST( aRelative ) );
    return Qnil;
}

// SoundSource#relative_to_listener?
// SoundSource#IsRelativeToListener
VALUE rbSoundSource::IsRelativeToListener( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->IsRelativeToListener() );
}

// SoundSource#GetMinDistance
VALUE rbSoundSource::GetMinDistance( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->GetMinDistance() );
}

// SoundSource#SetMinDistance(attenuation)
VALUE rbSoundSource::SetMinDistance( VALUE aSelf, VALUE anAttenuation )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetMinDistance( NUM2DBL( anAttenuation ) );
    return Qnil;
}

// SoundSource#GetAttenuation
VALUE rbSoundSource::GetAttenuation( VALUE aSelf )
{
    return rb_float_new( rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->GetAttenuation() );
}

// SoundSource#SetAttenuation(attenuation)
VALUE rbSoundSource::SetAttenuation( VALUE aSelf, VALUE anAttenuation )
{
    rbMacros::ToSFML< sf::SoundSource >( aSelf, rbSoundSource::Class )->SetAttenuation( NUM2DBL( anAttenuation ) );
    return Qnil;
}
