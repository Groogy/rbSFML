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
#include "rbcolor.hpp"
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
	ourDefinition.defineMethod<5>("create_from_color", &rbImage::createFromColor);
	ourDefinition.defineMethod<6>("create_from_data", &rbImage::createFromData);
    ourDefinition.defineMethod<7>("load_from_file", &rbImage::loadFromFile);
    ourDefinition.defineMethod<8>("load_from_memory", &rbImage::loadFromMemory);
    ourDefinition.defineMethod<9>("save_to_file", &rbImage::saveToFile);
    ourDefinition.defineMethod<10>("size", &rbImage::getSize);
    ourDefinition.defineMethod<11>("create_mask_from_color", &rbImage::createMaskFromColor);
    ourDefinition.defineMethod<12>("copy", &rbImage::copy);
    ourDefinition.defineMethod<13>("set_pixel", &rbImage::setPixel);
    ourDefinition.defineMethod<14>("get_pixel", &rbImage::getPixel);
    ourDefinition.defineMethod<15>("pixels", &rbImage::getPixel);
    ourDefinition.defineMethod<16>("flip_horizontally", &rbImage::flipHorizontally);
    ourDefinition.defineMethod<17>("flip_vertically", &rbImage::flipVertically);


	ourDefinition.aliasMethod("inspect", "to_s");
}

rbImageClass& rbImage::getDefinition()
{
    return ourDefinition;
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
        case 3:
            object->createFromColor(args[0].to<unsigned int>(), args[1].to<unsigned int>(), args[2].to<sf::Color>());
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 1 or 3" );
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
    const sf::Vector2u& imgSize = myObject.getSize();
    data.push_back(rb::Value::create(imgSize));
    const sf::Uint8* rawData = myObject.getPixelsPtr();
    for(int index = 0, size = imgSize.x * imgSize.y; index < size; index++)
    {
        data.push_back(rb::Value::create(rawData[index]));
    }
	return rb::Value::create(data);
}

void rbImage::marshalLoad(const std::vector<rb::Value>& data)
{
    sf::Vector2u imgSize = data[0].to<sf::Vector2u>();
    sf::Uint8* rawData = new sf::Uint8[data.size()-1];
    for(int index = 0, size = data.size()-1; index < size; index++)
    {
        rawData[index] = data[index+1].to<sf::Uint8>();
    }
    myObject.create(imgSize.x, imgSize.y, rawData);
    delete[] rawData;
}

std::string rbImage::inspect() const
{
    sf::Vector2u size = myObject.getSize();

    return ourDefinition.getName() + "(" + macro::toString(size.x) + ", " + macro::toString(size.y) + ")";
}

void rbImage::createFromColor(unsigned int width, unsigned int height, sf::Color color)
{
    myObject.create(width, height, color);
}

void rbImage::createFromData(unsigned int width, unsigned int height, const std::vector<rb::Value>& data)
{
    sf::Uint8* rawData = new sf::Uint8[data.size()];
    for(int index = 0, size = data.size(); index < size; index++)
    {
        rawData[index] = data[index].to<sf::Uint8>();
    }
    myObject.create(width, height, rawData);
    delete[] rawData;
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
    bool result = myObject.loadFromMemory(rawData, data.size());
    delete[] rawData;
    return result;
}

bool rbImage::saveToFile(const std::string& filename) const
{
    return myObject.saveToFile(filename);
}

sf::Vector2u rbImage::getSize() const
{
    return myObject.getSize();
}

rb::Value rbImage::createMaskFromColor(rb::Value self, const std::vector<rb::Value>& args)
{
	rbImage* object = self.to<rbImage*>();
	sf::Color color;
	sf::Uint8 alpha = 0;
	switch(args.size())
    {
        case 2:
            alpha = args[1].to<sf::Uint8>();
        case 1:
            color = args[0].to<sf::Color>();
            break;
        default:
        	rb::expectedNumArgs( args.size(), 1, 2 );
        	break;
    }

    object->myObject.createMaskFromColor(color, alpha);

	return rb::Nil;
}

rb::Value rbImage::copy(rb::Value self, const std::vector<rb::Value>& args)
{
	rbImage* object = self.to<rbImage*>();
	const sf::Image* source = nullptr;
	unsigned int destX = 0;
	unsigned int destY = 0;
	sf::IntRect sourceRect;
	bool applyAlpha = false;
	switch(args.size())
    {
        case 5:
            applyAlpha = args[4].to<bool>();
        case 4:
            sourceRect = args[3].to<sf::IntRect>();
        case 3:
            source = &args[0].to<const sf::Image&>();
            destX = args[1].to<unsigned int>();
            destY = args[2].to<unsigned int>();
            break;
        default:
        	rb::expectedNumArgs(args.size(), 3, 5);
        	break;
    }

    object->myObject.copy(*source, destX, destY, sourceRect, applyAlpha);

	return rb::Nil;
}

void rbImage::setPixel(unsigned int x, unsigned int y, sf::Color color)
{
    myObject.setPixel(x, y, color);
}

sf::Color rbImage::getPixel(unsigned int x, unsigned int y) const
{
    return myObject.getPixel(x, y);
}

rb::Value rbImage::getPixels() const
{
    std::vector<rb::Value> data;
    const sf::Vector2u& imgSize = myObject.getSize();
    const sf::Uint8* rawData = myObject.getPixelsPtr();
    for(int index = 0, size = imgSize.x * imgSize.y; index < size; index++)
    {
        data.push_back(rb::Value::create(rawData[index]));
    }
	return rb::Value::create(data);
}

void rbImage::flipHorizontally()
{
    myObject.flipHorizontally();
}

void rbImage::flipVertically()
{
    myObject.flipVertically();
}

namespace rb
{

template<>
rbImage* Value::to() const
{
	errorHandling(T_DATA);
	rbImage* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbImage, object);
	return object;
}

template<>
const rbImage* Value::to() const
{
	errorHandling(T_DATA);
	const rbImage* object = nullptr;
	if(myValue != Qnil)
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