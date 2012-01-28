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

#define AUDIO_SOUNDBUFFER_CPP
#include "SoundBuffer.hpp"

void rbSoundBuffer::Init(VALUE SFML)
{
    rbSoundBuffer::Class = rb_define_class_under(SFML, "SoundBuffer", rb_cObject);

    // Class methods
    rb_define_alloc_func(rbSoundBuffer::Class, Allocate);

    // Instance methods
    rb_define_method(rbSoundBuffer::Class, "initialize_copy",   InitializeCopy,   1);
    rb_define_method(rbSoundBuffer::Class, "marshal_dump",      MarshalDump,      0);
    rb_define_method(rbSoundBuffer::Class, "marshal_load",      MarshalLoad,      1);
    rb_define_method(rbSoundBuffer::Class, "load_from_file",    LoadFromFile,     1);
    rb_define_method(rbSoundBuffer::Class, "load_from_memory",  LoadFromMemory,   1);
    rb_define_method(rbSoundBuffer::Class, "load_from_stream",  LoadFromStream,   1);
    rb_define_method(rbSoundBuffer::Class, "load_from_samples", LoadFromSamples, -1);
    rb_define_method(rbSoundBuffer::Class, "save_to_file",      SaveToFile,       1);
    rb_define_method(rbSoundBuffer::Class, "samples",           GetSamples,       0);
    rb_define_method(rbSoundBuffer::Class, "samples_count",     GetSamplesCount,  0);
    rb_define_method(rbSoundBuffer::Class, "sample_rate",       GetSampleRate,    0);
    rb_define_method(rbSoundBuffer::Class, "channels_count",    GetChannelsCount, 0);
    rb_define_method(rbSoundBuffer::Class, "duration",          GetDuration,      0);
    rb_define_method(rbSoundBuffer::Class, "==",                Equal,            1);
    rb_define_method(rbSoundBuffer::Class, "inspect",           Inspect,          0);
    rb_define_method(rbSoundBuffer::Class, "memory_usage",      GetMemoryUsage,   0);

    // Instance aliasses
    rb_define_alias(rbSoundBuffer::Class, "LoadFromFile",     "load_from_file"   );
    rb_define_alias(rbSoundBuffer::Class, "load_file",        "load_from_file"   );
    rb_define_alias(rbSoundBuffer::Class, "load",             "load_from_file"   );
    rb_define_alias(rbSoundBuffer::Class, "LoadFromMemory",   "load_from_memory" );
    rb_define_alias(rbSoundBuffer::Class, "load_memory",      "load_from_memory" );
    rb_define_alias(rbSoundBuffer::Class, "LoadFromStream",   "load_from_stream" );
    rb_define_alias(rbSoundBuffer::Class, "load_stream",      "load_from_stream" );
    rb_define_alias(rbSoundBuffer::Class, "LoadFromSamples",  "load_from_samples");
    rb_define_alias(rbSoundBuffer::Class, "load_samples",     "load_from_samples");
    rb_define_alias(rbSoundBuffer::Class, "SaveToFile",       "save_to_file"     );
    rb_define_alias(rbSoundBuffer::Class, "save_file",        "save_to_file"     );
    rb_define_alias(rbSoundBuffer::Class, "save",             "save_to_file"     );
    rb_define_alias(rbSoundBuffer::Class, "GetSamples",       "samples"          );
    rb_define_alias(rbSoundBuffer::Class, "GetSamplesCount",  "samples_count"    );
    rb_define_alias(rbSoundBuffer::Class, "GetSampleRate",    "sample_rate"      );
    rb_define_alias(rbSoundBuffer::Class, "GetChannelsCount", "channels_count"   );
    rb_define_alias(rbSoundBuffer::Class, "channels",         "channels_count"   );
    rb_define_alias(rbSoundBuffer::Class, "GetDuration",      "duration"         );
    rb_define_alias(rbSoundBuffer::Class, "to_s",             "inspect"          );
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

    VALUE ptr[3];
    ptr[0] = rb_str_new((const char*)sound_buffer->GetSamples(),
                        sound_buffer->GetSamplesCount() * 2);
    ptr[1] = UINT2NUM(sound_buffer->GetChannelsCount());
    ptr[2] = UINT2NUM(sound_buffer->GetSampleRate());
    return rb_ary_new4(3, ptr);
}

// SoundBuffer#marshal_load
VALUE rbSoundBuffer::MarshalLoad(VALUE self, VALUE data)
{
    sf::SoundBuffer* sound_buffer = ToSFML(self);

    VALUE* ptr = RARRAY_PTR(data);
    const sf::Int16* samples    = (const sf::Int16*)RSTRING_PTR(ptr[0]);
    std::size_t samples_count   = RSTRING_LEN(ptr[0]) / 2;
    unsigned int channels_count = NUM2UINT(ptr[1]);
    unsigned int sample_rate    = NUM2UINT(ptr[2]);

    sound_buffer->LoadFromSamples(samples, samples_count, channels_count,
                                  sample_rate);
    return Qnil;
}

// SoundBuffer#load_from_file(filename)
// SoundBuffer#LoadFromFile(filename)
// SoundBuffer#load_file(filename)
// SoundBuffer#load(filename)
VALUE rbSoundBuffer::LoadFromFile(VALUE self, VALUE filename)
{
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->LoadFromFile(StringValueCStr(filename));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#load_from_memory(data)
// SoundBuffer#LoadFromMemory(data)
// SoundBuffer#load_memory(data)
VALUE rbSoundBuffer::LoadFromMemory(VALUE self, VALUE data)
{
    StringValue(data);
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->LoadFromMemory(RSTRING_PTR(data),
                                            RSTRING_LEN(data));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#load_from_stream(stream)
// SoundBuffer#LoadFromStream(stream)
// SoundBuffer#load_stream(stream)
VALUE rbSoundBuffer::LoadFromStream(VALUE self, VALUE stream)
{
    rbInputStream input_stream(stream);
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->LoadFromStream(input_stream);
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#load_from_samples(samples, channels_count, sample_rate)
// SoundBuffer#LoadFromSamples(samples, channels_count, sample_rate)
// SoundBuffer#load_samples(samples, channels_count, sample_rate)
// SoundBuffer#load_from_samples(samples, samples_count, channels_count, sample_rate)
// SoundBuffer#LoadFromSamples(samples, samples_count, channels_count, sample_rate)
// SoundBuffer#load_samples(samples, samples_count, channels_count, sample_rate)
VALUE rbSoundBuffer::LoadFromSamples(int argc, VALUE argv[], VALUE self)
{
    unsigned int channels_count;
    unsigned int sample_rate;
    switch (argc)
    {
        case 3:
            channels_count = NUM2UINT(argv[1]);
            sample_rate = NUM2UINT(argv[2]);
            break;
        case 4:
            channels_count = NUM2UINT(argv[2]);
            sample_rate = NUM2UINT(argv[3]);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 3..4)", argc);
    }
    VALUE samples_ary = rb_ary_to_ary(argv[0]);
    std::size_t samples_count = RARRAY_LEN(samples_ary);
    VALUE* samples_ptr = RARRAY_PTR(samples_ary);
    if (argc == 4 and samples_count != NUM2UINT(argv[1]))
    {
        rb_raise(rb_eArgError, "expected array size to be %d", samples_count);
    }
    sf::Int16* samples = new sf::Int16[samples_count];
    for (std::size_t i = 0; i < samples_count; ++i)
    {
        samples[i] = NUM2INT(samples_ptr[i]);
    }
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->LoadFromSamples(samples, samples_count,
                                             channels_count, sample_rate);
    delete[] samples;
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#save_to_file(filename)
// SoundBuffer#SaveToFile(filename)
// SoundBuffer#save_file(filename)
// SoundBuffer#save(filename)
VALUE rbSoundBuffer::SaveToFile(VALUE self, VALUE filename)
{
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->SaveToFile(StringValueCStr(filename));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// SoundBuffer#samples
// SoundBuffer#GetSamples
VALUE rbSoundBuffer::GetSamples(VALUE self)
{
    const sf::Int16* samples = ToSFML(self)->GetSamples();
    std::size_t samples_count = ToSFML(self)->GetSamplesCount();
    VALUE ary = rb_ary_new2(samples_count);
    for (std::size_t i = 0; i < samples_count; ++i)
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
// SoundBuffer#channels
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

// SoundBuffer#==(other)
VALUE rbSoundBuffer::Equal(VALUE self, VALUE other)
{
    if (!rb_obj_is_kind_of(other, SoundBuffer)) return Qfalse;
    sf::SoundBuffer* left = ToSFML(self);
    sf::SoundBuffer* right = ToSFML(other);

    if (left->GetSamplesCount() != right->GetSamplesCount()) return Qfalse;
    if (left->GetSampleRate() != right->GetSampleRate()) return Qfalse;
    if (left->GetChannelsCount() != right->GetChannelsCount()) return Qfalse;

    std::size_t samples_count = left->GetSamplesCount();
    const sf::Int16* left_samples = left->GetSamples();
    const sf::Int16* right_samples = right->GetSamples();
    for (std::size_t i = 0; i < samples_count; ++i)
    {
        if (left_samples[i] != right_samples[i]) return Qfalse;
    }

    return Qtrue;
}

// SoundBuffer#inspect
// SoundBuffer#to_s
VALUE rbSoundBuffer::Inspect(VALUE self)
{
    return rb_sprintf("%s(%p: %ims)",
                      rb_obj_classname(self),
                      (void*)self,
                      ToSFML(self)->GetDuration());
}

// SoundBuffer#memory_usage
VALUE rbSoundBuffer::GetMemoryUsage(VALUE self)
{
    std::size_t samples_count = ToSFML(self)->GetSamplesCount();
    return SIZET2NUM(sizeof(sf::SoundBuffer) + samples_count * 2);
}
