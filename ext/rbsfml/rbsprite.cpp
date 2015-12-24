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

#include "rbsprite.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "rbtexture.hpp"
#include "rbcolor.hpp"
#include "error.hpp"
#include "macros.hpp"

namespace
{
    constexpr char symVarInternalTexture[] = "@__internal__texture";
}

rbSpriteClass rbSprite::ourDefinition;

void rbSprite::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbSpriteClass::defineClassUnder("Sprite", sfml);
	ourDefinition.includeModule(rb::Value(rbDrawable::getDefinition()));
	ourDefinition.includeModule(rb::Value(rbTransformable::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbSprite::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbSprite::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbSprite::marshalDump);
	ourDefinition.defineMethod<3>("texture=", &rbSprite::setTexture);
	ourDefinition.defineMethod<4>("texture", &rbSprite::getTexture);
	ourDefinition.defineMethod<5>("texture_rect=", &rbSprite::setTextureRect);
    ourDefinition.defineMethod<6>("texture_rect", &rbSprite::getTextureRect);
    ourDefinition.defineMethod<5>("color=", &rbSprite::setColor);
    ourDefinition.defineMethod<6>("color", &rbSprite::getColor);
    ourDefinition.defineMethod<6>("local_bounds", &rbSprite::getLocalBounds);
    ourDefinition.defineMethod<6>("global_bounds", &rbSprite::getGlobalBounds);

	ourDefinition.aliasMethod("texture=", "set_texture");
}

rbSpriteClass& rbSprite::getDefinition()
{
    return ourDefinition;
}

rbSprite::rbSprite()
: rbTransformable()
, myObject()
{
}

rbSprite::~rbSprite()
{
}

rb::Value rbSprite::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	sf::Sprite& object = self.to<sf::Sprite&>();
	switch(args.size())
    {
        case 0:
            break;
        case 1:
            object.setTexture(args[0].to<const sf::Texture&>(), true);
            self.setVar<symVarInternalTexture>(args[0]);
            break;
        case 2:
            object.setTexture(args[0].to<const sf::Texture&>(), true);
            object.setTextureRect(args[1].to<sf::IntRect>());
            self.setVar<symVarInternalTexture>(args[0]);
            break;
        default:
        	rb::expectedNumArgs(args.size(), 0, 2);
        	break;
    }

	return self;
}

rbSprite* rbSprite::initializeCopy(const rbSprite* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbSprite::marshalDump() const
{
    rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
    return rb::Nil;
}

rb::Value rbSprite::setTexture(rb::Value self, const std::vector<rb::Value>& args)
{
    sf::Sprite& sprite = self.to<sf::Sprite&>();
    rb::Value texture = rb::Nil;
    bool resetRect = false;
    switch(args.size())
    {
        case 2:
            resetRect = args[1].to<bool>();
        case 1:
            texture = args[0];
            break;
        default:
            rb::expectedNumArgs(args.size(), 1, 2);
            break;
    }

    sprite.setTexture(texture.to<const sf::Texture&>(), resetRect);
    self.setVar<symVarInternalTexture>(texture);
    return rb::Nil;
}

rb::Value rbSprite::getTexture() const
{
    rb::Value self(myValue);
    return self.getVar<symVarInternalTexture>();
}

void rbSprite::setTextureRect(sf::IntRect rect)
{
    myObject.setTextureRect(rect);
}

const sf::IntRect& rbSprite::getTextureRect() const
{
    return myObject.getTextureRect();
}

void rbSprite::setColor(sf::Color color)
{
    myObject.setColor(color);
}

const sf::Color& rbSprite::getColor() const
{
    return myObject.getColor();
}

sf::FloatRect rbSprite::getLocalBounds() const
{
    return myObject.getLocalBounds();
}

sf::FloatRect rbSprite::getGlobalBounds() const
{
    return myObject.getGlobalBounds();
}

sf::Drawable* rbSprite::getDrawable()
{
    return &myObject;
}

const sf::Drawable* rbSprite::getDrawable() const
{
    return &myObject;
}

sf::Transformable* rbSprite::getTransformable()
{
    return &myObject;
}

const sf::Transformable* rbSprite::getTransformable() const
{
    return &myObject;
}

namespace rb
{

template<>
rbSprite* Value::to() const
{
	errorHandling(T_DATA);
	rbSprite* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbSprite, object);
	return object;
}

template<>
const rbSprite* Value::to() const
{
	errorHandling(T_DATA);
	const rbSprite* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbSprite, object);
	return object;
}

template<>
sf::Sprite& Value::to() const
{
    return to<rbSprite*>()->myObject;
}

template<>
const sf::Sprite& Value::to() const
{
    return to<const rbSprite*>()->myObject;
}

}