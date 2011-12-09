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

#include <Audio.hpp>

#if !defined(RBSFML_SFML)
#include <sstream>
std::stringstream gErrorStream;
namespace rbVector3 { VALUE Vector3; }
#endif

static inline void InitDependencies(VALUE SFML)
{
#if !defined(RBSFML_SFML)
    rbVector3::Vector3 = rb_const_get(SFML, rb_intern("Vector3"));
#endif
}

extern "C"
void Init_audio()
{
    VALUE SFML = rbSFML::Module();
    
    if (!rb_cvar_defined(SFML, rb_intern("@@system")))
        rb_require("sfml/system");
    
    rb_cv_set(SFML, "@@audio", Qtrue);
    
    InitDependencies(SFML);
    
    rbSoundSource::Init(SFML);
    rbSound::Init(SFML);
    rbSoundBuffer::Init(SFML);
    rbSoundStream::Init(SFML);
    rbMusic::Init(SFML);
}
