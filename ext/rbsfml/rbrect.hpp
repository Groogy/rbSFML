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

#ifndef RBSFML_RBRECT_HPP
#define RBSFML_RBRECT_HPP

#include <SFML/Graphics/Rect.hpp>
#include "class.hpp"
#include "object.hpp"

class rbRect;

typedef rb::Class<rbRect> rbRectClass;

class rbRect
{
public:
	static void defineClass(const rb::Value& sfml);
	static const rbRectClass& getDefinition();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value initializeCopy(rb::Value self, const rb::Value& value);
	static std::vector<rb::Value> marshalDump(const rb::Value& self);
	static rb::Value marshalLoad(rb::Value self, const rb::Value& data);

	static rb::Value contains(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value intersects(const rb::Value& self, const rb::Value& other);

	static bool equal(const rb::Value& self, const rb::Value& other);
	static bool strictEqual(const rb::Value& self, const rb::Value& other);

	static std::string inspect(const rb::Value& self);

private:
	static rbRectClass ourDefinition;
};

namespace rb
{
	template<>
	sf::FloatRect Value::to() const;
	template<>
	sf::IntRect Value::to() const;

	template<>
	Value Value::create<sf::FloatRect>( sf::FloatRect value );
	template<>
	Value Value::create<const sf::FloatRect&>( const sf::FloatRect& value );
	template<>
	Value Value::create<sf::IntRect>( sf::IntRect value );
	template<>
	Value Value::create<const sf::IntRect&>( const sf::IntRect& value );
}

#endif // RBSFML_RBRECT_HPP