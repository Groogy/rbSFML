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

#include "rbrenderwindow.hpp"
#include "rbimage.hpp"
#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

rbRenderWindowClass rbRenderWindow::ourDefinition;

void rbRenderWindow::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbRenderWindowClass::defineClassUnder("RenderWindow", sfml, rb::Value(rbWindow::getDefinition()));
	ourDefinition.includeModule(rb::Value(rbRenderTarget::getDefinition()));
	ourDefinition.defineMethod<0>("size", &rbRenderWindow::getSize);
	ourDefinition.defineMethod<1>("capture", &rbRenderWindow::capture);
}

rbRenderWindowClass& rbRenderWindow::getDefinition()
{
    return ourDefinition;
}

rbRenderWindow::rbRenderWindow()
: rbWindow()
, rbRenderTarget()
, myObject()
{
}

rbRenderWindow::~rbRenderWindow()
{
}

sf::Vector2u rbRenderWindow::getSize() const
{
    return myObject.getSize();
}

rb::Value rbRenderWindow::capture() const
{
    rb::Value value = rbImage::getDefinition().newObject();
    value.to<sf::Image&>() = myObject.capture();
    return value;
}

sf::RenderTarget* rbRenderWindow::getRenderTarget()
{
    return &myObject;
}

const sf::RenderTarget* rbRenderWindow::getRenderTarget() const
{
    return &myObject;
}

sf::Window* rbRenderWindow::getWindow()
{
    return &myObject;
}

const sf::Window* rbRenderWindow::getWindow() const
{
    return &myObject;
}

sf::RenderWindow* rbRenderWindow::getRenderWindow()
{
    return &myObject;
}

const sf::RenderWindow* rbRenderWindow::getRenderWindow() const
{
    return &myObject;
}

namespace rb
{

template<>
rbRenderWindow* Value::to() const
{
	errorHandling(T_DATA);
	rbRenderWindow* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderWindow, object);
	return object;
}

template<>
const rbRenderWindow* Value::to() const
{
	errorHandling(T_DATA);
	const rbRenderWindow* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderWindow, object);
	return object;
}

}