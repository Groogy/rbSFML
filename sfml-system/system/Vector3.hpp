/* rbSFML - Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 */
 
#ifndef SFML_RUBYEXT_VECTOR3_HEADER_
#define SFML_RUBYEXT_VECTOR3_HEADER_

#include "ruby.h"
#include "main.hpp"

VALUE Vector3_ForceType( VALUE someValue );

int Vector3_Type( VALUE aVector3 );
sf::Vector3i Vector3_ToSFMLi( VALUE aVector3 );
sf::Vector3f Vector3_ToSFMLf( VALUE aVector3 );
VALUE Vector3_ToRuby( const sf::Vector2i &aVector3 );
VALUE Vector3_ToRuby( const sf::Vector2f &aVector3 );

// Ruby initiation function
void Init_Vector3( void );

#endif // SFML_RUBYEXT_VECTOR2_HEADER_
