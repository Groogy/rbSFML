/* rbSFML
 * Copyright (c) 2015 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#ifndef RBSFML_RBVECTOR2_HPP
#define RBSFML_RBVECTOR2_HPP

#include <SFML/System/Vector2.hpp>
#include "class.hpp"
#include "object.hpp"

class rbVector2;

typedef rb::Class<rbVector2> rbVector2Class;

class rbVector2
{
public:
	static void defineClass(const rb::Value& sfml);

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value initializeCopy(const rb::Value& self, const rb::Value& value);
	static rb::Value marshalDump(const rb::Value& self);
	static rb::Value marshalLoad(const rb::Value& self);

private:
	static rbVector2Class ourDefinition;
};

#endif // RBSFML_RBVECTOR2_HPP