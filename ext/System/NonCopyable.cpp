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

#define SYSTEM_NON_COPYABLE_CPP

#include "NonCopyable.hpp"

void rbNonCopyable::Init( VALUE SFML )
{
    rbNonCopyable::Module = rb_define_module_under( SFML, "NonCopyable" );

    // Instance methods
    ext_define_method( rbNonCopyable::Module, "initialize_copy", rbNonCopyable::InitializeCopy,  1 );
}

// NonCopyable#initialize_copy(source)
VALUE rbNonCopyable::InitializeCopy( VALUE aSelf, VALUE aSource )
{
    rb_raise( rb_eRuntimeError, "%s can not be copied!", rb_obj_classname( aSelf ) );

    return aSelf;
}
