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

#ifndef RBSFML_RBTRANSFORM_HPP_
#define RBSFML_RBTRANSFORM_HPP_

#include <SFML/Graphics/Transform.hpp>
#include "class.hpp"
#include "object.hpp"

class rbTransform;

typedef rb::Class<rbTransform> rbTransformClass;

class rbTransform : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbTransformClass& getDefinition();

	rbTransform();
	~rbTransform();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbTransform* initializeCopy(const rbTransform* value);

	rb::Value marshalDump() const;
	void marshalLoad(const std::vector<rb::Value>& data);

	std::string inspect() const;

	rb::Value getMatrix() const;
	rbTransform* getInverse() const;

	sf::Vector2f transformPoint(sf::Vector2f point) const;
	sf::FloatRect transformRect(sf::FloatRect rect) const;

	rbTransform* combine(const sf::Transform& transform) const;
	rbTransform* combineBang(const sf::Transform& transform);

	rbTransform* translate(sf::Vector2f offset) const;
    rbTransform* translateBang(sf::Vector2f offset);

    rbTransform* rotate(float angle) const;
    rbTransform* rotateBang(float angle);
    rbTransform* rotateAround(float angle, sf::Vector2f center) const;
    rbTransform* rotateAroundBang(float angle, sf::Vector2f center);

    rbTransform* scale(sf::Vector2f factors) const;
    rbTransform* scaleBang(sf::Vector2f factors);
    rbTransform* scaleAround(sf::Vector2f factors, sf::Vector2f center) const;
    rbTransform* scaleAroundBang(sf::Vector2f factors, sf::Vector2f center);

    rb::Value multiply(const rb::Value& other) const;

private:
    friend class rb::Value;
    friend class rbView;
    
	static rbTransformClass ourDefinition;

	sf::Transform myObject;
};

namespace rb
{
	template<>
	rbTransform* Value::to() const;
	template<>
	const rbTransform* Value::to() const;
	template<>
    sf::Transform& Value::to() const;
    template<>
    const sf::Transform& Value::to() const;
}

#endif // RBSFML_RBTRANSFORM_HPP_
