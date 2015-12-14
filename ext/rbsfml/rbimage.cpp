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

#include "rbimage.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "error.hpp"
#include "macros.hpp"

rbImageClass rbImage::ourDefinition;

void rbImage::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbImageClass::defineClassUnder("Image", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbImage::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbImage::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbImage::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbImage::marshalLoad);
	ourDefinition.defineMethod<4>("inspect", &rbImage::inspect);
    ourDefinition.defineMethod<5>("load_from_file", &rbImage::loadFromFile);
    ourDefinition.defineMethod<6>("load_from_memory", &rbImage::loadFromMemory);

	ourDefinition.aliasMethod("inspect", "to_s");
}

rbImage::rbImage()
: rb::Object()
, myObject()
{
}

rbImage::~rbImage()
{
}

rb::Value rbImage::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	rbImage* object = self.to<rbImage*>();
	switch( args.size() )
    {
        case 0:
            break;
        case 1:
            if(args[0].getType() == rb::ValueType::Array)
                object->loadFromMemory(args[0].to<std::vector<rb::Value>>());
            else
                object->loadFromFile(args[0].to<std::string>());
            break;
        default:
        	rb::expectedNumArgs( args.size(), 0, 2 );
        	break;
    }

	return self;
}

rbImage* rbImage::initializeCopy(const rbImage* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbImage::marshalDump() const
{
    std::vector<rb::Value> data;
    //data.push_back(rb::Value::create(myObject.getViewport()));
	return rb::Value::create(data);
}

void rbImage::marshalLoad(const std::vector<rb::Value>& data)
{
    //myObject.reset(data[0].to<sf::FloatRect>());
}

std::string rbImage::inspect() const
{
    sf::Vector2u size = myObject.getSize();

    return ourDefinition.getName() + "(" + macro::toString(size.x) + ", " + macro::toString(size.y) + ")";
}

bool rbImage::loadFromFile(const std::string& filename)
{
    return myObject.loadFromFile(filename);
}

bool rbImage::loadFromMemory(const std::vector<rb::Value>& data)
{
    sf::Uint8* rawData = new sf::Uint8[data.size()];
    for(int index = 0, size = data.size(); index < size; index++)
    {
        rawData[index] = data[index].to<sf::Uint8>();
    }
    return myObject.loadFromMemory(rawData, data.size());
}

namespace rb
{

template<>
rbImage* Value::to() const
{
	errorHandling(T_DATA);
	rbImage* object = nullptr;
	Data_Get_Struct(myValue, rbImage, object);
	return object;
}

template<>
const rbImage* Value::to() const
{
	errorHandling(T_DATA);
	const rbImage* object = nullptr;
	Data_Get_Struct(myValue, rbImage, object);
	return object;
}

template<>
sf::Image& Value::to() const
{
    return to<rbImage*>()->myObject;
}

template<>
const sf::Image& Value::to() const
{
    return to<const rbImage*>()->myObject;
}

}