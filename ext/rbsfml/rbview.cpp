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

#include "rbview.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "rbtransform.hpp"
#include "error.hpp"
#include "macros.hpp"

rbViewClass rbView::ourDefinition;

void rbView::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbViewClass::defineClassUnder("View", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbView::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbView::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbView::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbView::marshalLoad);
	ourDefinition.defineMethod<4>("inspect", &rbView::inspect);
    ourDefinition.defineMethod<5>("center=", &rbView::setCenter);
    ourDefinition.defineMethod<6>("center", &rbView::getCenter);
    ourDefinition.defineMethod<7>("size=", &rbView::setSize);
    ourDefinition.defineMethod<8>("size", &rbView::getSize);
    ourDefinition.defineMethod<9>("rotation=", &rbView::setRotation);
    ourDefinition.defineMethod<10>("rotation", &rbView::getRotation);
    ourDefinition.defineMethod<11>("reset", &rbView::reset);
    ourDefinition.defineMethod<12>("viewport", &rbView::getViewport);
    ourDefinition.defineMethod<13>("move", &rbView::move);
    ourDefinition.defineMethod<14>("rotate", &rbView::rotate);
    ourDefinition.defineMethod<15>("zoom", &rbView::zoom);
    ourDefinition.defineMethod<16>("transform", &rbView::getTransform);
    ourDefinition.defineMethod<17>("inverse_transform", &rbView::getInverseTransform);

	ourDefinition.aliasMethod("inspect", "to_s");
}

rbView::rbView()
: rb::Object()
, myObject()
{
}

rbView::~rbView()
{
}

rb::Value rbView::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	rbView* object = self.to<rbView*>();
	switch( args.size() )
    {
        case 0:
            break;
        case 1:
            object->myObject = sf::View(args[0].to<sf::FloatRect>());
            break;
        case 2:
            object->myObject = sf::View(args[0].to<sf::Vector2f>(), args[1].to<sf::Vector2f>());
            break;
        default:
        	rb::expectedNumArgs( args.size(), 0, 2 );
        	break;
    }

	return self;
}

rbView* rbView::initializeCopy(const rbView* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbView::marshalDump() const
{
    std::vector<rb::Value> data;
    data.push_back(rb::Value::create(myObject.getViewport()));
	return rb::Value::create(data);
}

void rbView::marshalLoad(const std::vector<rb::Value>& data)
{
    myObject.reset(data[0].to<sf::FloatRect>());
}

std::string rbView::inspect() const
{
	sf::Vector2f center = myObject.getCenter();
    sf::Vector2f size = myObject.getSize();

    return ourDefinition.getName() + "(" + macro::toString(center.x) + ", " + macro::toString(center.y) + ", " 
                                         + macro::toString(size.x) + ", " + macro::toString(size.y) + ")";
}

void rbView::setCenter(sf::Vector2f center)
{
    myObject.setCenter(center);
}

const sf::Vector2f& rbView::getCenter() const
{
    return myObject.getCenter();
}

void rbView::setSize(sf::Vector2f size)
{
    myObject.setSize(size);
}

const sf::Vector2f& rbView::getSize() const
{
    return myObject.getSize();
}

void rbView::setRotation(float rotation)
{
    myObject.setRotation(rotation);
}

float rbView::getRotation() const
{
    return myObject.getRotation();
}

void rbView::reset(sf::FloatRect rect)
{
    myObject.reset(rect);
}

const sf::FloatRect& rbView::getViewport() const
{
    return myObject.getViewport();
}

void rbView::move(sf::Vector2f offset)
{
    myObject.move(offset);
}

void rbView::rotate(float angle)
{
    myObject.rotate(angle);
}

void rbView::zoom(float factor)
{
    myObject.zoom(factor);
}

rbTransform* rbView::getTransform() const
{
    rbTransform* transform = rbTransform::getDefinition().newObject().to<rbTransform*>();
    transform->myObject = myObject.getTransform();
    return transform;
}

rbTransform* rbView::getInverseTransform() const
{
    rbTransform* transform = rbTransform::getDefinition().newObject().to<rbTransform*>();
    transform->myObject = myObject.getInverseTransform();
    return transform;
}

namespace rb
{

template<>
rbView* Value::to() const
{
	errorHandling(T_DATA);
	rbView* object = nullptr;
	Data_Get_Struct(myValue, rbView, object);
	return object;
}

template<>
const rbView* Value::to() const
{
	errorHandling(T_DATA);
	const rbView* object = nullptr;
	Data_Get_Struct(myValue, rbView, object);
	return object;
}

template<>
sf::View& Value::to() const
{
    return to<rbView*>()->myObject;
}

template<>
const sf::View& Value::to() const
{
    return to<const rbView*>()->myObject;
}

}