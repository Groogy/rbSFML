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

void rbSoundSource::Init(VALUE SFML)
{
    SoundSource = rb_define_class_under(SFML, "SoundSource", rb_cObject);
    
	rb_define_const(SoundSource, "Stopped", INT2FIX(sf::SoundSource::Stopped));
	rb_define_const(SoundSource, "Paused",  INT2FIX(sf::SoundSource::Paused ));
	rb_define_const(SoundSource, "Playing", INT2FIX(sf::SoundSource::Playing));
    
    // Class methods
    rb_define_alloc_func(SoundSource, Allocate);
    
    // Instance methods
    rb_define_method(SoundSource, "marshal_dump",          MarshalDump,            0);
    rb_define_method(SoundSource, "marshal_load",          MarshalLoad,            1);
    rb_define_method(SoundSource, "pitch",                 Pitch,                 -1);
    rb_define_method(SoundSource, "volume",                Volume,                -1);
    rb_define_method(SoundSource, "position",              Position,              -1);
    rb_define_method(SoundSource, "relative_to_listener=", SetRelativeToListener,  1);
    rb_define_method(SoundSource, "relative_to_listener?", IsRelativeToListener,   0);
    rb_define_method(SoundSource, "min_distance",          MinDistance,           -1);
    rb_define_method(SoundSource, "attenuation",           Attenuation,           -1);
    
    // Instance aliasses
    rb_define_alias(SoundSource, "pitch=",                "pitch"                );
    rb_define_alias(SoundSource, "SetPitch",              "pitch"                );
    rb_define_alias(SoundSource, "GetPitch",              "pitch"                );
    rb_define_alias(SoundSource, "volume=",               "volume"               );
    rb_define_alias(SoundSource, "SetVolume",             "volume"               );
    rb_define_alias(SoundSource, "GetVolume",             "volume"               );
    rb_define_alias(SoundSource, "position=",             "position"             );
    rb_define_alias(SoundSource, "SetPosition",           "position"             );
    rb_define_alias(SoundSource, "GetPosition",           "position"             );
    rb_define_alias(SoundSource, "SetRelativeToListener", "relative_to_listener=");
    rb_define_alias(SoundSource, "relative_to_listener",  "relative_to_listener=");
    rb_define_alias(SoundSource, "IsRelativeToListener",  "relative_to_listener?");
    rb_define_alias(SoundSource, "min_distance=",         "min_distance"         );
    rb_define_alias(SoundSource, "SetMinDistance",        "min_distance"         );
    rb_define_alias(SoundSource, "GetMinDistance",        "min_distance"         );
    rb_define_alias(SoundSource, "attenuation=",          "attenuation"          );
    rb_define_alias(SoundSource, "SetAttenuation",        "attenuation"          );
    rb_define_alias(SoundSource, "GetAttenuation",        "attenuation"          );
}

// SoundSource#marshal_dump
VALUE rbSoundSource::MarshalDump(VALUE self)
{
    sf::SoundSource* sound_source = ToSFML(self);
    sf::Vector3f position = sound_source->GetPosition();
    
    VALUE ptr[8];
    ptr[0] = rb_float_new(sound_source->GetPitch());
    ptr[1] = rb_float_new(sound_source->GetVolume());
    ptr[2] = rb_float_new(position.x);
    ptr[3] = rb_float_new(position.y);
    ptr[4] = rb_float_new(position.z);
    ptr[5] = RBOOL(sound_source->IsRelativeToListener());
    ptr[6] = rb_float_new(sound_source->GetMinDistance());
    ptr[7] = rb_float_new(sound_source->GetAttenuation());
    return rb_ary_new4(8, ptr);
}

// SoundSource#marshal_load
VALUE rbSoundSource::MarshalLoad(VALUE self, VALUE data)
{
    sf::SoundSource* sound_source = ToSFML(self);
    sf::Vector3f position;
    
    VALUE* ptr = RARRAY_PTR(data);
    sound_source->SetPitch(NUM2DBL(ptr[0]));
    sound_source->SetVolume(NUM2DBL(ptr[1]));
    position.x = NUM2DBL(ptr[2]);
    position.y = NUM2DBL(ptr[3]);
    position.z = NUM2DBL(ptr[4]);
    sound_source->SetPosition(position);
    sound_source->SetRelativeToListener(RTEST(ptr[5]));
    sound_source->SetMinDistance(NUM2DBL(ptr[6]));
    sound_source->SetAttenuation(NUM2DBL(ptr[7]));
    return Qnil;
}

// SoundSource#pitch
// SoundSource#pitch=(pitch)
// SoundSource#SetPitch(pitch)
// SoundSource#GetPitch
// SoundSource#pitch(pitch)
VALUE rbSoundSource::Pitch(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return rb_float_new(ToSFML(self)->GetPitch());
        case 1:
            ToSFML(self)->SetPitch(NUM2DBL(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0..1)", argc);
    }
    
    return Qnil;
}

// SoundSource#volume(volume)
// SoundSource#volume=(volume)
// SoundSource#SetVolume(volume)
// SoundSource#GetVolume
// SoundSource#volume
VALUE rbSoundSource::Volume(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return rb_float_new(ToSFML(self)->GetVolume());
        case 1:
            ToSFML(self)->SetVolume(NUM2DBL(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0..1)", argc);
    }
    
    return Qnil;
}

// SoundSource#position(position)
// SoundSource#position=(v)
// SoundSource#SetPosition(position)
// SoundSource#SetPosition(x, y, z)
// SoundSource#GetPosition
// SoundSource#position(x, y, z)
// SoundSource#position
VALUE rbSoundSource::Position(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
        {
            sf::Vector3f pos = ToSFML(self)->GetPosition();
            return rbVector3::ToRuby(&pos);
        }
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf(argv[0]);
            ToSFML(self)->SetPosition(pos);
            break;
        }
        case 3:
            ToSFML(self)->SetPosition(NUM2DBL(argv[0]), NUM2DBL(argv[1]),
                                      NUM2DBL(argv[2]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0, 1, or 3)", argc);
    }
    
    return Qnil;
}

// SoundSource#relative_to_listener=(relative)
// SoundSource#SetRelativeToListener(relative)
// SoundSource#relative_to_listener(relative)
VALUE rbSoundSource::SetRelativeToListener(VALUE self, VALUE relative)
{
    ToSFML(self)->SetRelativeToListener(RTEST(relative));
    return Qnil;
}

// SoundSource#IsRelativeToListener
// SoundSource#relative_to_listener?
VALUE rbSoundSource::IsRelativeToListener(VALUE self)
{
    return RBOOL(ToSFML(self)->IsRelativeToListener());
}

// SoundSource#min_distance(distance)
// SoundSource#min_distance=(distance)
// SoundSource#SetMinDistance(distance)
// SoundSource#GetMinDistance
// SoundSource#min_distance
VALUE rbSoundSource::MinDistance(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return rb_float_new(ToSFML(self)->GetMinDistance());
        case 1:
            ToSFML(self)->SetMinDistance(NUM2DBL(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0..1)", argc);
    }
    
    return Qnil;
}

// SoundSource#attenuation(attenuation)
// SoundSource#attenuation=(attenuation)
// SoundSource#SetAttenuation(attenuation)
// SoundSource#GetAttenuation
// SoundSource#attenuation
VALUE rbSoundSource::Attenuation(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return rb_float_new(ToSFML(self)->GetAttenuation());
        case 1:
            ToSFML(self)->SetAttenuation(NUM2DBL(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0..1)", argc);
    }
    
    return Qnil;
}
