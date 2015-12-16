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

#include "rbcontextsettings.hpp"
#include "error.hpp"
#include "macros.hpp"

rbContextSettingsClass rbContextSettings::ourDefinition;

void rbContextSettings::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbContextSettingsClass::defineClassUnder("ContextSettings", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbContextSettings::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbContextSettings::initializeCopy);
	ourDefinition.defineMethod<2>("depth_bits=", &rbContextSettings::setDepthBits);
	ourDefinition.defineMethod<3>("depth_bits", &rbContextSettings::getDepthBits);
	ourDefinition.defineMethod<4>("stencil_bits=", &rbContextSettings::setStencilBits);
	ourDefinition.defineMethod<5>("stencil_bits", &rbContextSettings::getStencilBits);
	ourDefinition.defineMethod<6>("antialiasing_level=", &rbContextSettings::setAntialiasingLevel);
	ourDefinition.defineMethod<7>("antialiasing_level", &rbContextSettings::getAntialiasingLevel);
	ourDefinition.defineMethod<8>("major_version=", &rbContextSettings::setMajorVersion);
	ourDefinition.defineMethod<9>("major_version", &rbContextSettings::getMajorVersion);
	ourDefinition.defineMethod<10>("minor_version=", &rbContextSettings::setMinorVersion);
	ourDefinition.defineMethod<11>("minor_version", &rbContextSettings::getMinorVersion);
	ourDefinition.defineMethod<12>("attribute_flags=", &rbContextSettings::setAttributeFlags);
	ourDefinition.defineMethod<13>("attribute_flags", &rbContextSettings::getAttributeFlags);
	ourDefinition.defineMethod<14>("marshal_dump", &rbContextSettings::marshalDump);
	ourDefinition.defineMethod<15>("inspect", &rbContextSettings::inspect);

	ourDefinition.aliasMethod("inspect", "to_s");

	ourDefinition.defineConstant("Default", rb::Value(sf::ContextSettings::Default));
	ourDefinition.defineConstant("Core", rb::Value(sf::ContextSettings::Core));
	ourDefinition.defineConstant("Debug", rb::Value(sf::ContextSettings::Debug));
}

rbContextSettings::rbContextSettings()
: rb::Object()
, myObject()
{
}

rbContextSettings::~rbContextSettings()
{
}

rb::Value rbContextSettings::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	rbContextSettings* object = self.to<rbContextSettings*>();
	switch( args.size() )
    {
        case 0:
            break;
        case 1:
        	object->myObject = sf::ContextSettings(
        		args[0].to<unsigned int>()
        	);
        	break;
        case 2:
        	object->myObject = sf::ContextSettings(
        		args[0].to<unsigned int>(), args[1].to<unsigned int>()
        	);
        	break;
        case 3:
        	object->myObject = sf::ContextSettings(
        		args[0].to<unsigned int>(), args[1].to<unsigned int>(),
        		args[2].to<unsigned int>()
        	);
        	break;
        case 4:
        	object->myObject = sf::ContextSettings(
        		args[0].to<unsigned int>(), args[1].to<unsigned int>(),
        		args[2].to<unsigned int>(), args[3].to<unsigned int>()
        	);
        	break;
        case 5:
        	object->myObject = sf::ContextSettings(
        		args[0].to<unsigned int>(), args[1].to<unsigned int>(),
        		args[2].to<unsigned int>(), args[3].to<unsigned int>(),
        		args[4].to<unsigned int>()
        	);
        	break;
        case 6:
        	object->myObject = sf::ContextSettings(
        		args[0].to<unsigned int>(), args[1].to<unsigned int>(),
        		args[2].to<unsigned int>(), args[3].to<unsigned int>(),
        		args[4].to<unsigned int>(), args[5].to<unsigned int>()
        	);
        	break;
        default:
        	rb::expectedNumArgs( args.size(), 0, 6 );
        	break;
    }

	return self;
}

rbContextSettings* rbContextSettings::initializeCopy(const rbContextSettings* value)
{
	myObject = value->myObject;
	return this;
}

void rbContextSettings::setDepthBits(unsigned int value)
{
	myObject.depthBits = value;
}

unsigned int rbContextSettings::getDepthBits() const
{
	return myObject.depthBits;
}

void rbContextSettings::setStencilBits(unsigned int value)
{
	myObject.stencilBits = value;
}

unsigned int rbContextSettings::getStencilBits() const
{
	return myObject.stencilBits;
}

void rbContextSettings::setAntialiasingLevel(unsigned int value)
{
	myObject.antialiasingLevel = value;
}

unsigned int rbContextSettings::getAntialiasingLevel() const
{
	return myObject.antialiasingLevel;
}

void rbContextSettings::setMajorVersion(unsigned int value)
{
	myObject.majorVersion = value;
}

unsigned int rbContextSettings::getMajorVersion() const
{
	return myObject.majorVersion;
}

void rbContextSettings::setMinorVersion(unsigned int value)
{
	myObject.minorVersion = value;
}

unsigned int rbContextSettings::getMinorVersion() const
{
	return myObject.minorVersion;
}

void rbContextSettings::setAttributeFlags(unsigned int value)
{
	myObject.attributeFlags = value;
}

unsigned int rbContextSettings::getAttributeFlags() const
{
	return myObject.attributeFlags;
}

rb::Value rbContextSettings::marshalDump() const
{
	rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
	return rb::Nil;
}

std::string rbContextSettings::inspect() const
{
	return ourDefinition.getName() + "(" 
		+ macro::toString(myObject.depthBits) + ", "
		+ macro::toString(myObject.stencilBits) + ", "
		+ macro::toString(myObject.antialiasingLevel) + ", "
		+ macro::toString(myObject.majorVersion) + ", "
		+ macro::toString(myObject.minorVersion) + ")";
}

namespace rb
{

template<>
rbContextSettings* Value::to() const
{
	errorHandling(T_DATA);
	rbContextSettings* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbContextSettings, object);
	return object;
}

template<>
const rbContextSettings* Value::to() const
{
	errorHandling(T_DATA);
	const rbContextSettings* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbContextSettings, object);
	return object;
}

}