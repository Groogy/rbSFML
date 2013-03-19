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

#ifndef WINDOW_CONTEXT_HPP
#define WINDOW_CONTEXT_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"
#include "ContextSettings.hpp"

#include <SFML/Window/Context.hpp>

namespace rbContext
{    
#if defined( WINDOW_CONTEXT_CPP )
    VALUE Class;
#else
    extern VALUE Context;
#endif
    
#if defined( RBSFML_WINDOW )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_CONTEXT_CPP )
    // Context#initialize
    // Context#initialize(settings, width, height)
    static VALUE Initialize( int argc, VALUE argv[], VALUE aSelf );
    
    // Context#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // Context#active=(active)
    // Context#setActive(active)
    static VALUE SetActive( VALUE aSelf, VALUE anActiveFlag );
#endif
    
}

#endif // WINDOW_CONTEXT_HPP
