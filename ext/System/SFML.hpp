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

#include "../rbSFML.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <SFML/System/Err.hpp>

namespace rbSFML
{

    static inline VALUE Module();
    static inline void PrepareErrorStream();
    static inline void Raise( const std::string &aMessage );
    static inline void Warn( const std::string &aMessage);
    static inline void CheckRaise();
    static inline void CheckWarn();
    static inline std::string Message();

#if defined(RBSFML_SYSTEM)
    void Init(VALUE rbSFML);
#endif

#if defined(SYSTEM_SFML_CPP)
    // SFML.raise_exceptions
    static VALUE GetRaiseExceptions( VALUE aSelf );

    // SFML.raise_exceptions=(flag)
    static VALUE SetRaiseExceptions( VALUE aSelf, VALUE aFlag );

    // SFML.system?
    static VALUE SystemLoaded( VALUE aSelf );

    // SFML.window?
    static VALUE WindowLoaded( VALUE aSelf );

    // SFML.graphics?
    static VALUE GraphicsLoaded( VALUE aSelf );

    // SFML.audio?
    static VALUE AudioLoaded( VALUE aSelf );
    
#endif

};

VALUE rbSFML::Module()
{
    return rb_define_module( "SFML" );
}

extern std::stringstream globalErrorStream; // main.cpp

// Make sure there is no return keyword between the call to this function and
// the call to Raise() or Warn().
void rbSFML::PrepareErrorStream()
{
    VALUE SFML = Module();
    VALUE flag = rb_cv_get(SFML, "@@raise_exceptions");
    if( RTEST( flag ) )
        sf::err().rdbuf( globalErrorStream.rdbuf() );
}

std::string rbSFML::Message()
{
    sf::err().rdbuf( std::cerr.rdbuf() );
    if( RTEST( rb_cv_get( Module(), "@@raise_exceptions" ) ) )
    {
        std::string message = globalErrorStream.str();
        globalErrorStream.str( "" );
        if( !message.empty() )
            message.erase( message.end() - 1 ); // Remove '\n' from end.
        return message;
    }
    return "";
}

void rbSFML::Raise( const std::string &aMessage )
{
    VALUE error = rb_const_get( Module(), rb_intern( "Error" ) );
    rb_raise( error, aMessage.c_str(), "" );
}

void rbSFML::Warn( const std::string &aMessage )
{
    rb_warn( aMessage.c_str(), "" );
}

void rbSFML::CheckRaise()
{
    std::string message = Message();
    if( !message.empty() ) Raise( message );
}

void rbSFML::CheckWarn()
{
    std::string message = Message();
    if( !message.empty() ) Warn( message );
}

#endif // SYSTEM_SFML_HPP
