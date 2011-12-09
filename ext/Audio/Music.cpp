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

#define AUDIO_MUSIC_CPP
#include "Music.hpp"

void rbMusic::Init(VALUE SFML)
{
    Music = rb_define_class_under(SFML, "Music", rbSoundStream::SoundStream);
    
    // Class methods
    rb_define_alloc_func(Music, Allocate);
    
    // Instance methods
    rb_define_method(Music, "marshal_dump",      MarshalDump,      0);
    rb_define_method(Music, "clone",             Clone,            0);
    rb_define_method(Music, "dup",               Dup,              0);
    rb_define_method(Music, "open_from_file",    OpenFromFile,     1);
    rb_define_method(Music, "open_from_memory",  OpenFromMemory,   1);
    rb_define_method(Music, "open_from_stream",  OpenFromStream,   1);
    rb_define_method(Music, "duration",          GetDuration,      0);
    rb_define_method(Music, "inspect",           Inspect,          0);
    rb_define_method(Music, "memory_usage",      GetMemoryUsage,   0);
    
    // Instance aliasses
    rb_define_alias(Music, "OpenFromFile",     "open_from_file"   );
    rb_define_alias(Music, "open_file",        "open_from_file"   );
    rb_define_alias(Music, "open",             "open_from_file"   );
    rb_define_alias(Music, "OpenFromMemory",   "open_from_memory" );
    rb_define_alias(Music, "open_memory",      "open_from_memory" );
    rb_define_alias(Music, "OpenFromStream",   "open_from_stream" );
    rb_define_alias(Music, "open_stream",      "open_from_stream" );
    rb_define_alias(Music, "GetDuration",      "duration"         );
    rb_define_alias(Music, "to_s",             "inspect"          );
}

// Music#marshal_dump
VALUE rbMusic::MarshalDump(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dump %s", rb_obj_classname(self));
    return Qnil;
}

// Music#clone
VALUE rbMusic::Clone(VALUE self)
{
    rb_raise(rb_eTypeError, "can't clone instance of %s",
             rb_obj_classname(self));
    return Qnil;
}

// Music#dup
VALUE rbMusic::Dup(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dup instance of %s",
             rb_obj_classname(self));
    return Qnil;
}

// Music#open_from_file(filename)
// Music#OpenFromFile(filename)
// Music#open_file(filename)
// Music#open(filename)
VALUE rbMusic::OpenFromFile(VALUE self, VALUE filename)
{
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->OpenFromFile(StringValueCStr(filename));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// Music#open_from_memory(data)
// Music#OpenFromMemory(data)
// Music#open_memory(data)
VALUE rbMusic::OpenFromMemory(VALUE self, VALUE data)
{
    StringValue(data);
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->OpenFromMemory(RSTRING_PTR(data),
                                            RSTRING_LEN(data));
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// Music#open_from_stream(stream)
// Music#OpenFromStream(stream)
// Music#open_stream(stream)
VALUE rbMusic::OpenFromStream(VALUE self, VALUE stream)
{
    rbInputStream input_stream(stream);
    rbSFML::PrepareErrorStream();
    bool ret = ToSFML(self)->OpenFromStream(input_stream);
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// Music#duration
// Music#GetDuration
VALUE rbMusic::GetDuration(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetDuration());
}

// Music#inspect
// Music#to_s
VALUE rbMusic::Inspect(VALUE self)
{
    return rb_sprintf("%s(%p: %ims)",
                      rb_obj_classname(self),
                      (void*)self,
                      ToSFML(self)->GetDuration());
}

// Music#memory_usage
VALUE rbMusic::GetMemoryUsage(VALUE self)
{
    return SIZET2NUM(sizeof(sf::Music));
}
