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
#include "rbevent.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

#include <SFML/Window/WindowHandle.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/Event.hpp>

rbWindowClass rbWindow::ourDefinition;

namespace 
{
	class StyleModule
	{
	};

	constexpr char freezeSym[] = "freeze";
}

class rbWindowImpl : public rbWindow
{
public:
protected:
    sf::Window* getWindow() { return &myObject; }
    const sf::Window* getWindow() const { return &myObject; }

private:
    sf::Window myObject;
};

typedef rb::DefaultAllocator<rbWindowImpl> AllocatorImpl;

void rbWindow::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbWindowClass::defineClassUnder<AllocatorImpl>("Window", sfml);
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
	ourDefinition.defineMethod<9>("set_title", &rbWindow::setTitle);
	ourDefinition.defineMethod<10>("set_icon", &rbWindow::setIcon);
	ourDefinition.defineMethod<11>("visible=", &rbWindow::setVisible);
	ourDefinition.defineMethod<12>("vertical_sync_enabled=", &rbWindow::setVerticalSyncEnabled);
	ourDefinition.defineMethod<13>("mouse_cursor_visible=", &rbWindow::setMouseCursorVisible);
	ourDefinition.defineMethod<14>("key_repeat_enabled=", &rbWindow::setKeyRepeatEnabled);
	ourDefinition.defineMethod<15>("framerate_limit=", &rbWindow::setFramerateLimit);
	ourDefinition.defineMethod<16>("joystick_threshold=", &rbWindow::setJoystickThreshold);
	ourDefinition.defineMethod<17>("set_active", &rbWindow::setActive);
	ourDefinition.defineMethod<18>("request_focus", &rbWindow::requestFocus);
	ourDefinition.defineMethod<19>("has_focus", &rbWindow::hasFocus);
	ourDefinition.defineMethod<20>("display", &rbWindow::display);
	ourDefinition.defineMethod<21>("system_handle", &rbWindow::getSystemHandle);
	ourDefinition.defineMethod<22>("poll_event", &rbWindow::pollEvent);
	ourDefinition.defineMethod<23>("wait_event", &rbWindow::waitEvent);
	ourDefinition.defineMethod<24>("each_event", &rbWindow::eachEvent);

	rb::Module<StyleModule> style = rb::Module<StyleModule>::defineModuleUnder("Style", sfml);
	style.defineConstant("None", rb::Value(sf::Style::None));
	style.defineConstant("Titlebar", rb::Value(sf::Style::Titlebar));
	style.defineConstant("Resize", rb::Value(sf::Style::Resize));
	style.defineConstant("Close", rb::Value(sf::Style::Close));
	style.defineConstant("Fullscreen", rb::Value(sf::Style::Fullscreen));
	style.defineConstant("Default", rb::Value(sf::Style::Default));
}

rbWindowClass& rbWindow::getDefinition()
{
    return ourDefinition;
}

rbWindow::rbWindow()
: rbRenderBaseType()
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
		object->getWindow()->create(handle);
		break;
	}
	case 2:
		if(arguments[0].getType() == rb::ValueType::Fixnum)
		{
			sf::WindowHandle handle = reinterpret_cast<sf::WindowHandle>(arguments[0].to<unsigned long>());
			rbContextSettings* settings = arguments[1].to<rbContextSettings*>();
			object->getWindow()->create(handle, settings->myObject);
		}
		else
		{
			rbVideoMode* mode = arguments[0].to<rbVideoMode*>();
			const std::string& title = arguments[1].to<const std::string&>();
			object->getWindow()->create(mode->myObject, title);
		}
		break;
	case 3:
	{
		rbVideoMode* mode = arguments[0].to<rbVideoMode*>();
		const std::string& title = arguments[1].to<const std::string&>();
		sf::Uint8 style = arguments[2].to<int>();
		object->getWindow()->create(mode->myObject, title, style);
		break;
	}
	case 4:
	{
		rbVideoMode* mode = arguments[0].to<rbVideoMode*>();
		const std::string& title = arguments[1].to<const std::string&>();
		sf::Uint8 style = arguments[2].to<int>();
		rbContextSettings* settings = arguments[3].to<rbContextSettings*>();
		object->getWindow()->create(mode->myObject, title, style, settings->myObject);
		break;
	}
	default:
		rb::expectedNumArgs(arguments.size(), 1, 4);
	};
	return self;
}

void rbWindow::close()
{
	return getWindow()->close();
}

bool rbWindow::isOpen() const
{
	getWindow()->isOpen();
}

rbContextSettings* rbWindow::getSettings() const
{
	rb::Value value = rbContextSettings::ourDefinition.newObject();
	rbContextSettings* object = value.to<rbContextSettings*>();
	object->myObject = getWindow()->getSettings();
	value.call<freezeSym>();
	return object;
}

void rbWindow::setPosition(sf::Vector2i position)
{
	getWindow()->setPosition(position);
}

sf::Vector2i rbWindow::getPosition() const
{
	return getWindow()->getPosition();
}

void rbWindow::setSize(sf::Vector2u size)
{
	getWindow()->setSize(size);
}

sf::Vector2u rbWindow::getSize() const
{
	return getWindow()->getSize();
}

void rbWindow::setTitle(const std::string& title)
{
	getWindow()->setTitle(title);
}

void rbWindow::setIcon(unsigned int width, unsigned int height, const std::vector<rb::Value>& pixels)
{
	std::vector<sf::Uint8> convPixels(pixels.size(), 0);
	for(int index = 0, size = pixels.size(); index < size; index++)
	{
		convPixels[index] = pixels[index].to<int>();
	}
	getWindow()->setIcon(width, height, convPixels.data());
}

void rbWindow::setVisible(bool enabled)
{
	getWindow()->setVisible(enabled);
}

void rbWindow::setVerticalSyncEnabled(bool enabled)
{
	getWindow()->setVerticalSyncEnabled(enabled);
}

void rbWindow::setMouseCursorVisible(bool enabled)
{
	getWindow()->setMouseCursorVisible(enabled);
}

void rbWindow::setKeyRepeatEnabled(bool enabled)
{
	getWindow()->setKeyRepeatEnabled(enabled);
}

void rbWindow::setFramerateLimit(unsigned int limit)
{
	getWindow()->setFramerateLimit(limit);
}

void rbWindow::setJoystickThreshold(float treshold)
{
	getWindow()->setJoystickThreshold(treshold);
}

rb::Value rbWindow::setActive(rb::Value self, const std::vector<rb::Value>& arguments)
{
	sf::Window& object = self.to<sf::Window&>();
	bool flag = true;
	switch(arguments.size())
	{
	case 0:
		break;
	case 1:
		flag = arguments[0].to<bool>();
		break;
	default:
		rb::expectedNumArgs(arguments.size(), 0, 1);
	};
	return rb::Value::create(object.setActive(flag));
}

void rbWindow::requestFocus()
{
	getWindow()->requestFocus();
}

bool rbWindow::hasFocus() const
{
	return getWindow()->hasFocus();
}

void rbWindow::display()
{
	getWindow()->display();
}

sf::WindowHandle rbWindow::getSystemHandle() const
{
	return getWindow()->getSystemHandle();
}

rbEvent* rbWindow::pollEvent()
{
	sf::Event event;
	if(getWindow()->pollEvent(event) == false)
		return nullptr;

	rbEvent* object = rbEvent::createEvent(event);
	return object;
}

rbEvent* rbWindow::waitEvent()
{
	sf::Event event;
	if(getWindow()->waitEvent(event) == false)
		return nullptr;

	rbEvent* object = rbEvent::createEvent(event);
	return object;
}

rb::Value rbWindow::eachEvent()
{
	if(!rb::blockGiven())
		return rb::getEnumerator(myValue);

	sf::Event event;
	while(getWindow()->pollEvent(event))
	{
		rbEvent* object = rbEvent::createEvent(event);
		rb::yield(rb::Value(object));
	}
	return myValue;
}

namespace rb
{

template<>
rbWindow* Value::to() const
{
	errorHandling(T_DATA);
	rbWindow* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbWindow, object);
	return object;
}

template<>
const rbWindow* Value::to() const
{
	errorHandling(T_DATA);
	const rbWindow* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbWindow, object);
	return object;
}

}