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

#include "rbevent.hpp"
#include "error.hpp"
#include "macros.hpp"

#define ACCESSOR_IMPL(Name, Type, Klass, Accessor) \
Type Klass::get##Name() const { return Accessor; } \
void Klass::set##Name(Type value) { Accessor = value; }

rbEventClass rbEvent::ourEventDefinition;
rbJoystickButtonEventClass rbJoystickButtonEvent::ourJoystickButtonDefinition;
rbJoystickConnectEventClass rbJoystickConnectEvent::ourJoystickConnectDefinition;
rbJoystickMoveEventClass rbJoystickMoveEvent::ourJoystickMoveDefinition;
rbKeyEventClass rbKeyEvent::ourKeyDefinition;
rbMouseButtonEventClass rbMouseButtonEvent::ourMouseButtonDefinition;
rbMouseMoveEventClass rbMouseMoveEvent::ourMouseMoveDefinition;
rbMouseWheelEventClass rbMouseWheelEvent::ourMouseWheelDefinition;
rbMouseWheelScrollEventClass rbMouseWheelScrollEvent::ourMouseWheelScrollDefinition;
rbSensorEventClass rbSensorEvent::ourSensorDefinition;
rbSizeEventClass rbSizeEvent::ourSizeDefinition;
rbTextEventClass rbTextEvent::ourTextDefinition;
rbTouchEventClass rbTouchEvent::ourTouchDefinition;

void rbEvent::defineClass(const rb::Value& sfml)
{
	ourEventDefinition = rbEventClass::defineClassUnder("Event", sfml);
	ourEventDefinition.defineMethod<0>("initialize", &rbEvent::initialize);
	ourEventDefinition.defineMethod<1>("type", &rbEvent::getType);

  	ourEventDefinition.defineConstant("Closed", rb::Value(sf::Event::Closed));
  	ourEventDefinition.defineConstant("Resized", rb::Value(sf::Event::Resized));
  	ourEventDefinition.defineConstant("LostFocus", rb::Value(sf::Event::LostFocus));
  	ourEventDefinition.defineConstant("GainedFocus", rb::Value(sf::Event::GainedFocus));
  	ourEventDefinition.defineConstant("TextEntered", rb::Value(sf::Event::TextEntered));
  	ourEventDefinition.defineConstant("KeyPressed", rb::Value(sf::Event::KeyPressed));
  	ourEventDefinition.defineConstant("KeyReleased", rb::Value(sf::Event::KeyReleased));
  	ourEventDefinition.defineConstant("MouseWheelMoved", rb::Value(sf::Event::MouseWheelMoved));
  	ourEventDefinition.defineConstant("MouseWheelScrolled", rb::Value(sf::Event::MouseWheelScrolled));
  	ourEventDefinition.defineConstant("MouseButtonPressed", rb::Value(sf::Event::MouseButtonPressed));
  	ourEventDefinition.defineConstant("MouseButtonReleased", rb::Value(sf::Event::MouseButtonReleased));
  	ourEventDefinition.defineConstant("MouseMoved", rb::Value(sf::Event::MouseMoved));
  	ourEventDefinition.defineConstant("MouseEntered", rb::Value(sf::Event::MouseEntered));
  	ourEventDefinition.defineConstant("MouseLeft", rb::Value(sf::Event::MouseLeft));
  	ourEventDefinition.defineConstant("JoystickButtonPressed", rb::Value(sf::Event::JoystickButtonPressed));
  	ourEventDefinition.defineConstant("JoystickButtonReleased", rb::Value(sf::Event::JoystickButtonReleased));
  	ourEventDefinition.defineConstant("JoystickMoved", rb::Value(sf::Event::JoystickMoved));
  	ourEventDefinition.defineConstant("JoystickConnected", rb::Value(sf::Event::JoystickConnected));
  	ourEventDefinition.defineConstant("JoystickDisconnected", rb::Value(sf::Event::JoystickDisconnected));
  	ourEventDefinition.defineConstant("TouchBegan", rb::Value(sf::Event::TouchBegan));
  	ourEventDefinition.defineConstant("TouchMoved", rb::Value(sf::Event::TouchMoved));
  	ourEventDefinition.defineConstant("TouchEnded", rb::Value(sf::Event::TouchEnded));
  	ourEventDefinition.defineConstant("SensorChanged", rb::Value(sf::Event::SensorChanged));
  	ourEventDefinition.defineConstant("Count", rb::Value(sf::Event::Count));

  	rbJoystickButtonEvent::defineClass(sfml);
  	rbJoystickConnectEvent::defineClass(sfml);
  	rbJoystickMoveEvent::defineClass(sfml);
  	rbKeyEvent::defineClass(sfml);
  	rbMouseButtonEvent::defineClass(sfml);
  	rbMouseMoveEvent::defineClass(sfml);
  	rbMouseWheelEvent::defineClass(sfml);
  	rbMouseWheelScrollEvent::defineClass(sfml);
  	rbSensorEvent::defineClass(sfml);
  	rbSizeEvent::defineClass(sfml);
  	rbTextEvent::defineClass(sfml);
  	rbTouchEvent::defineClass(sfml);
}

rbEvent* rbEvent::createEvent(const sf::Event& event)
{
  rbEvent* object = nullptr;
  switch(event.type)
  {
    case sf::Event::Resized:
      object = rbSizeEvent::ourSizeDefinition.newObject().to<rbEvent*>();
      break;
    case sf::Event::JoystickButtonPressed:
    case sf::Event::JoystickButtonReleased:
    	object = rbJoystickButtonEvent::ourJoystickButtonDefinition.newObject().to<rbEvent*>();
    	break;
    case sf::Event::JoystickConnected:
    case sf::Event::JoystickDisconnected:
    	object = rbJoystickConnectEvent::ourJoystickConnectDefinition.newObject().to<rbEvent*>();
    	break;
    case sf::Event::JoystickMoved:
    	object = rbJoystickMoveEvent::ourJoystickMoveDefinition.newObject().to<rbEvent*>();
    	break;
    case sf::Event::KeyPressed:
   	case sf::Event::KeyReleased:
   		object = rbKeyEvent::ourKeyDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::MouseButtonPressed:
   	case sf::Event::MouseButtonReleased:
   		object = rbMouseButtonEvent::ourMouseButtonDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::MouseMoved:
   		object = rbMouseMoveEvent::ourMouseMoveDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::MouseWheelMoved:
   		object = rbMouseWheelEvent::ourMouseWheelDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::MouseWheelScrolled:
   		object = rbMouseWheelScrollEvent::ourMouseWheelScrollDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::SensorChanged:
   		object = rbSensorEvent::ourSensorDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::TextEntered:
   		object = rbTextEvent::ourTextDefinition.newObject().to<rbEvent*>();
   		break;
   	case sf::Event::TouchBegan:
   	case sf::Event::TouchEnded:
   	case sf::Event::TouchMoved:
   		object = rbTouchEvent::ourTouchDefinition.newObject().to<rbEvent*>();
   		break;
    default:
    	object = rbEvent::ourEventDefinition.newObject().to<rbEvent*>();
      break;
  };
  
  object->myObject = event;
  return object;
}

rbEvent::rbEvent()
: rb::Object()
, myObject()
{
}

rbEvent::~rbEvent()
{
}

void rbEvent::initialize()
{
}

int rbEvent::getType() const
{
	return myObject.type;
}

void rbJoystickButtonEvent::defineClass(const rb::Value& sfml)
{
	ourJoystickButtonDefinition = rbJoystickButtonEventClass::defineClassUnder("JoystickButtonEvent", sfml, rb::Value(ourEventDefinition));
	ourJoystickButtonDefinition.defineMethod<0>("joystickId", &rbJoystickButtonEvent::getJoystickId);
	ourJoystickButtonDefinition.defineMethod<1>("joystickId=", &rbJoystickButtonEvent::setJoystickId);
	ourJoystickButtonDefinition.defineMethod<2>("button", &rbJoystickButtonEvent::getButton);
	ourJoystickButtonDefinition.defineMethod<3>("button=", &rbJoystickButtonEvent::setButton);
}

unsigned int rbJoystickButtonEvent::getJoystickId() const
{
  	return myObject.joystickButton.joystickId;
}

void rbJoystickButtonEvent::setJoystickId(unsigned int value)
{
  	myObject.joystickButton.joystickId = value;
}

unsigned int rbJoystickButtonEvent::getButton() const
{
	return myObject.joystickButton.button;
}

void rbJoystickButtonEvent::setButton(unsigned int value)
{
	myObject.joystickButton.button = value;
}

void rbJoystickConnectEvent::defineClass(const rb::Value& sfml)
{
	ourJoystickConnectDefinition = rbJoystickConnectEventClass::defineClassUnder("JoystickConnectEvent", sfml, rb::Value(ourEventDefinition));
	ourJoystickConnectDefinition.defineMethod<0>("joystickId", &rbJoystickConnectEvent::getJoystickId);
	ourJoystickConnectDefinition.defineMethod<1>("joystickId=", &rbJoystickConnectEvent::setJoystickId);
}

unsigned int rbJoystickConnectEvent::getJoystickId() const
{
  	return myObject.joystickConnect.joystickId;
}

void rbJoystickConnectEvent::setJoystickId(unsigned int value)
{
  	myObject.joystickConnect.joystickId = value;
}

void rbJoystickMoveEvent::defineClass(const rb::Value& sfml)
{
	ourJoystickMoveDefinition = rbJoystickMoveEventClass::defineClassUnder("JoystickMoveEvent", sfml, rb::Value(ourEventDefinition));
	ourJoystickMoveDefinition.defineMethod<0>("joystickId", &rbJoystickMoveEvent::getJoystickId);
	ourJoystickMoveDefinition.defineMethod<1>("joystickId=", &rbJoystickMoveEvent::setJoystickId);
	ourJoystickMoveDefinition.defineMethod<2>("axis", &rbJoystickMoveEvent::getAxis);
	ourJoystickMoveDefinition.defineMethod<3>("axis=", &rbJoystickMoveEvent::setAxis);
	ourJoystickMoveDefinition.defineMethod<4>("position", &rbJoystickMoveEvent::getPosition);
	ourJoystickMoveDefinition.defineMethod<5>("position=", &rbJoystickMoveEvent::setPosition);
}

unsigned int rbJoystickMoveEvent::getJoystickId() const
{
  	return myObject.joystickMove.joystickId;
}

void rbJoystickMoveEvent::setJoystickId(unsigned int value)
{
  	myObject.joystickMove.joystickId = value;
}

unsigned int rbJoystickMoveEvent::getAxis() const
{
	return myObject.joystickMove.axis;
}

void rbJoystickMoveEvent::setAxis(unsigned int value)
{
	myObject.joystickMove.axis = static_cast<sf::Joystick::Axis>(value);
}

float rbJoystickMoveEvent::getPosition() const
{
	return myObject.joystickMove.position;
}

void rbJoystickMoveEvent::setPosition(float value)
{
	myObject.joystickMove.position = value;
}

void rbKeyEvent::defineClass(const rb::Value& sfml)
{
	ourKeyDefinition = rbKeyEventClass::defineClassUnder("KeyEvent", sfml, rb::Value(ourEventDefinition));
	ourKeyDefinition.defineMethod<0>("code", &rbKeyEvent::getCode );
	ourKeyDefinition.defineMethod<1>("code=", &rbKeyEvent::setCode );
	ourKeyDefinition.defineMethod<2>("alt", &rbKeyEvent::getAlt );
	ourKeyDefinition.defineMethod<3>("alt=", &rbKeyEvent::setAlt );
	ourKeyDefinition.defineMethod<4>("control", &rbKeyEvent::getControl );
	ourKeyDefinition.defineMethod<5>("control=", &rbKeyEvent::setControl );
	ourKeyDefinition.defineMethod<6>("shift", &rbKeyEvent::getShift );
	ourKeyDefinition.defineMethod<7>("shift=", &rbKeyEvent::setShift );
	ourKeyDefinition.defineMethod<8>("system", &rbKeyEvent::getSystem );
	ourKeyDefinition.defineMethod<9>("system=", &rbKeyEvent::setSystem );
}

unsigned int rbKeyEvent::getCode() const
{
	return myObject.key.code;
}

void rbKeyEvent::setCode(unsigned int value)
{
	myObject.key.code = static_cast<sf::Keyboard::Key>(value);
}

ACCESSOR_IMPL(Alt, bool, rbKeyEvent, myObject.key.alt);
ACCESSOR_IMPL(Control, bool, rbKeyEvent, myObject.key.control);
ACCESSOR_IMPL(Shift, bool, rbKeyEvent, myObject.key.shift);
ACCESSOR_IMPL(System, bool, rbKeyEvent, myObject.key.system);

void rbMouseButtonEvent::defineClass(const rb::Value& sfml)
{
	ourMouseButtonDefinition = rbMouseButtonEventClass::defineClassUnder("MouseButtonEvent", sfml, rb::Value(ourEventDefinition));
	ourMouseButtonDefinition.defineMethod<0>("button", &rbMouseButtonEvent::getButton );
	ourMouseButtonDefinition.defineMethod<1>("button=", &rbMouseButtonEvent::setButton );
	ourMouseButtonDefinition.defineMethod<2>("x", &rbMouseButtonEvent::getX );
	ourMouseButtonDefinition.defineMethod<3>("x=", &rbMouseButtonEvent::setX );
	ourMouseButtonDefinition.defineMethod<4>("y", &rbMouseButtonEvent::getY );
	ourMouseButtonDefinition.defineMethod<5>("y=", &rbMouseButtonEvent::setY );
}

unsigned int rbMouseButtonEvent::getButton() const
{
	return myObject.mouseButton.button;
}

void rbMouseButtonEvent::setButton(unsigned int value)
{
	myObject.mouseButton.button = static_cast<sf::Mouse::Button>(value);
}

ACCESSOR_IMPL(X, int, rbMouseButtonEvent, myObject.mouseButton.x);
ACCESSOR_IMPL(Y, int, rbMouseButtonEvent, myObject.mouseButton.y);

void rbMouseMoveEvent::defineClass(const rb::Value& sfml)
{
	ourMouseMoveDefinition = rbMouseMoveEventClass::defineClassUnder("MouseMoveEvent", sfml, rb::Value(ourEventDefinition));
	ourMouseMoveDefinition.defineMethod<0>("x", &rbMouseMoveEvent::getX );
	ourMouseMoveDefinition.defineMethod<1>("x=", &rbMouseMoveEvent::setX );
	ourMouseMoveDefinition.defineMethod<2>("y", &rbMouseMoveEvent::getY );
	ourMouseMoveDefinition.defineMethod<3>("y=", &rbMouseMoveEvent::setY );
}

ACCESSOR_IMPL(X, int, rbMouseMoveEvent, myObject.mouseMove.x);
ACCESSOR_IMPL(Y, int, rbMouseMoveEvent, myObject.mouseMove.y);

void rbMouseWheelEvent::defineClass(const rb::Value& sfml)
{
	ourMouseWheelDefinition = rbMouseWheelEventClass::defineClassUnder("MouseWheelEvent", sfml, rb::Value(ourEventDefinition));
	ourMouseWheelDefinition.defineMethod<0>("delta", &rbMouseWheelEvent::getDelta );
	ourMouseWheelDefinition.defineMethod<1>("delta=", &rbMouseWheelEvent::setDelta );
	ourMouseWheelDefinition.defineMethod<2>("x", &rbMouseWheelEvent::getX );
	ourMouseWheelDefinition.defineMethod<3>("x=", &rbMouseWheelEvent::setX );
	ourMouseWheelDefinition.defineMethod<4>("y", &rbMouseWheelEvent::getY );
	ourMouseWheelDefinition.defineMethod<5>("y=", &rbMouseWheelEvent::setY );
}

ACCESSOR_IMPL(Delta, int, rbMouseWheelEvent, myObject.mouseWheel.delta);
ACCESSOR_IMPL(X, int, rbMouseWheelEvent, myObject.mouseWheel.x);
ACCESSOR_IMPL(Y, int, rbMouseWheelEvent, myObject.mouseWheel.y);

void rbMouseWheelScrollEvent::defineClass(const rb::Value& sfml)
{
	ourMouseWheelScrollDefinition = rbMouseWheelScrollEventClass::defineClassUnder("MouseWheelScrollEvent", sfml, rb::Value(ourEventDefinition));
	ourMouseWheelScrollDefinition.defineMethod<0>("wheel", &rbMouseWheelScrollEvent::getWheel );
	ourMouseWheelScrollDefinition.defineMethod<1>("wheel=", &rbMouseWheelScrollEvent::setWheel );
	ourMouseWheelScrollDefinition.defineMethod<2>("delta", &rbMouseWheelScrollEvent::getDelta );
	ourMouseWheelScrollDefinition.defineMethod<3>("delta=", &rbMouseWheelScrollEvent::setDelta );
	ourMouseWheelScrollDefinition.defineMethod<4>("x", &rbMouseWheelScrollEvent::getX );
	ourMouseWheelScrollDefinition.defineMethod<5>("x=", &rbMouseWheelScrollEvent::setX );
	ourMouseWheelScrollDefinition.defineMethod<6>("y", &rbMouseWheelScrollEvent::getY );
	ourMouseWheelScrollDefinition.defineMethod<7>("y=", &rbMouseWheelScrollEvent::setY );
}

unsigned int rbMouseWheelScrollEvent::getWheel() const
{
	return myObject.mouseWheelScroll.wheel;
}

void rbMouseWheelScrollEvent::setWheel(unsigned int value)
{
	myObject.mouseWheelScroll.wheel = static_cast<sf::Mouse::Wheel>(value);
}

ACCESSOR_IMPL(Delta, int, rbMouseWheelScrollEvent, myObject.mouseWheelScroll.delta);
ACCESSOR_IMPL(X, int, rbMouseWheelScrollEvent, myObject.mouseWheelScroll.x);
ACCESSOR_IMPL(Y, int, rbMouseWheelScrollEvent, myObject.mouseWheelScroll.y);

void rbSensorEvent::defineClass(const rb::Value& sfml)
{
	ourSensorDefinition = rbSensorEventClass::defineClassUnder("SensorEvent", sfml, rb::Value(ourEventDefinition));
	ourSensorDefinition.defineMethod<0>("sensor_type", &rbSensorEvent::getSensorType );
	ourSensorDefinition.defineMethod<1>("sensor_type=", &rbSensorEvent::setSensorType );
	ourSensorDefinition.defineMethod<2>("x", &rbSensorEvent::getX );
	ourSensorDefinition.defineMethod<3>("x=", &rbSensorEvent::setX );
	ourSensorDefinition.defineMethod<4>("y", &rbSensorEvent::getY );
	ourSensorDefinition.defineMethod<5>("y=", &rbSensorEvent::setY );
	ourSensorDefinition.defineMethod<6>("z", &rbSensorEvent::getZ );
	ourSensorDefinition.defineMethod<7>("z=", &rbSensorEvent::setZ );
}

unsigned int rbSensorEvent::getSensorType() const
{
	return myObject.sensor.type;
}

void rbSensorEvent::setSensorType(unsigned int value)
{
	myObject.sensor.type = static_cast<sf::Sensor::Type>(value);
}

ACCESSOR_IMPL(X, int, rbSensorEvent, myObject.sensor.x);
ACCESSOR_IMPL(Y, int, rbSensorEvent, myObject.sensor.y);
ACCESSOR_IMPL(Z, int, rbSensorEvent, myObject.sensor.z);

void rbSizeEvent::defineClass(const rb::Value& sfml)
{
	ourSizeDefinition = rbSizeEventClass::defineClassUnder("SizeEvent", sfml, rb::Value(ourEventDefinition));
	ourSizeDefinition.defineMethod<0>("width", &rbSizeEvent::getWidth);
	ourSizeDefinition.defineMethod<1>("width=", &rbSizeEvent::setWidth);
	ourSizeDefinition.defineMethod<2>("height", &rbSizeEvent::getHeight);
	ourSizeDefinition.defineMethod<3>("height=", &rbSizeEvent::setHeight);
}

int rbSizeEvent::getWidth() const
{
	return myObject.size.width;
}

void rbSizeEvent::setWidth(int value)
{
	myObject.size.width = value;
}

int rbSizeEvent::getHeight() const
{
	return myObject.size.height;
}

void rbSizeEvent::setHeight(int value)
{
	myObject.size.height = value;
}

void rbTextEvent::defineClass(const rb::Value& sfml)
{
	ourTextDefinition = rbTextEventClass::defineClassUnder("TextEvent", sfml, rb::Value(ourEventDefinition));
	ourTextDefinition.defineMethod<0>("unicode", &rbTextEvent::getUnicode);
	ourTextDefinition.defineMethod<1>("unicode=", &rbTextEvent::setUnicode);
}

ACCESSOR_IMPL(Unicode, sf::Uint32, rbTextEvent, myObject.text.unicode);

void rbTouchEvent::defineClass(const rb::Value& sfml)
{
	ourTouchDefinition = rbTouchEventClass::defineClassUnder("TouchEvent", sfml, rb::Value(ourEventDefinition));
	ourTouchDefinition.defineMethod<0>("finger", &rbTouchEvent::getFinger);
	ourTouchDefinition.defineMethod<1>("finger=", &rbTouchEvent::setFinger);
	ourTouchDefinition.defineMethod<2>("x", &rbTouchEvent::getX);
	ourTouchDefinition.defineMethod<3>("x=", &rbTouchEvent::setX);
	ourTouchDefinition.defineMethod<4>("y", &rbTouchEvent::getY);
	ourTouchDefinition.defineMethod<5>("y=", &rbTouchEvent::setY);
}

ACCESSOR_IMPL(Finger, unsigned int, rbTouchEvent, myObject.touch.finger);
ACCESSOR_IMPL(X, int, rbTouchEvent, myObject.touch.x);
ACCESSOR_IMPL(Y, int, rbTouchEvent, myObject.touch.y);

namespace rb
{

template<>
rbEvent* Value::to() const
{
	errorHandling(T_DATA);
	rbEvent* object = nullptr;
	Data_Get_Struct(myValue, rbEvent, object);
	return object;
}

template<>
const rbEvent* Value::to() const
{
	errorHandling(T_DATA);
	const rbEvent* object = nullptr;
	Data_Get_Struct(myValue, rbEvent, object);
	return object;
}

}