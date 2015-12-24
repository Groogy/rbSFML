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

#ifndef RBSFML_RBTEXT_HPP_
#define RBSFML_RBTEXT_HPP_

#include "class.hpp"
#include "rbdrawable.hpp"
#include "rbtransformable.hpp"

#include <SFML/Graphics/Text.hpp>

class rbText;

typedef rb::Class<rbText> rbTextClass;

class rbText : public rbTransformable
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbTextClass& getDefinition();

	rbText();
	~rbText();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbText* initializeCopy(const rbText* value);

	rb::Value marshalDump() const;

	void setColor(sf::Color color);
	const sf::Color& getColor() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

    void setString(const std::string& text);
    std::string getString() const;

    void setFont(rb::Value font);
    rb::Value getFont() const;

    void setCharacterSize(unsigned int size);
    unsigned int getCharacterSize() const;

    void setStyle(sf::Uint32 style);
    sf::Uint32 getStyle() const;

    sf::Vector2f findCharacterPos(unsigned int index) const;

protected:
    virtual sf::Drawable* getDrawable();
    virtual const sf::Drawable* getDrawable() const;

    virtual sf::Transformable* getTransformable();
    virtual const sf::Transformable* getTransformable() const;

private:
    friend class rb::Value;
	static rbTextClass ourDefinition;

	sf::Text myObject;
};

namespace rb
{
	template<>
	rbText* Value::to() const;
	template<>
	const rbText* Value::to() const;
	template<>
    sf::Text& Value::to() const;
    template<>
    const sf::Text& Value::to() const;

    template<>
    sf::Text::Style Value::to() const;
    template<>
    Value Value::create(sf::Text::Style style);
}

#endif // RBSFML_RBTEXT_HPP_
