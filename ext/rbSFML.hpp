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

#ifndef RBSFML_HPP
#define RBSFML_HPP

#include <Ruby.hpp>
#include <new>

#define SFML_VERSION    "2.0"
#define BINDING_VERSION "development-unstable"

#define INVALID_EXPECTED_TYPE( type ) \
rb_raise( rb::eTypeError, "Did not receive expected type '%s'", rb_class2name( type ) );

#define INVALID_EXPECTED_TYPES( type1, type2 ) \
rb_raise( rb::eTypeError, "Did not receive expected types ( '%s', '%s' )", rb_class2name( type1 ), rb_class2name( type2 ) );

#define INVALID_ARGUMENT_LIST( count, argumentList ) \
rb_raise( rb::eArgError, "wrong number of arguments(%i for %s)", count, argumentList );

#endif // RBSFML_HPP
