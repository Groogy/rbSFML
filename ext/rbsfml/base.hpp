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

#ifndef RBSFML_BASE_HEADER_
#define RBSFML_BASE_HEADER_

#include <ruby.h>
#include "value.hpp"

namespace rb
{
	Value yield(const Value& value);
	Value getEnumerator(const Value& object);
	bool blockGiven();

	Value max(Value a, Value b);
	Value min(Value a, Value b);

	Value callSuper(const std::vector<Value>& args);

	Value eval(const std::string& script);
}

#endif // RBSFML_BASE_HEADER_