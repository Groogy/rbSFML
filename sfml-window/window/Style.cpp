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
 
#include "Style.hpp"

static VALUE mSFML;
static VALUE cStyle;

void Init_Style( void )
{
	mSFML = rb_define_module( "SFML" );
	cStyle = rb_define_module_under( mSFML, "Style" );
	
	rb_define_const( cStyle, "None",       INT2FIX( sf::Style::None       ) );
	rb_define_const( cStyle, "Titlebar",   INT2FIX( sf::Style::Titlebar   ) );
	rb_define_const( cStyle, "Resize",     INT2FIX( sf::Style::Resize     ) );
	rb_define_const( cStyle, "Close",      INT2FIX( sf::Style::Close      ) );
	rb_define_const( cStyle, "Fullscreen", INT2FIX( sf::Style::Fullscreen ) );
	rb_define_const( cStyle, "Default",    INT2FIX( sf::Style::Default    ) );
}
