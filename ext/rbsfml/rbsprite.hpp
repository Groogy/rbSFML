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

#ifndef RBSFML_RBSPRITE_HPP_
#define RBSFML_RBSPRITE_HPP_

#include "class.hpp"
#include "rbdrawable.hpp"
#include "rbtransformable.hpp"

#include <SFML/Graphics/Sprite.hpp>

class rbSprite;

typedef rb::Class<rbSprite> rbSpriteClass;

class rbSprite : public rbTransformable
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbSpriteClass& getDefinition();

	rbSprite();
	~rbSprite();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbSprite* initializeCopy(const rbSprite* value);

	rb::Value marshalDump() const;

	static rb::Value setTexture(rb::Value self, const std::vector<rb::Value>& args);
	rb::Value getTexture() const;

	void setTextureRect(sf::IntRect rect);
	const sf::IntRect& getTextureRect() const;

	void setColor(sf::Color color);
	const sf::Color& getColor() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

protected:
    virtual sf::Drawable* getDrawable();
    virtual const sf::Drawable* getDrawable() const;

    virtual sf::Transformable* getTransformable();
    virtual const sf::Transformable* getTransformable() const;

private:
    friend class rb::Value;
	static rbSpriteClass ourDefinition;

	sf::Sprite myObject;
};

namespace rb
{
	template<>
	rbSprite* Value::to() const;
	template<>
	const rbSprite* Value::to() const;
	template<>
    sf::Sprite& Value::to() const;
    template<>
    const sf::Sprite& Value::to() const;
}

#endif // RBSFML_RBSPRITE_HPP_
