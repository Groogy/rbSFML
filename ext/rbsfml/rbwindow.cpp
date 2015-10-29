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

#include "rbwindow.hpp"
#include "rbcontextsettings.hpp"
#include "rbvideomode.hpp"
#include "rbnoncopyable.hpp"
#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"

#include <SFML/Window/WindowHandle.hpp>
#include <SFML/Window/WindowStyle.hpp>

rbWindowClass rbWindow::ourDefinition;

namespace 
{
	class StyleModule
	{
	};

	constexpr char freezeSym[] = "freeze";
}

void rbWindow::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbWindowClass::defineClassUnder("Window", sfml);
	ourDefinition.includeModule(rb::Value(rbNonCopyable::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbWindow::initialize);
	ourDefinition.defineMethod<1>("create", &rbWindow::create);
	ourDefinition.defineMethod<2>("close", &rbWindow::close);
	ourDefinition.defineMethod<3>("open?", &rbWindow::isOpen);
	ourDefinition.defineMethod<4>("settings", &rbWindow::getSettings);
	ourDefinition.defineMethod<5>("position=", &rbWindow::setPosition);
	ourDefinition.defineMethod<6>("position", &rbWindow::getPosition);
	ourDefinition.defineMethod<7>("size=", &rbWindow::setSize);
	ourDefinition.defineMethod<8>("size", &rbWindow::getSize);

	rb::Module<StyleModule> style = rb::Module<StyleModule>::defineModuleUnder("Style", sfml);
	style.defineConstant("None", rb::Value(sf::Style::None));
	style.defineConstant("Titlebar", rb::Value(sf::Style::Titlebar));
	style.defineConstant("Resize", rb::Value(sf::Style::Resize));
	style.defineConstant("Close", rb::Value(sf::Style::Close));
	style.defineConstant("Fullscreen", rb::Value(sf::Style::Fullscreen));
	style.defineConstant("Default", rb::Value(sf::Style::Default));
}

rbWindow::rbWindow()
: rb::Object()
, myObject()
{
}

rbWindow::~rbWindow()
{
}

rb::Value rbWindow::initialize(rb::Value self, const std::vector<rb::Value>& arguments)
{
	switch(arguments.size())
	{
	case 0:
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		rbWindow::create(self, arguments);
		break;
	default:
		rb::expectedNumArgs( arguments.size(), 0, 4 );
	};
	return self;
}

rb::Value rbWindow::create(rb::Value self, const std::vector<rb::Value>& arguments)
{
	rbWindow* object = self.to<rbWindow*>();
	switch(arguments.size())
	{
	case 1:
	{
		sf::WindowHandle handle = reinterpret_cast<sf::WindowHandle>(arguments[0].to<unsigned long>());
		object->myObject.create(handle);
		break;
	}
	case 2:
		if(arguments[0].getType() == rb::ValueType::Fixnum)
		{
			sf::WindowHandle handle = reinterpret_cast<sf::WindowHandle>(arguments[0].to<unsigned long>());
			rbContextSettings* settings = arguments[1].to<rbContextSettings*>();
			object->myObject.create(handle, settings->myObject);
		}
		else
		{
			rbVideoMode* mode = arguments[0].to<rbVideoMode*>();
			const std::string& title = arguments[1].to<const std::string&>();
			object->myObject.create(mode->myObject, title);
		}
		break;
	case 3:
	{
		rbVideoMode* mode = arguments[0].to<rbVideoMode*>();
		const std::string& title = arguments[1].to<const std::string&>();
		sf::Uint8 style = arguments[2].to<int>();
		object->myObject.create(mode->myObject, title, style);
		break;
	}
	case 4:
	{
		rbVideoMode* mode = arguments[0].to<rbVideoMode*>();
		const std::string& title = arguments[1].to<const std::string&>();
		sf::Uint8 style = arguments[2].to<int>();
		rbContextSettings* settings = arguments[3].to<rbContextSettings*>();
		object->myObject.create(mode->myObject, title, style, settings->myObject);
		break;
	}
	default:
		rb::expectedNumArgs( arguments.size(), 1, 4 );
	};
	return self;
}

void rbWindow::close()
{
	return myObject.close();
}

bool rbWindow::isOpen() const
{
	return myObject.isOpen();
}

rbContextSettings* rbWindow::getSettings() const
{
	rb::Value value = rbContextSettings::ourDefinition.newObject();
	rbContextSettings* object = value.to<rbContextSettings*>();
	object->myObject = myObject.getSettings();
	value.call<freezeSym>();
	return object;
}

void rbWindow::setPosition(sf::Vector2i position)
{
	myObject.setPosition(position);
}

sf::Vector2i rbWindow::getPosition() const
{
	return myObject.getPosition();
}

void rbWindow::setSize(sf::Vector2u size)
{
	myObject.setSize(size);
}

sf::Vector2u rbWindow::getSize() const
{
	return myObject.getSize();
}

namespace rb
{

template<>
rbWindow* Value::to() const
{
	errorHandling(T_DATA);
	rbWindow* object = nullptr;
	Data_Get_Struct(myValue, rbWindow, object);
	return object;
}

template<>
const rbWindow* Value::to() const
{
	errorHandling(T_DATA);
	const rbWindow* object = nullptr;
	Data_Get_Struct(myValue, rbWindow, object);
	return object;
}

}