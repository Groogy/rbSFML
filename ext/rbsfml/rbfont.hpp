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

#ifndef RBSFML_RBFONT_HPP_
#define RBSFML_RBFONT_HPP_

#include <SFML/Graphics/Font.hpp>
#include "class.hpp"
#include "object.hpp"

class rbFont;

typedef rb::Class<rbFont> rbFontClass;
typedef rb::Class<sf::Font::Info> rbFontInfoClass;
typedef rb::Class<sf::Glyph> rbGlyphClass;

class rbFont : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbFontClass& getDefinition();

	rbFont();
	~rbFont();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbFont* initializeCopy(const rbFont* value);

	rb::Value marshalDump() const;

	bool loadFromFile(const std::string& filename);
	bool loadFromMemory(std::vector<rb::Value> data);

	const sf::Font::Info& getInfo() const;
	const sf::Glyph& getGlyph(unsigned int codePoint, unsigned int characterSize, bool bold) const;
	float getKerning(unsigned int first, unsigned int second, unsigned int characterSize) const;
	float getLineSpacing(unsigned int characterSize) const;
	float getUnderlinePosition(unsigned int characterSize) const;
	float getUnderlineThickness(unsigned int characterSize) const;

	rb::Value getTexture(unsigned int characterSize) const;

private:
    friend class rb::Value;
	static rbFontClass ourDefinition;
	static rbFontInfoClass ourInfoDefinition;
	static rbGlyphClass ourGlyphDefinition;

	sf::Font myObject;
};

namespace rb
{
	template<>
	rbFont* Value::to() const;
	template<>
	const rbFont* Value::to() const;
	template<>
    sf::Font& Value::to() const;
    template<>
    const sf::Font& Value::to() const;

    template<>
    sf::Font::Info Value::to() const;
    template<>
    sf::Glyph Value::to() const;
    template<>
    Value Value::create(const sf::Font::Info& info);
    template<>
    Value Value::create(sf::Font::Info glyph);
    template<>
    Value Value::create(const sf::Glyph& glyph);
    template<>
    Value Value::create(sf::Glyph info);
}

#endif // RBSFML_RBFONT_HPP_
