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

#ifndef RBSFML_RBNONCOPYABLE_HPP
#define RBSFML_RBNONCOPYABLE_HPP

#include <SFML/System/NonCopyable.hpp>
#include "class.hpp"
#include "object.hpp"

class rbNonCopyable;

typedef rb::Module<rbNonCopyable> rbNonCopyableModule;

class rbNonCopyable
{
public:
	static void defineModule(const rb::Value& sfml);
	static rbNonCopyableModule getDefinition();

	static const rb::Value& initializeCopy(const rb::Value& self, const rb::Value& value);
	static const rb::Value& marshalDump(const rb::Value& self);

private:
	static rbNonCopyableModule ourDefinition;
};

#endif // RBSFML_RBNONCOPYABLE_HPP