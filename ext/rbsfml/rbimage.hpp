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

#ifndef RBSFML_RBIMAGE_HPP_
#define RBSFML_RBIMAGE_HPP_

#include <SFML/Graphics/Image.hpp>
#include "class.hpp"
#include "object.hpp"

class rbImage;

typedef rb::Class<rbImage> rbImageClass;

class rbImage : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);

	rbImage();
	~rbImage();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbImage* initializeCopy(const rbImage* value);

	rb::Value marshalDump() const;
	void marshalLoad(const std::vector<rb::Value>& data);

	std::string inspect() const;

    void createFromColor(unsigned int width, unsigned int height, sf::Color color);
    void createFromData(unsigned int width, unsigned int height, const std::vector<rb::Value>& data);

	bool loadFromFile(const std::string& filename);
	bool loadFromMemory(const std::vector<rb::Value>& data);
	bool saveToFile(const std::string& filename) const;

	sf::Vector2u getSize() const;

	static rb::Value createMaskFromColor(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value copy(rb::Value self, const std::vector<rb::Value>& args);

	void setPixel(unsigned int x, unsigned int y, sf::Color color);
	sf::Color getPixel(unsigned int x, unsigned int y) const;
	rb::Value getPixels() const;

	void flipHorizontally();
	void flipVertically();

private:
    friend class rb::Value;
	static rbImageClass ourDefinition;

	sf::Image myObject;
};

namespace rb
{
	template<>
	rbImage* Value::to() const;
	template<>
	const rbImage* Value::to() const;
	template<>
    sf::Image& Value::to() const;
    template<>
    const sf::Image& Value::to() const;
}

#endif // RBSFML_RBIMAGE_HPP_
