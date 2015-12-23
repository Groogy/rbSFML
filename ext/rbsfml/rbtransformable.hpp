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

#ifndef RBSFML_RBTRANSFORMABLE_HPP_
#define RBSFML_RBTRANSFORMABLE_HPP_

#include <SFML/Graphics/RenderTarget.hpp>
#include "class.hpp"
#include "rbdrawablebasetype.hpp"

class rbTransformable;

typedef rb::Class<rbTransformable> rbTransformableClass;

class rbTransformable : public virtual rbDrawableBaseType
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbTransformableClass& getDefinition();

	rbTransformable();
	virtual ~rbTransformable();

	void setPosition(sf::Vector2f value);
	const sf::Vector2f& getPosition() const;

	void setRotation(float value);
	float getRotation() const;

	void setScale(sf::Vector2f value);
    const sf::Vector2f& getScale() const;

    void setOrigin(sf::Vector2f value);
    const sf::Vector2f& getOrigin() const;

    void move(sf::Vector2f value);
    void rotate(float value);
    void zoom(sf::Vector2f value);

    rb::Value getTransform() const;
    rb::Value getInverseTransform() const;

private:
    friend class rb::Value;
	static rbTransformableClass ourDefinition;
};

namespace rb
{
	template<>
	rbTransformable* Value::to() const;
	template<>
	const rbTransformable* Value::to() const;
}

#endif // RBSFML_RBTRANSFORMABLE_HPP_
