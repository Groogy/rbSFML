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
#include "error.hpp"
#include "macros.hpp"

rbSpriteClass rbSprite::ourDefinition;

void rbSprite::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbSpriteClass::defineClassUnder("Sprite", sfml);
	ourDefinition.includeModule(rb::Value(rbDrawable::getDefinition()));
	ourDefinition.includeModule(rb::Value(rbTransformable::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbSprite::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbSprite::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbSprite::marshalDump);
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
            break;
        case 2:
            object.setTexture(args[0].to<const sf::Texture&>(), true);
            object.setTextureRect(args[1].to<sf::IntRect>());
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