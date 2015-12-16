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

#include "rbvideomode.hpp"
#include "error.hpp"
#include "macros.hpp"

rbVideoModeClass rbVideoMode::ourDefinition;

void rbVideoMode::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbVideoModeClass::defineClassUnder("VideoMode", sfml);
	ourDefinition.includeModule(rb::Value(rb_mComparable));
	ourDefinition.defineFunction<0>("desktop_mode", &rbVideoMode::getDesktopMode);
	ourDefinition.defineFunction<1>("fullscreen_modes", &rbVideoMode::getFullscreenModes);
	ourDefinition.defineMethod<2>("initialize", &rbVideoMode::initialize);
	ourDefinition.defineMethod<3>("initialize_copy", &rbVideoMode::initializeCopy);
	ourDefinition.defineMethod<4>("valid?", &rbVideoMode::isValid);
	ourDefinition.defineMethod<5>("width", &rbVideoMode::getWidth);
	ourDefinition.defineMethod<6>("width=", &rbVideoMode::setWidth);
	ourDefinition.defineMethod<7>("height", &rbVideoMode::getHeight);
	ourDefinition.defineMethod<8>("height=", &rbVideoMode::setHeight);
	ourDefinition.defineMethod<9>("bits_per_pixel", &rbVideoMode::getBitsPerPixel);
	ourDefinition.defineMethod<10>("bits_per_pixel=", &rbVideoMode::setBitsPerPixel);
	ourDefinition.defineMethod<11>("marshal_dump", &rbVideoMode::marshalDump);
	ourDefinition.defineMethod<12>("inspect", &rbVideoMode::inspect);
	ourDefinition.defineMethod<13>("<=>", &rbVideoMode::compare);

	ourDefinition.aliasMethod("inspect", "to_s");
	ourDefinition.aliasMethod("bits_per_pixel", "bpp");
	ourDefinition.aliasMethod("bits_per_pixel=", "bpp=");
}

rbVideoMode::rbVideoMode()
: rb::Object()
, myObject()
{
}

rbVideoMode::~rbVideoMode()
{
}

rbVideoMode* rbVideoMode::getDesktopMode()
{
	rb::Value desktopMode = ourDefinition.newObject();
	rbVideoMode* object = desktopMode.to<rbVideoMode*>();
	object->myObject = sf::VideoMode::getDesktopMode();
	return object;
}

std::vector<rb::Value> rbVideoMode::getFullscreenModes()
{
	const std::vector<sf::VideoMode>& fullscreenModes = sf::VideoMode::getFullscreenModes();
	std::vector<rb::Value> convertedModes;
	for(int index = 0, size = fullscreenModes.size(); index < size; index++)
	{
		rb::Value value = ourDefinition.newObject();
		rbVideoMode* object = value.to<rbVideoMode*>();
		object->myObject = fullscreenModes[index];
		convertedModes.push_back(value);
	}
	return convertedModes;
}

rb::Value rbVideoMode::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	rbVideoMode* object = self.to<rbVideoMode*>();
	switch( args.size() )
    {
        case 0:
            break;
        case 2:
        	object->myObject = sf::VideoMode(args[0].to<unsigned int>(), args[1].to<unsigned int>());
        	break;
        case 3:
        	object->myObject = sf::VideoMode(args[0].to<unsigned int>(), args[1].to<unsigned int>(),
        							 args[2].to<unsigned int>());
        	break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 2 or 3" );
        	break;
    }

	return self;
}

rbVideoMode* rbVideoMode::initializeCopy(const rbVideoMode* value)
{
	myObject = value->myObject;
	return this;
}

bool rbVideoMode::isValid() const
{
	return myObject.isValid();
}

void rbVideoMode::setWidth(unsigned int value)
{
	myObject.width = value;
}

unsigned int rbVideoMode::getWidth() const
{
	return myObject.width;
}

void rbVideoMode::setHeight(unsigned int value)
{
	myObject.height = value;
}

unsigned int rbVideoMode::getHeight() const
{
	return myObject.height;
}

void rbVideoMode::setBitsPerPixel(unsigned int value)
{
	myObject.bitsPerPixel = value;
}

unsigned int rbVideoMode::getBitsPerPixel() const
{
	return myObject.bitsPerPixel;
}


rb::Value rbVideoMode::marshalDump() const
{
	rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
	return rb::Nil;
}

std::string rbVideoMode::inspect() const
{
	return ourDefinition.getName() + "(" 
		+ macro::toString(myObject.width) + ", "
		+ macro::toString(myObject.height) + ", "
		+ macro::toString(myObject.bitsPerPixel) + ")";
}

int rbVideoMode::compare(const rbVideoMode* other) const
{
	if(myObject == other->myObject) return 0;
	if(myObject > other->myObject) return 1;
	return -1;
}

namespace rb
{

template<>
rbVideoMode* Value::to() const
{
	errorHandling(T_DATA);
	rbVideoMode* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbVideoMode, object);
	return object;
}

template<>
const rbVideoMode* Value::to() const
{
	errorHandling(T_DATA);
	const rbVideoMode* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbVideoMode, object);
	return object;
}

}