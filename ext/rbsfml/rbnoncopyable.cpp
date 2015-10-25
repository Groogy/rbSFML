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

#include "rbnoncopyable.hpp"
#include "error.hpp"
#include "macros.hpp"

rbNonCopyableModule rbNonCopyable::ourDefinition;

void rbNonCopyable::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbNonCopyableModule::defineModuleUnder("NonCopyable", sfml);
	ourDefinition.defineMethod<0>("initialize_copy", &rbNonCopyable::initializeCopy);
	ourDefinition.defineMethod<1>("marshal_dump", &rbNonCopyable::marshalDump);
}

rbNonCopyableModule rbNonCopyable::getDefinition()
{
	return ourDefinition;
}

const rb::Value& rbNonCopyable::initializeCopy(const rb::Value& self, const rb::Value& value)
{
	std::string type = self.getClassName();
	rb::raise(rb::RuntimeError, "%s can not be copied!", type.c_str());
	return rb::Nil;
}

const rb::Value& rbNonCopyable::marshalDump(const rb::Value& self)
{
	std::string type = self.getClassName();
	rb::raise(rb::TypeError, "can't dump %s", type.c_str());
	return rb::Nil;
}
