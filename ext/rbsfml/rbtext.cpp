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

#include "rbtext.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "rbfont.hpp"
#include "rbcolor.hpp"
#include "error.hpp"
#include "macros.hpp"

namespace
{
    constexpr char symVarInternalFont[] = "@__internal__font";
}

rbTextClass rbText::ourDefinition;

void rbText::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbTextClass::defineClassUnder("Font", sfml);
	ourDefinition.includeModule(rb::Value(rbDrawable::getDefinition()));
	ourDefinition.includeModule(rb::Value(rbTransformable::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbText::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbText::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbText::marshalDump);
    ourDefinition.defineMethod<3>("color=", &rbText::setColor);
    ourDefinition.defineMethod<4>("color", &rbText::getColor);
    ourDefinition.defineMethod<5>("local_bounds", &rbText::getLocalBounds);
    ourDefinition.defineMethod<6>("global_bounds", &rbText::getGlobalBounds);
    ourDefinition.defineMethod<7>("string=", &rbText::setString);
    ourDefinition.defineMethod<8>("string", &rbText::getString);
    ourDefinition.defineMethod<9>("font=", &rbText::setFont);
    ourDefinition.defineMethod<10>("font", &rbText::getFont);
    ourDefinition.defineMethod<11>("character_size=", &rbText::setCharacterSize);
    ourDefinition.defineMethod<12>("character_size", &rbText::getCharacterSize);
    ourDefinition.defineMethod<13>("style=", &rbText::setStyle);
    ourDefinition.defineMethod<14>("style", &rbText::getStyle);
    ourDefinition.defineMethod<15>("find_character_pos", &rbText::findCharacterPos);

    ourDefinition.defineConstant("Regular", rb::Value(sf::Text::Regular));
    ourDefinition.defineConstant("Bold", rb::Value(sf::Text::Bold));
    ourDefinition.defineConstant("Italic", rb::Value(sf::Text::Italic));
    ourDefinition.defineConstant("Underlined", rb::Value(sf::Text::Underlined));
    ourDefinition.defineConstant("StrikeThrough", rb::Value(sf::Text::StrikeThrough));
}

rbTextClass& rbText::getDefinition()
{
    return ourDefinition;
}

rbText::rbText()
: rbTransformable()
, myObject()
{
}

rbText::~rbText()
{
}

rb::Value rbText::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	sf::Text& object = self.to<sf::Text&>();
	switch(args.size())
    {
        case 0:
            break;
        case 2:
            object.setString(args[0].to<const std::string&>());
            object.setFont(args[1].to<const sf::Font&>());
            self.setVar<symVarInternalFont>(args[1]);
            break;
        case 3:
            object.setString(args[0].to<const std::string&>());
            object.setFont(args[1].to<const sf::Font&>());
            object.setCharacterSize(args[2].to<unsigned int>());
            self.setVar<symVarInternalFont>(args[1]);
            break;
        default:
        	rb::expectedNumArgs(args.size(), "0, 2 or 3");
        	break;
    }

	return self;
}

rbText* rbText::initializeCopy(const rbText* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbText::marshalDump() const
{
    rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str());
    return rb::Nil;
}

void rbText::setColor(sf::Color color)
{
    myObject.setColor(color);
}

const sf::Color& rbText::getColor() const
{
    return myObject.getColor();
}

sf::FloatRect rbText::getLocalBounds() const
{
    return myObject.getLocalBounds();
}

sf::FloatRect rbText::getGlobalBounds() const
{
    return myObject.getGlobalBounds();
}

void rbText::setString(const std::string& text)
{
    myObject.setString(text);
}

std::string rbText::getString() const
{
    return myObject.getString();
}

void rbText::setFont(rb::Value font)
{
    rb::Value self(this);
    self.setVar<symVarInternalFont>(font);
    myObject.setFont(font.to<const sf::Font&>());
}

rb::Value rbText::getFont() const
{
    rb::Value self(this);
    return self.getVar<symVarInternalFont>();
}

void rbText::setCharacterSize(unsigned int size)
{
    myObject.setCharacterSize(size);
}

unsigned int rbText::getCharacterSize() const
{
    return myObject.getCharacterSize();
}

void rbText::setStyle(sf::Uint32 style)
{
    myObject.setStyle(style);
}

sf::Uint32 rbText::getStyle() const
{
    return myObject.getStyle();
}

sf::Vector2f rbText::findCharacterPos(unsigned int index) const
{
    return myObject.findCharacterPos(index);
}

sf::Drawable* rbText::getDrawable()
{
    return &myObject;
}

const sf::Drawable* rbText::getDrawable() const
{
    return &myObject;
}

sf::Transformable* rbText::getTransformable()
{
    return &myObject;
}

const sf::Transformable* rbText::getTransformable() const
{
    return &myObject;
}

namespace rb
{

template<>
rbText* Value::to() const
{
	errorHandling(T_DATA);
	rbText* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbText, object);
	return object;
}

template<>
const rbText* Value::to() const
{
	errorHandling(T_DATA);
	const rbText* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbText, object);
	return object;
}

template<>
sf::Text& Value::to() const
{
    return to<rbText*>()->myObject;
}

template<>
const sf::Text& Value::to() const
{
    return to<const rbText*>()->myObject;
}

template<>
sf::Text::Style Value::to() const
{
    return static_cast<sf::Text::Style>(to<unsigned int>());
}
template<>
Value Value::create(sf::Text::Style style)
{
    return create(static_cast<unsigned int>(style));
}

}