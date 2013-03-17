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

#ifndef SYSTEM_NONCOPYABLE_HPP
#define SYSTEM_NONCOPYABLE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "SFML.hpp"

#include <SFML/System/NonCopyable.hpp>

namespace rbNonCopyable
{
#if defined( SYSTEM_NON_COPYABLE_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif

#if defined( RBSFML_SYSTEM )
    void Init( VALUE SFML );
#endif

#if defined( SYSTEM_NON_COPYABLE_CPP )

    // NonCopyable#initialize_copy( source )
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );

#endif

}

#endif // SYSTEM_NONCOPYABLE_HPP

