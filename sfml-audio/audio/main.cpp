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
 
#include "main.hpp"
#include "global.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "NonCopyable.hpp"

static bool CheckDependencies( void )
{
	if( rb_cvar_defined( globalSFMLNamespace, rb_intern( "SystemLoaded" ) ) == Qtrue )
	{
		return true;
	}

	return false;
}

void Init_audio( void )
{
	/* SFML namespace which contains the classes of this module. */
	globalSFMLNamespace = rb_define_module( "SFML" );
	if( CheckDependencies() == false )
	{
		rb_raise( rb_eRuntimeError, "This module depends on sfml-window" );
	}
	/*globalVector2Class = RetrieveSFMLClass( "Vector2" );
	globalVector3Class = RetrieveSFMLClass( "Vector3" );
	globalNonCopyableModule = RetrieveSFMLClass( "NonCopyable" );*/
	rb_define_const(globalSFMLNamespace, "AudioLoaded", Qtrue);
}
