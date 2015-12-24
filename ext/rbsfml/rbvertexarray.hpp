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

#ifndef RBSFML_RBVERTEXARRAY_HPP_
#define RBSFML_RBVERTEXARRAY_HPP_

#include "class.hpp"
#include "rbdrawable.hpp"

#include <SFML/Graphics/VertexArray.hpp>

class rbVertexArray;

typedef rb::Class<rbVertexArray> rbVertexArrayClass;

class rbVertexArray : public rbDrawableBaseType
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbVertexArrayClass& getDefinition();

	rbVertexArray();
	~rbVertexArray();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbVertexArray* initializeCopy(const rbVertexArray* value);

	rb::Value marshalDump() const;

	unsigned int getVertexCount() const;

	void setAtIndex(unsigned int index, sf::Vertex vertex);
	const sf::Vertex& getAtIndex(unsigned int index);

	void clear();
	void resize(unsigned int size);
	void append(sf::Vertex vertex);

	void setPrimitiveType(sf::PrimitiveType type);
	sf::PrimitiveType getPrimitiveType() const;

	sf::FloatRect getBounds() const;

protected:
    virtual sf::Drawable* getDrawable();
    virtual const sf::Drawable* getDrawable() const;

private:
    friend class rb::Value;
	static rbVertexArrayClass ourDefinition;

	sf::VertexArray myObject;
};

namespace rb
{
	template<>
	rbVertexArray* Value::to() const;
	template<>
	const rbVertexArray* Value::to() const;
	template<>
    sf::VertexArray& Value::to() const;
    template<>
    const sf::VertexArray& Value::to() const;
}

#endif // RBSFML_RBVERTEXARRAY_HPP_
