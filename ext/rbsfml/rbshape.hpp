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

#ifndef RBSFML_RBSHAPE_HPP_
#define RBSFML_RBSHAPE_HPP_

#include "class.hpp"
#include "rbdrawable.hpp"
#include "rbtransformable.hpp"

#include <SFML/Graphics/Shape.hpp>

class rbShape;

typedef rb::Class<rbShape> rbShapeClass;

class rbShape : public rbTransformable
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbShapeClass& getDefinition();

	rbShape();
	~rbShape();

	rb::Value marshalDump() const;

	static rb::Value setTexture(rb::Value self, const std::vector<rb::Value>& args);
	rb::Value getTexture() const;

	void setTextureRect(sf::IntRect rect);
	const sf::IntRect& getTextureRect() const;

	void setFillColor(sf::Color color);
	const sf::Color& getFillColor() const;
	void setOutlineColor(sf::Color color);
    const sf::Color& getOutlineColor() const;

    void setOutlineThickness(float thickness);
    float getOutlineThickness() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	unsigned int getPointCount() const;
	sf::Vector2f getPoint(unsigned int index);

protected:
    virtual sf::Drawable* getDrawable();
    virtual const sf::Drawable* getDrawable() const;

    virtual sf::Transformable* getTransformable();
    virtual const sf::Transformable* getTransformable() const;

    virtual sf::Shape& getShape() = 0;
    virtual const sf::Shape& getShape() const = 0;

private:
    friend class rb::Value;
	static rbShapeClass ourDefinition;
};

namespace rb
{
	template<>
	rbShape* Value::to() const;
	template<>
	const rbShape* Value::to() const;
	template<>
    sf::Shape& Value::to() const;
    template<>
    const sf::Shape& Value::to() const;
}

#endif // RBSFML_RBSHAPE_HPP_
