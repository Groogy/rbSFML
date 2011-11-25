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

#define SYSTEM_SFML_CPP
#include <System/SFML.hpp>

void rbSFML::Init(VALUE SFML)
{
    rb_define_class_under(SFML, "Error", rb_eRuntimeError);
    
    rb_define_const(SFML, "SFML_VERSION",    rb_str_new2(SFML_VERSION   ));
    rb_define_const(SFML, "BINDING_VERSION", rb_str_new2(BINDING_VERSION));
    
    SetRaiseExceptions(SFML, Qtrue);
    
    rb_define_module_function(SFML, "raise_exceptions",  GetRaiseExceptions, 0);
    rb_define_module_function(SFML, "raise_exceptions=", SetRaiseExceptions, 1);
    rb_define_module_function(SFML, "system?",           SystemLoaded,       0);
    rb_define_module_function(SFML, "window?",           WindowLoaded,       0);
    rb_define_module_function(SFML, "graphics?",         GraphicsLoaded,     0);
    rb_define_module_function(SFML, "audio?",            AudioLoaded,        0);
}

// SFML.raise_exceptions
VALUE rbSFML::GetRaiseExceptions(VALUE self)
{
    if (!rb_cvar_defined(self, rb_intern("@@raise_exceptions")))
        return Qfalse;
    return rb_cv_get(self, "@@raise_exceptions") ? Qtrue : Qfalse;
}

// SFML.raise_exceptions=(flag)
VALUE rbSFML::SetRaiseExceptions(VALUE self, VALUE flag)
{
    rb_cv_set(self, "@@raise_exceptions", flag);
}

// SFML.system?
VALUE rbSFML::SystemLoaded(VALUE self)
{
    return Qtrue; // You can't call this method without system.
}

// SFML.window?
VALUE rbSFML::WindowLoaded(VALUE self)
{
    static ID id_window = rb_intern("@@window");
    return rb_cvar_defined(self, id_window)
        ? Qtrue
        : Qfalse;
}

// SFML.graphics?
VALUE rbSFML::GraphicsLoaded(VALUE self)
{
    static ID id_graphics = rb_intern("@@graphics");
    return rb_cvar_defined(self, id_graphics)
        ? Qtrue
        : Qfalse;
}

// SFML.audio?
VALUE rbSFML::AudioLoaded(VALUE self)
{
    static ID id_audio = rb_intern("@@audio");
    return rb_cvar_defined(self, id_audio)
        ? Qtrue
        : Qfalse;
}
