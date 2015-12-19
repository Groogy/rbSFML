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

#ifndef RBSFML_RBVERTEX_HPP
#define RBSFML_RBVERTEX_HPP

#include <SFML/Graphics/Vertex.hpp>
#include "class.hpp"
#include "object.hpp"

class rbVertex;

typedef rb::Class<rbVertex> rbVertexClass;

class rbVertex
{
public:
	static void defineClass(const rb::Value& sfml);
	static const rbVertexClass& getDefinition();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value marshalDump(const rb::Value& self);
	static void marshalLoad(rb::Value self, const std::vector<rb::Value>& data);

private:
	static rbVertexClass ourDefinition;
};

namespace rb
{
	template<>
	sf::Vertex Value::to() const;
}

#endif // RBSFML_RBVERTEX_HPP