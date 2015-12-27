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
#include "error.hpp"

namespace rb
{

rb::Value TypeError(rb_eTypeError);
rb::Value RuntimeError(rb_eRuntimeError);
rb::Value ArgumentError(rb_eArgError);

void raise(const rb::Value& exception)
{
    rb_exc_raise(exception.to<VALUE>());
}

void expectedNumArgs(int argCount, int count)
{
	raise(ArgumentError, "wrong number of arguments(%i for %i)", argCount, count);
}

void expectedNumArgs(int argCount, int minCount, int maxCount)
{
	raise(ArgumentError, "wrong number of arguments(%i for %i...%i)", argCount, minCount, maxCount);
}

void expectedNumArgs(int argCount, const std::string& customText)
{
	raise(ArgumentError, "wrong number of arguments(%i for %s)", argCount, customText.c_str());
}

void modifiedFrozen(rb::Value object)
{
	raise(RuntimeError, "can't modify frozen %s", object.getClassName().c_str());
}

}
