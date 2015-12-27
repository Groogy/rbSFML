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

#ifndef RBSFML_RBDATAPTR_HPP_
#define RBSFML_RBDATAPTR_HPP_

#include "class.hpp"
#include "object.hpp"

class rbDataPtr;

typedef rb::Class<rbDataPtr> rbDataPtrClass;

class rbDataPtr : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbDataPtrClass& getDefinition();

	rbDataPtr();
	~rbDataPtr();

	std::string inspect() const;

    intptr_t getPtr() const;
    void setPtr(intptr_t ptr);

private:
    friend class rb::Value;

	static rbDataPtrClass ourDefinition;

	intptr_t myObject;
};

namespace rb
{
    template<>
    rbDataPtr* Value::to() const;
    template<>
    const rbDataPtr* Value::to() const;
}

#endif // RBSFML_RBDATAPTR_HPP_
