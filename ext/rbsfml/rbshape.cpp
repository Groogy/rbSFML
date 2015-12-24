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

#include "rbshape.hpp"
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

rbShapeClass rbShape::ourDefinition;

void rbShape::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbShapeClass::defineClassUnder<rb::AbstractAllocator>("Shape", sfml);
	ourDefinition.includeModule(rb::Value(rbDrawable::getDefinition()));
	ourDefinition.includeModule(rb::Value(rbTransformable::getDefinition()));
	ourDefinition.defineMethod<0>("marshal_dump", &rbShape::marshalDump);
	ourDefinition.defineMethod<1>("texture=", &rbShape::setTexture);
	ourDefinition.defineMethod<2>("texture", &rbShape::getTexture);
	ourDefinition.defineMethod<3>("texture_rect=", &rbShape::setTextureRect);
    ourDefinition.defineMethod<4>("texture_rect", &rbShape::getTextureRect);
    ourDefinition.defineMethod<5>("fill_color=", &rbShape::setFillColor);
    ourDefinition.defineMethod<6>("fill_color", &rbShape::getFillColor);
    ourDefinition.defineMethod<7>("outline_color=", &rbShape::setOutlineColor);
    ourDefinition.defineMethod<8>("outline_color", &rbShape::getOutlineColor);
    ourDefinition.defineMethod<9>("outline_thickness=", &rbShape::setOutlineThickness);
    ourDefinition.defineMethod<10>("outline_thickness", &rbShape::getOutlineThickness);
    ourDefinition.defineMethod<11>("local_bounds", &rbShape::getLocalBounds);
    ourDefinition.defineMethod<12>("global_bounds", &rbShape::getGlobalBounds);
    ourDefinition.defineMethod<13>("point_count", &rbShape::getPointCount);
    ourDefinition.defineMethod<14>("get_point", &rbShape::getPoint);

	ourDefinition.aliasMethod("texture=", "set_texture");
	ourDefinition.aliasMethod("get_point", "[]");
}

rbShapeClass& rbShape::getDefinition()
{
    return ourDefinition;
}

rbShape::rbShape()
: rbTransformable()
{
}

rbShape::~rbShape()
{
}

rb::Value rbShape::marshalDump() const
{
    rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str());
    return rb::Nil;
}

rb::Value rbShape::setTexture(rb::Value self, const std::vector<rb::Value>& args)
{
    sf::Shape& shape = self.to<sf::Shape&>();
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

    if(texture == rb::Nil)
        shape.setTexture(nullptr, resetRect);
    else
        shape.setTexture(&texture.to<const sf::Texture&>(), resetRect);
    self.setVar<symVarInternalTexture>(texture);
    return rb::Nil;
}

rb::Value rbShape::getTexture() const
{
    rb::Value self(myValue);
    return self.getVar<symVarInternalTexture>();
}

void rbShape::setTextureRect(sf::IntRect rect)
{
    getShape().setTextureRect(rect);
}

const sf::IntRect& rbShape::getTextureRect() const
{
    return getShape().getTextureRect();
}

void rbShape::setFillColor(sf::Color color)
{
    getShape().setFillColor(color);
}

const sf::Color& rbShape::getFillColor() const
{
    return getShape().getFillColor();
}

void rbShape::setOutlineColor(sf::Color color)
{
    getShape().setOutlineColor(color);
}

const sf::Color& rbShape::getOutlineColor() const
{
    return getShape().getOutlineColor();
}

sf::FloatRect rbShape::getLocalBounds() const
{
    return getShape().getLocalBounds();
}

void rbShape::setOutlineThickness(float thickness)
{
    getShape().setOutlineThickness(thickness);
}

float rbShape::getOutlineThickness() const
{
    return getShape().getOutlineThickness();
}

sf::FloatRect rbShape::getGlobalBounds() const
{
    return getShape().getGlobalBounds();
}

unsigned int rbShape::getPointCount() const
{
    return getShape().getPointCount();
}

sf::Vector2f rbShape::getPoint(unsigned int index)
{
    return getShape().getPoint(index);
}

sf::Drawable* rbShape::getDrawable()
{
    return &getShape();
}

const sf::Drawable* rbShape::getDrawable() const
{
    return &getShape();
}

sf::Transformable* rbShape::getTransformable()
{
    return &getShape();
}

const sf::Transformable* rbShape::getTransformable() const
{
    return &getShape();
}

namespace rb
{

template<>
rbShape* Value::to() const
{
	errorHandling(T_DATA);
	rbShape* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbShape, object);
	return object;
}

template<>
const rbShape* Value::to() const
{
	errorHandling(T_DATA);
	const rbShape* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbShape, object);
	return object;
}

template<>
sf::Shape& Value::to() const
{
    return to<rbShape*>()->getShape();
}

template<>
const sf::Shape& Value::to() const
{
    return to<const rbShape*>()->getShape();
}

}