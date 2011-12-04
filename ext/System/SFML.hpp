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
#include <string>
#include <sstream>

#include <SFML/System/Err.hpp>

namespace rbSFML
{
    
    static inline VALUE Module();
    static inline void PrepareErrorStream();
    static inline void Raise(std::string message);
    static inline void Warn(std::string message);
    static inline void CheckRaise();
    static inline void CheckWarn();
    static inline std::string Message();
    
#if defined(RBSFML_SYSTEM)
    void Init(VALUE rbSFML);
#endif

#if defined(SYSTEM_SFML_CPP)
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

extern std::stringstream gErrorStream; // main.cpp

// Make sure there is no return keyword between the call to this function and
// the call to Raise() or Warn().
void rbSFML::PrepareErrorStream()
{
    VALUE SFML = Module();
    VALUE flag = rb_cv_get(SFML, "@@raise_exceptions");
    if (RTEST(flag))
        sf::Err().rdbuf(gErrorStream.rdbuf());
}

std::string rbSFML::Message()
{
    sf::Err().rdbuf(std::cerr.rdbuf());
    if (RTEST(rb_cv_get(Module(), "@@raise_exceptions")))
    {
        std::string message = gErrorStream.str();
        gErrorStream.str("");
        if (!message.empty())
            message.erase(message.end() - 1); // Remove '\n' from end.
        return message;
    }
    return "";
}

void rbSFML::Raise(std::string message)
{
    VALUE Error = rb_const_get(Module(), rb_intern("Error"));
    rb_raise(Error, message.c_str(), "");
}

void rbSFML::Warn(std::string message)
{
    rb_warn(message.c_str(), "");
}

void rbSFML::CheckRaise()
{
    std::string message = Message();
    if (!message.empty()) Raise(message);
}

void rbSFML::CheckWarn()
{
    std::string message = Message();
    if (!message.empty()) Warn(message);
}

#endif // SYSTEM_SFML_HPP
