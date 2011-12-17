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

#define AUDIO_SOUNDBUFFERRECORDER_CPP
#include "SoundBufferRecorder.hpp"

void rbSoundBufferRecorder::Init(VALUE SFML)
{
    SoundBufferRecorder = rb_define_class_under(SFML, "SoundBufferRecorder", rbSoundRecorder::SoundRecorder);
    
    // Class methods
    rb_define_alloc_func(SoundBufferRecorder, Allocate);
    
    // Instance methods
    rb_define_method(SoundBufferRecorder, "buffer",       GetBuffer,      0);
    rb_define_method(SoundBufferRecorder, "memory_usage", GetMemoryUsage, 0);
    
    // Instance aliasses
    rb_define_alias(SoundBufferRecorder, "GetBuffer", "buffer");
}

// SoundBufferRecorder#buffer
// SoundBufferRecorder#GetBuffer
VALUE rbSoundBufferRecorder::GetBuffer(VALUE self)
{
    sf::SoundBuffer* buffer = const_cast<sf::SoundBuffer*>(&ToSFML(self)->GetBuffer());
    return rb_data_object_alloc(rbSoundBuffer::SoundBuffer, buffer, NULL, NULL);
}

// SoundBufferRecorder#memory_usage
VALUE rbSoundBufferRecorder::GetMemoryUsage(VALUE self)
{
    return SIZET2NUM(sizeof(sf::SoundBufferRecorder));
}
