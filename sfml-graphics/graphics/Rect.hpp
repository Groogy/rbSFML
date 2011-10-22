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
 
#ifndef SFML_RUBYEXT_RECT_HEADER_
#define SFML_RUBYEXT_RECT_HEADER_

#include "ruby.h"
#include <SFML/Graphics/Rect.hpp>

VALUE Rect_ForceType( VALUE someValue );

VALUE Rect_GetLeft( VALUE self );
VALUE Rect_GetTop( VALUE self );
VALUE Rect_GetWidth( VALUE self );
VALUE Rect_GetHeight( VALUE self );

void Rect_SetLeft( VALUE self, VALUE aVal );
void Rect_SetTop( VALUE self, VALUE aVal );
void Rect_SetWidth( VALUE self, VALUE aVal );
void Rect_SetHeight( VALUE self, VALUE aVal );

int Rect_Type( VALUE aRect );
sf::IntRect Rect_ToSFMLi( VALUE aRect );
sf::FloatRect Rect_ToSFMLf( VALUE aRect );
VALUE Rect_ToRuby( const sf::IntRect &aRect );
VALUE Rect_ToRuby( const sf::FloatRect &aRect );

// Ruby initiation function
void Init_Rect( void );

#endif // SFML_RUBYEXT_RECT_HEADER_
