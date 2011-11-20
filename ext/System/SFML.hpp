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

#ifndef SYSTEM_SFML_HPP
#define SYSTEM_SFML_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <iostream>
#include <sstream>

#include <SFML/System/Err.hpp>

namespace rbSFML
{
    
    static inline VALUE Module();
    
#if defined(RBSFML_SYSTEM) || defined(RBSFML_SFML)
    
    void Init(VALUE rbSFML);
    
    // SFML.raise
    static VALUE Raise(VALUE self);
    
    // SFML.raise_exceptions
    static VALUE GetRaiseExceptions(VALUE self);
    
    // SFML.raise_exceptions=(flag)
    static VALUE SetRaiseExceptions(VALUE self, VALUE flag);
    
    // SFML.system?
    static VALUE SystemLoaded(VALUE self);
    
    // SFML.window?
    static VALUE WindowLoaded(VALUE self);
    
    // SFML.graphics?
    static VALUE GraphicsLoaded(VALUE self);
    
    // SFML.audio?
    static VALUE AudioLoaded(VALUE self);
    
#endif
    
};

VALUE rbSFML::Module()
{
    return rb_define_module("SFML");
}

#endif // SYSTEM_SFML_HPP
