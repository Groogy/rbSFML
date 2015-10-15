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

#ifndef RBSFML_CLASS_HPP_
#define RBSFML_CLASS_HPP_

#include <ruby.h>
#include <string>
#include <array>

#include "module.hpp"
#include "object.hpp"

namespace rb
{
	template<typename Base>
	class DefaultAllocator
	{
	public:
		static Base* allocate();
		static VALUE allocate(VALUE klass);
		static void free(void* memory);
	};

	class RubyObjAllocator
	{
	public:
		static VALUE allocate(VALUE klass);
	};

	template<typename Base, int MaxFunctions = 32>
	class Class : public Module<Base, MaxFunctions>
	{
	public:
		static Module<Base, MaxFunctions> defineModule(const std::string& name) = delete;
		static Module<Base, MaxFunctions> defineModuleUnder(const std::string& name, const Value& otherModule) = delete;

		template<typename Allocator = DefaultAllocator<Base>>
		static Class defineClass(const std::string& name, const Value& parent = Value(rb_cObject));
		template<typename Allocator = DefaultAllocator<Base>>
		static Class defineClassUnder(const std::string& name, const Value& otherModule, const Value& parent = Value(rb_cObject));

		Class();

		Base* newObject();

	protected:
		static Value myParent;
	};
}

#include "class.inc"

#endif // RBSFML_CLASS_HPP_
