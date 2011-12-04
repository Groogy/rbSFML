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

#define AUDIO_SOUNDBUFFER_CPP
#include "SoundBuffer.hpp"

void rbSoundBuffer::Init(VALUE SFML)
{
    SoundBuffer = rb_define_class_under(SFML, "SoundBuffer", rb_cObject);
    
    // Class methods
    rb_define_alloc_func(SoundBuffer, Allocate);
    
    // Instance methods
    rb_define_method(SoundBuffer, "initialize_copy",  InitializeCopy,   1);
    rb_define_method(SoundBuffer, "marshal_dump",     MarshalDump,      0);
    rb_define_method(SoundBuffer, "marshal_load",     MarshalLoad,      1);
    rb_define_method(SoundBuffer, "load_from_file",   LoadFromFile,     1);
    rb_define_method(SoundBuffer, "load_from_memory", LoadFromMemory,   1);
    rb_define_method(SoundBuffer, "samples",          GetSamples,       0);
    rb_define_method(SoundBuffer, "samples_count",    GetSamplesCount,  0);
    rb_define_method(SoundBuffer, "sample_rate",      GetSampleRate,    0);
    rb_define_method(SoundBuffer, "channels_count",   GetChannelsCount, 0);
    rb_define_method(SoundBuffer, "duration",         GetDuration,      0);
    rb_define_method(SoundBuffer, "memory_usage",     GetMemoryUsage,   0);
    
    // Instance aliasses
    rb_define_alias(SoundBuffer, "LoadFromFile",     "load_from_file"  );
    rb_define_alias(SoundBuffer, "LoadFromMemory",   "load_from_memory");
    rb_define_alias(SoundBuffer, "GetSamples",       "samples"         );
    rb_define_alias(SoundBuffer, "GetSamplesCount",  "samples_count"   );
    rb_define_alias(SoundBuffer, "GetSampleRate",    "sample_rate"     );
    rb_define_alias(SoundBuffer, "GetChannelsCount", "channels_count"  );
    rb_define_alias(SoundBuffer, "GetDuration",      "duration"        );
}

// SoundBuffer#initialize_copy(sound_buffer)
VALUE rbSoundBuffer::InitializeCopy(VALUE self, VALUE sound_buffer)
{
    *ToSFML(self) = *ToSFML(sound_buffer);
    return self;
}

// SoundBuffer#marshal_dump
VALUE rbSoundBuffer::MarshalDump(VALUE self)
{
    sf::SoundBuffer* sound_buffer = ToSFML(self);
    
    const sf::Int16* samples_ary = sound_buffer->GetSamples();
    std::size_t samples_count = sound_buffer->GetSamplesCount();
    VALUE samples_str = rb_str_new((char*)samples_ary, samples_count * 2);
    
    return rb_ary_new3(3, samples_str,
                       UINT2NUM(sound_buffer->GetChannelsCount()),
                       UINT2NUM(sound_buffer->GetSampleRate()));
}

// SoundBuffer#marshal_load
VALUE rbSoundBuffer::MarshalLoad(VALUE self, VALUE data)
{
    sf::SoundBuffer* sound_buffer = ToSFML(self);
    
    VALUE samples_str = rb_ary_entry(data, 0);
    const sf::Int16* samples = (sf::Int16*)RSTRING_PTR(samples_str);
    std::size_t samples_count = RSTRING_LEN(samples_str) / 2;
    unsigned int channels_count = NUM2UINT(rb_ary_entry(data, 1));
    unsigned int sample_rate = NUM2UINT(rb_ary_entry(data, 2));
    
    sound_buffer->LoadFromSamples(samples, samples_count, channels_count,
                                  sample_rate);
    
    return Qnil;
}

// SoundBuffer#load_from_file(filename)
// SoundBuffer#LoadFromFile(filename)
VALUE rbSoundBuffer::LoadFromFile(VALUE self, VALUE filename)
{
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->LoadFromFile(StringValueCStr(filename));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#load_from_memory(filename)
// SoundBuffer#LoadFromMemory(filename)
VALUE rbSoundBuffer::LoadFromMemory(VALUE self, VALUE data)
{
    StringValue(data);
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->LoadFromMemory(RSTRING_PTR(data),
                                            RSTRING_LEN(data));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#samples
// SoundBuffer#GetSamples
VALUE rbSoundBuffer::GetSamples(VALUE self)
{
    const sf::Int16* samples = ToSFML(self)->GetSamples();
    std::size_t size = ToSFML(self)->GetSamplesCount();
    VALUE ary = rb_ary_new2(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        rb_ary_push(ary, INT2FIX(samples[i]));
    }
    
    return ary;
}

// SoundBuffer#samples_count
// SoundBuffer#GetSamplesCount
VALUE rbSoundBuffer::GetSamplesCount(VALUE self)
{
    return INT2NUM(ToSFML(self)->GetSamplesCount());
}

// SoundBuffer#sample_rate
// SoundBuffer#GetSampleRate
VALUE rbSoundBuffer::GetSampleRate(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetSampleRate());
}

// SoundBuffer#channels_count
// SoundBuffer#GetChannelsCount
VALUE rbSoundBuffer::GetChannelsCount(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetChannelsCount());
}

// SoundBuffer#duration
// SoundBuffer#GetDuration
VALUE rbSoundBuffer::GetDuration(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetDuration());
}

// SoundBuffer#memory_usage
VALUE rbSoundBuffer::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::SoundBuffer));
}
