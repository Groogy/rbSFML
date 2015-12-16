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

#ifndef RBSFML_RBTEXTURE_HPP_
#define RBSFML_RBTEXTURE_HPP_

#include <SFML/Graphics/Texture.hpp>
#include "class.hpp"
#include "object.hpp"

class rbTexture;

typedef rb::Class<rbTexture> rbTextureClass;

class rbTexture : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbTextureClass& getDefinition();

	rbTexture();
	~rbTexture();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbTexture* initializeCopy(const rbTexture* value);

	rb::Value marshalDump() const;

	std::string inspect() const;

    void create(unsigned int width, unsigned int height);
	static rb::Value loadFromFile(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value loadFromMemory(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value loadFromImage(rb::Value self, const std::vector<rb::Value>& args);

	sf::Vector2u getSize() const;

	rb::Value copyToImage() const;

	static rb::Value update(rb::Value self, const std::vector<rb::Value>& args);

	void setSmooth(bool smooth);
	bool isSmooth() const;

	void setRepeated(bool repeated);
	bool isRepeated() const;

	unsigned int getNativeHandle() const;

	static void bind(const rbTexture* texture, sf::Texture::CoordinateType type);
	static unsigned int getMaximumSize();

private:
    friend class rb::Value;
	static rbTextureClass ourDefinition;

	sf::Texture myObject;
};

namespace rb
{
	template<>
	rbTexture* Value::to() const;
	template<>
	const rbTexture* Value::to() const;
	template<>
    sf::Texture& Value::to() const;
    template<>
    const sf::Texture& Value::to() const;

    template<>
    sf::Texture::CoordinateType Value::to() const;
    template<>
    Value Value::create(sf::Texture::CoordinateType value);
}

#endif // RBSFML_RBTEXTURE_HPP_
