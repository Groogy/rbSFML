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

#include "rbtransformable.hpp"
#include "rbvector2.hpp"
#include "rbtransform.hpp"
#include "error.hpp"
#include "macros.hpp"

#include <SFML/Graphics/Transformable.hpp>

rbTransformableModule rbTransformable::ourDefinition;

class rbTransformableImpl : public rbTransformable, sf::Transformable
{
public:
protected:
    sf::Transformable* getTransformable() { return this; }
    const sf::Transformable* getTransformable() const { return this; }
};

void rbTransformable::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbTransformableModule::defineModuleUnder("Transformable", sfml);
	ourDefinition.defineMethod<1>("position=", &rbTransformable::setPosition);
	ourDefinition.defineMethod<2>("position", &rbTransformable::getPosition);
	ourDefinition.defineMethod<3>("rotation=", &rbTransformable::setRotation);
    ourDefinition.defineMethod<4>("rotation", &rbTransformable::getRotation);
    ourDefinition.defineMethod<5>("scale=", &rbTransformable::setScale);
    ourDefinition.defineMethod<6>("scale", &rbTransformable::getScale);
    ourDefinition.defineMethod<7>("origin=", &rbTransformable::setOrigin);
    ourDefinition.defineMethod<8>("origin", &rbTransformable::getOrigin);
    ourDefinition.defineMethod<9>("move", &rbTransformable::move);
    ourDefinition.defineMethod<10>("rotate", &rbTransformable::rotate);
    ourDefinition.defineMethod<11>("zoom", &rbTransformable::zoom);
    ourDefinition.defineMethod<12>("transform", &rbTransformable::getTransform);
    ourDefinition.defineMethod<13>("inverse_transform", &rbTransformable::getInverseTransform);
}

void rbTransformable::defineIncludeFunction()
{
    ourDefinition.defineFunction<0>("included", &rbTransformable::included);
}

rbTransformableModule& rbTransformable::getDefinition()
{
    return ourDefinition;
}

void rbTransformable::included(const rb::Value& base)
{
    if(base.getType() == rb::ValueType::Class)
    {
        rb::defineAllocator<rb::DefaultAllocator<rbTransformableImpl>>(base);
    }
}

void rbTransformable::setPosition(sf::Vector2f value)
{
    getTransformable()->setPosition(value);
}

const sf::Vector2f& rbTransformable::getPosition() const
{
    return getTransformable()->getPosition();
}

void rbTransformable::setRotation(float value)
{
    getTransformable()->setRotation(value);
}

float rbTransformable::getRotation() const
{
    return getTransformable()->getRotation();
}

void rbTransformable::setScale(sf::Vector2f value)
{
    getTransformable()->setScale(value);
}

const sf::Vector2f& rbTransformable::getScale() const
{
    return getTransformable()->getScale();
}

void rbTransformable::setOrigin(sf::Vector2f value)
{
    getTransformable()->setOrigin(value);
}

const sf::Vector2f& rbTransformable::getOrigin() const
{
    return getTransformable()->getOrigin();
}

void rbTransformable::move(sf::Vector2f value)
{
    getTransformable()->move(value);
}

void rbTransformable::rotate(float value)
{
    getTransformable()->rotate(value);
}

void rbTransformable::zoom(sf::Vector2f value)
{
    getTransformable()->scale(value);
}

rb::Value rbTransformable::getTransform() const
{
    rb::Value object = rbTransform::getDefinition().newObject();
    object.to<sf::Transform&>() = getTransformable()->getTransform();
    return object;
}

rb::Value rbTransformable::getInverseTransform() const
{
    rb::Value object = rbTransform::getDefinition().newObject();
    object.to<sf::Transform&>() = getTransformable()->getInverseTransform();
    return object;
}
