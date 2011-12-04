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

#define AUDIO_SOUND_CPP
#include "Sound.hpp"

void rbSound::Init(VALUE SFML)
{
    Sound = rb_define_class_under(SFML, "Sound", rbSoundSource::SoundSource);
    
    // Class methods
    rb_define_alloc_func(Sound, Allocate);
    
    // Instance methods
    rb_define_method(Sound, "initialize_copy", InitializeCopy, 1);
    rb_define_method(Sound, "marshal_dump",    MarshalDump,    0);
    rb_define_method(Sound, "marshal_load",    MarshalLoad,    1);
    rb_define_method(Sound, "memory_usage",    GetMemoryUsage, 0);
    
    // Instance aliasses
}

// Sound#initialize_copy(sound)
VALUE rbSound::InitializeCopy(VALUE self, VALUE sound)
{
    *ToSFML(self) = *ToSFML(sound);
    return self;
}

// Sound#marshal_dump
VALUE rbSound::MarshalDump(VALUE self)
{
    sf::Sound* sound = ToSFML(self);
    
    return rb_ary_new3(1,
                       rb_call_super(0, NULL));
}

// Sound#marshal_load
VALUE rbSound::MarshalLoad(VALUE self, VALUE data)
{
    sf::Sound* sound = ToSFML(self);
    
    rb_call_super(1, (VALUE[]){rb_ary_entry(data, 0)});
    
    return Qnil;
}



// Sound#memory_usage
VALUE rbSound::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::Sound));
}
