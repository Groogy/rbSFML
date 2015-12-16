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

#include "rbtransform.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "error.hpp"
#include "macros.hpp"

rbTransformClass rbTransform::ourDefinition;

void rbTransform::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbTransformClass::defineClassUnder("Transform", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbTransform::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbTransform::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbTransform::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbTransform::marshalLoad);
	ourDefinition.defineMethod<4>("inspect", &rbTransform::inspect);
    ourDefinition.defineMethod<5>("to_ary", &rbTransform::getMatrix);
    ourDefinition.defineMethod<6>("inverse", &rbTransform::getInverse);
    ourDefinition.defineMethod<7>("transform_point", &rbTransform::transformPoint);
    ourDefinition.defineMethod<8>("transform_rect", &rbTransform::transformRect);
    ourDefinition.defineMethod<9>("combine", &rbTransform::combine);
    ourDefinition.defineMethod<10>("combine!", &rbTransform::combineBang);
    ourDefinition.defineMethod<11>("translate", &rbTransform::translate);
    ourDefinition.defineMethod<12>("translate!", &rbTransform::translateBang);
    ourDefinition.defineMethod<13>("rotate", &rbTransform::rotate);
    ourDefinition.defineMethod<14>("rotate!", &rbTransform::rotateBang);
    ourDefinition.defineMethod<15>("rotate_around", &rbTransform::rotateAround);
    ourDefinition.defineMethod<16>("rotate_around!", &rbTransform::rotateAroundBang);
    ourDefinition.defineMethod<17>("scale", &rbTransform::scale);
    ourDefinition.defineMethod<18>("scale!", &rbTransform::scaleBang);
    ourDefinition.defineMethod<19>("scale_around", &rbTransform::scaleAround);
    ourDefinition.defineMethod<20>("scale_around!", &rbTransform::scaleAroundBang);
    ourDefinition.defineMethod<21>("*", &rbTransform::multiply);

	ourDefinition.aliasMethod("inspect", "to_s");
	ourDefinition.aliasMethod("to_ary", "to_a");

    rb::Value identity = ourDefinition.newObject();
    identity.freeze();
	ourDefinition.defineConstant("Identity", identity);
}

rbTransformClass& rbTransform::getDefinition()
{
    return ourDefinition;
}

rbTransform::rbTransform()
: rb::Object()
, myObject()
{
}

rbTransform::~rbTransform()
{
}

rb::Value rbTransform::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	rbTransform* object = self.to<rbTransform*>();
	switch( args.size() )
    {
        case 0:
            break;
        case 1:
            if(args[0].getType() == rb::ValueType::Array)
            {
                const std::vector<rb::Value>& elements = args[0].to<const std::vector<rb::Value>&>();
                object->myObject = sf::Transform(
                    elements[0].to<float>(),elements[1].to<float>(),elements[2].to<float>(),
                    elements[3].to<float>(),elements[4].to<float>(),elements[5].to<float>(),
                    elements[6].to<float>(),elements[7].to<float>(),elements[8].to<float>()
                );
            }
            else
            {
                object->initializeCopy(args[0].to<const rbTransform*>());
            }
            break;
        case 9:
            object->myObject = sf::Transform(
                args[0].to<float>(),args[1].to<float>(),args[2].to<float>(),
                args[3].to<float>(),args[4].to<float>(),args[5].to<float>(),
                args[6].to<float>(),args[7].to<float>(),args[8].to<float>()
            );
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 1 or 9" );
        	break;
    }

	return self;
}

rbTransform* rbTransform::initializeCopy(const rbTransform* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbTransform::marshalDump() const
{
    std::vector<rb::Value> data;
    const float* elements = myObject.getMatrix();
    for(int index = 0, size = 4*4; index < size; index++)
    {
        data.push_back(rb::Value::create(elements[index]));
    }
	return rb::Value::create(data);
}

void rbTransform::marshalLoad(const std::vector<rb::Value>& data)
{
    myObject = sf::Transform(
        data[0].to<float>(),data[1].to<float>(),data[2].to<float>(),
        data[3].to<float>(),data[4].to<float>(),data[5].to<float>(),
        data[6].to<float>(),data[7].to<float>(),data[8].to<float>()
    );
}

std::string rbTransform::inspect() const
{
	const float* elements = myObject.getMatrix();
	std::string str = ourDefinition.getName() + "(";
	for(int x = 0; x < 3; x++)
	{
	    for(int y = 0; y < 3; y++)
	    {
	        if(x + y > 0)
	            str += ", ";
	        str += macro::toString(elements[y * 4 + x]);
	    }
	}
	return str + ")";
}

rb::Value rbTransform::getMatrix() const
{
    const float* elements = myObject.getMatrix();
    std::vector<rb::Value> data;
    for(int index = 0, size = 4*4; index < size; index++)
    {
        data.push_back(rb::Value::create(elements[index]));
    }
    return rb::Value::create(data);
}

rbTransform* rbTransform::getInverse() const
{
    rbTransform* inverse = ourDefinition.newObject().to<rbTransform*>();
    inverse->myObject = myObject.getInverse();
    return inverse;
}

sf::Vector2f rbTransform::transformPoint(sf::Vector2f point) const
{
    return myObject.transformPoint(point);
}

sf::FloatRect rbTransform::transformRect(sf::FloatRect rect) const
{
    return myObject.transformRect(rect);
}

rbTransform* rbTransform::combine(const sf::Transform& transform) const
{
    rbTransform* copy = ourDefinition.newObject(this).to<rbTransform*>();
    return copy->combineBang(transform);
}

rbTransform* rbTransform::combineBang(const sf::Transform& transform)
{
    myObject.combine(transform);
    return this;
}

rbTransform* rbTransform::translate(sf::Vector2f offset) const
{
    rbTransform* copy = ourDefinition.newObject(this).to<rbTransform*>();
    return copy->translateBang(offset);
}

rbTransform* rbTransform::translateBang(sf::Vector2f offset)
{
    myObject.translate(offset);
    return this;
}

rbTransform* rbTransform::rotate(float angle) const
{
    rbTransform* copy = ourDefinition.newObject(this).to<rbTransform*>();
    return copy->rotateBang(angle);
}

rbTransform* rbTransform::rotateBang(float angle)
{
    myObject.rotate(angle);
    return this;
}

rbTransform* rbTransform::rotateAround(float angle, sf::Vector2f center) const
{
    rbTransform* copy = ourDefinition.newObject(this).to<rbTransform*>();
    return copy->rotateAroundBang(angle, center);
}

rbTransform* rbTransform::rotateAroundBang(float angle, sf::Vector2f center)
{
    myObject.rotate(angle, center);
    return this;
}

rbTransform* rbTransform::scale(sf::Vector2f factors) const
{
    rbTransform* copy = ourDefinition.newObject(this).to<rbTransform*>();
    return copy->scaleBang(factors);
}

rbTransform* rbTransform::scaleBang(sf::Vector2f factors)
{
    myObject.scale(factors);
    return this;
}

rbTransform* rbTransform::scaleAround(sf::Vector2f factors, sf::Vector2f center) const
{
    rbTransform* copy = ourDefinition.newObject(this).to<rbTransform*>();
    return copy->scaleAroundBang(factors, center);
}

rbTransform* rbTransform::scaleAroundBang(sf::Vector2f factors, sf::Vector2f center)
{
    myObject.scale(factors, center);
    return this;
}

rb::Value rbTransform::multiply(const rb::Value& other) const
{
    if(other.isKindOf(rb::Value(ourDefinition)))
    {
        return rb::Value::create(combine(other.to<const sf::Transform&>()));
    }
    else
    {
        return rb::Value::create(transformPoint(other.to<sf::Vector2f>()));
    }
}

namespace rb
{

template<>
rbTransform* Value::to() const
{
	errorHandling(T_DATA);
	rbTransform* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbTransform, object);
	return object;
}

template<>
const rbTransform* Value::to() const
{
	errorHandling(T_DATA);
	const rbTransform* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbTransform, object);
	return object;
}

template<>
sf::Transform& Value::to() const
{
    return to<rbTransform*>()->myObject;
}

template<>
const sf::Transform& Value::to() const
{
    return to<const rbTransform*>()->myObject;
}

}