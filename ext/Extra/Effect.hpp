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

#ifndef EXTRA_EFFECT_HPP
#define EXTRA_EFFECT_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

namespace rbEffect
{
#if defined( EXTRA_EFFECT_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_EXTRA )
    void Init( VALUE SFML );
#endif

#if defined( EXTRA_EFFECT_CPP )
  // Effect#initialize
  static VALUE Initialize( VALUE aSelf );
  
  // Effect#load_from_file(filename)
  static VALUE LoadFromFile( VALUE aSelf, VALUE aFilename );
  
  // Shader#set_parameter(name, x)
	// Shader#set_parameter(name, x, y)
	// Shader#set_parameter(name, x, y, z)
	// Shader#set_parameter(name, vector2)
	// Shader#set_parameter(name, vector3)
	// Shader#set_parameter(name, color)
	// Shader#set_parameter(name, transform)
	// Shader#set_parameter(name, texture)
	// Shader#set_parameter(name, current_texture)
	// Shader#setParameter(name, x)
	// Shader#setParameter(name, x, y)
	// Shader#setParameter(name, x, y, z)
	// Shader#setParameter(name, vector2)
	// Shader#setParameter(name, vector3)
	// Shader#setParameter(name, color)
	// Shader#setParameter(name, transform)
	// Shader#setParameter(name, texture)
	// Shader#setParameter(name, current_texture)
	// Shader#[]=(name, x)
	// Shader#[]=(name, vector2)
	// Shader#[]=(name, vector3)
	// Shader#[]=(name, color)
	// Shader#[]=(name, transform)
	// Shader#[]=(name, texture)
	// Shader#[]=(name, current_texture)
	static VALUE SetParameter( int argc, VALUE* args, VALUE aSelf );
#endif

}

#endif // EXTRA_EFFECT_HPP
