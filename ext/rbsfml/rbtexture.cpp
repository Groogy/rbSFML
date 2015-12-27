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

#include "rbtexture.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "rbimage.hpp"
#include "rbwindow.hpp"
#include "rbdataptr.hpp"
#include "error.hpp"
#include "macros.hpp"

rbTextureClass rbTexture::ourDefinition;

void rbTexture::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbTextureClass::defineClassUnder("Texture", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbTexture::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbTexture::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbTexture::marshalDump);
	ourDefinition.defineMethod<3>("create", &rbTexture::create);
    ourDefinition.defineMethod<4>("load_from_file", &rbTexture::loadFromFile);
    ourDefinition.defineMethod<5>("load_from_memory", &rbTexture::loadFromMemory);
    ourDefinition.defineMethod<6>("load_from_image", &rbTexture::loadFromImage);
    ourDefinition.defineMethod<7>("size", &rbTexture::getSize);
    ourDefinition.defineMethod<8>("copy_to_image", &rbTexture::copyToImage);
    ourDefinition.defineMethod<9>("update", &rbTexture::update);
    ourDefinition.defineMethod<10>("smooth=", &rbTexture::setSmooth);
    ourDefinition.defineMethod<11>("smooth?", &rbTexture::isSmooth);
    ourDefinition.defineMethod<12>("repeated=", &rbTexture::setRepeated);
    ourDefinition.defineMethod<13>("repeated?", &rbTexture::isRepeated);
    ourDefinition.defineMethod<14>("native_handle", &rbTexture::getNativeHandle);
    ourDefinition.defineMethod<15>("native_ptr", &rbTexture::getNativePtr);

    ourDefinition.defineFunction<16>("bind", &rbTexture::bind);
    ourDefinition.defineFunction<17>("maximum_size", &rbTexture::getMaximumSize);

    ourDefinition.defineConstant("Normalized", rb::Value(sf::Texture::Normalized));
    ourDefinition.defineConstant("Pixels", rb::Value(sf::Texture::Pixels));
}

rbTextureClass& rbTexture::getDefinition()
{
    return ourDefinition;
}

rbTexture::rbTexture()
: rb::Object()
, myObject()
{
}

rbTexture::~rbTexture()
{
}

rb::Value rbTexture::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	rbTexture* object = self.to<rbTexture*>();
	switch( args.size() )
    {
        case 0:
            break;
        case 1:
            if(args[0].getType() == rb::ValueType::Array)
                loadFromMemory(self, args);
            else
                loadFromFile(self, args);
            break;
        case 2:
            object->create(args[0].to<unsigned int>(), args[1].to<unsigned int>());
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 1 or 3" );
        	break;
    }

	return self;
}

rbTexture* rbTexture::initializeCopy(const rbTexture* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbTexture::marshalDump() const
{
    rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
    return rb::Nil;
}

void rbTexture::create(unsigned int width, unsigned int height)
{
    myObject.create(width, height);
}

rb::Value rbTexture::loadFromFile(rb::Value self, const std::vector<rb::Value>& args)
{
    rbTexture* object = self.to<rbTexture*>();
    std::string filename;
    sf::IntRect rect;
    switch(args.size())
    {
        case 2:
            rect = args[1].to<sf::IntRect>();
        case 1:
            filename = args[0].to<std::string>();
            break;
        default:
           rb::expectedNumArgs( args.size(), 1, 2 );
           break;
    }
    bool result = object->myObject.loadFromFile(filename, rect);
    return rb::Value::create(result);
}

rb::Value rbTexture::loadFromMemory(rb::Value self, const std::vector<rb::Value>& args)
{
    rbTexture* object = self.to<rbTexture*>();
    std::vector<rb::Value> data;
    sf::IntRect rect;
    switch(args.size())
    {
        case 2:
            rect = args[1].to<sf::IntRect>();
        case 1:
            data = args[0].to<std::vector<rb::Value>>();
            break;
        default:
           rb::expectedNumArgs( args.size(), 1, 2 );
           break;
    }


    sf::Uint8* rawData = new sf::Uint8[data.size()];
    for(int index = 0, size = data.size(); index < size; index++)
    {
        rawData[index] = data[index].to<sf::Uint8>();
    }
    bool result = object->myObject.loadFromMemory(rawData, data.size(), rect);
    delete[] rawData;
    return rb::Value::create(result);
}

rb::Value rbTexture::loadFromImage(rb::Value self, const std::vector<rb::Value>& args)
{
    rbTexture* object = self.to<rbTexture*>();
    const sf::Image* img = nullptr;
    sf::IntRect rect;
    switch(args.size())
    {
        case 2:
            rect = args[1].to<sf::IntRect>();
        case 1:
            img = &args[0].to<const sf::Image&>();
            break;
        default:
           rb::expectedNumArgs( args.size(), 1, 2 );
           break;
    }
    bool result = object->myObject.loadFromImage(*img, rect);
    return rb::Value::create(result);
}

sf::Vector2u rbTexture::getSize() const
{
    return myObject.getSize();
}

rb::Value rbTexture::copyToImage() const
{
    rb::Value image = rbImage::getDefinition().newObject();
    image.to<sf::Image&>() = myObject.copyToImage();
    return image;
}

rb::Value rbTexture::update(rb::Value self, const std::vector<rb::Value>& args)
{
    rbTexture* texture = self.to<rbTexture*>();
    switch(args.size())
    {
        case 1:
            if(args[0].getType() == rb::ValueType::Array)
            {
                std::vector<rb::Value> data = args[0].to<std::vector<rb::Value>>();
                sf::Uint8* rawData = new sf::Uint8[data.size()];
                for(int index = 0, size = data.size(); index < size; index++)
                {
                    rawData[index] = data[index].to<sf::Uint8>();
                }
                texture->myObject.update(rawData);
                delete[] rawData;
            }
            else if(args[0].isKindOf(rb::Value(rbImage::getDefinition())))
            {
                texture->myObject.update(args[0].to<sf::Image&>());
            }
            else if(args[0].isKindOf(rb::Value(rbWindow::getDefinition())))
            {
                texture->myObject.update(args[0].to<sf::Window&>());
            }
            break;
        case 3:
            if(args[0].isKindOf(rb::Value(rbImage::getDefinition())))
            {
                texture->myObject.update(args[0].to<sf::Image&>(), args[1].to<unsigned int>(), args[2].to<unsigned int>());
            }
            else if(args[0].isKindOf(rb::Value(rbWindow::getDefinition())))
            {
                texture->myObject.update(args[0].to<sf::Window&>(), args[1].to<unsigned int>(), args[2].to<unsigned int>());
            }
            break;
        case 5:
            {
                std::vector<rb::Value> data = args[0].to<std::vector<rb::Value>>();
                sf::Uint8* rawData = new sf::Uint8[data.size()];
                for(int index = 0, size = data.size(); index < size; index++)
                {
                    rawData[index] = data[index].to<sf::Uint8>();
                }
                texture->myObject.update(rawData, args[1].to<unsigned int>(), args[2].to<unsigned int>(), args[3].to<unsigned int>(), args[4].to<unsigned int>());
                delete[] rawData;
                break;
            }
    }
    return rb::Nil;
}

void rbTexture::setSmooth(bool smooth)
{
    myObject.setSmooth(smooth);
}

bool rbTexture::isSmooth() const
{
    return myObject.isSmooth();
}

void rbTexture::setRepeated(bool repeated)
{
    myObject.setRepeated(repeated);
}

bool rbTexture::isRepeated() const
{
    return myObject.isRepeated();
}

unsigned int rbTexture::getNativeHandle() const
{
    return myObject.getNativeHandle();
}

void rbTexture::bind(const rbTexture* texture, sf::Texture::CoordinateType type)
{
    if(texture)
        sf::Texture::bind(&texture->myObject, type);
    else
        sf::Texture::bind(nullptr, type);
}

unsigned int rbTexture::getMaximumSize()
{
    return sf::Texture::getMaximumSize();
}

rbDataPtr* rbTexture::getNativePtr() const
{
    rbDataPtr* ptr = rbDataPtr::getDefinition().newObject().to<rbDataPtr*>();
    ptr->setPtr(reinterpret_cast<intptr_t>(&myObject));
    return ptr;
}

namespace rb
{

template<>
rbTexture* Value::to() const
{
	errorHandling(T_DATA);
	rbTexture* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbTexture, object);
	return object;
}

template<>
const rbTexture* Value::to() const
{
	errorHandling(T_DATA);
	const rbTexture* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbTexture, object);
	return object;
}

template<>
sf::Texture& Value::to() const
{
    return to<rbTexture*>()->myObject;
}

template<>
const sf::Texture& Value::to() const
{
    return to<const rbTexture*>()->myObject;
}

template<>
sf::Texture::CoordinateType Value::to() const
{
    errorHandling(T_FIXNUM);
    return static_cast<sf::Texture::CoordinateType>(to<unsigned int>());
}
template<>
Value Value::create(sf::Texture::CoordinateType value)
{
    return create(static_cast<unsigned int>(value));
}

}