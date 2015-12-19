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

#ifndef RBSFML_RBVIEW_HPP_
#define RBSFML_RBVIEW_HPP_

#include <SFML/Graphics/View.hpp>
#include "class.hpp"
#include "object.hpp"

class rbView;
class rbTransform;

typedef rb::Class<rbView> rbViewClass;

class rbView : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbViewClass& getDefinition();

	rbView();
	~rbView();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbView* initializeCopy(const rbView* value);

	rb::Value marshalDump() const;
	void marshalLoad(const std::vector<rb::Value>& data);

	std::string inspect() const;

	void setCenter(sf::Vector2f center);
	const sf::Vector2f& getCenter() const;

	void setSize(sf::Vector2f size);
	const sf::Vector2f& getSize() const;

	void setRotation(float rotation);
	float getRotation() const;

	void reset(sf::FloatRect rect);
	const sf::FloatRect& getViewport() const;

	void move(sf::Vector2f offset);
	void rotate(float angle);
	void zoom(float factor);

	rbTransform* getTransform() const;
	rbTransform* getInverseTransform() const;

private:
    friend class rb::Value;
    friend class rbRenderTarget;

	static rbViewClass ourDefinition;

	sf::View myObject;
};

namespace rb
{
	template<>
	rbView* Value::to() const;
	template<>
	const rbView* Value::to() const;
	template<>
    sf::View& Value::to() const;
    template<>
    const sf::View& Value::to() const;
}

#endif // RBSFML_RBVIEW_HPP_
