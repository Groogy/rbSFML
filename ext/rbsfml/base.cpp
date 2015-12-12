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
#include "base.hpp"

namespace
{
	constexpr char symMore[] = ">";
	constexpr char symLess[] = "<";
}

namespace rb
{

rb::Value yield(const rb::Value& value)
{
	return rb::Value(rb_yield(value.to<VALUE>()));
}

rb::Value getEnumerator(const rb::Value& value)
{
	VALUE enumerator = SIZED_ENUMERATOR(value.to<VALUE>(), 0, nullptr, 0);
	return rb::Value(enumerator);
}

bool blockGiven()
{
	return rb_block_given_p();
}

rb::Value max(rb::Value a, rb::Value b)
{
	return a.call<symMore>(b) == rb::True ? a : b;
}

rb::Value min(rb::Value a, rb::Value b)
{
	return a.call<symLess>(b) == rb::True ? a : b;
}

}
