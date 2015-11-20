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

#ifndef RBSFML_RBEVENT_HPP_
#define RBSFML_RBEVENT_HPP_

#include <SFML/Window/Event.hpp>
#include "class.hpp"
#include "object.hpp"

class rbEvent;
class rbSizeEvent;
class rbJoystickButtonEvent;
class rbJoystickConnectEvent;
class rbJoystickMoveEvent;
class rbKeyEvent;
class rbMouseButtonEvent;
class rbMouseMoveEvent;
class rbMouseWheelEvent;
class rbMouseWheelScrollEvent;
class rbSensorEvent;
class rbTextEvent;
class rbTouchEvent;

typedef rb::Class<rbEvent> rbEventClass;
typedef rb::Class<rbJoystickButtonEvent> rbJoystickButtonEventClass;
typedef rb::Class<rbJoystickConnectEvent> rbJoystickConnectEventClass;
typedef rb::Class<rbJoystickMoveEvent> rbJoystickMoveEventClass;
typedef rb::Class<rbSizeEvent> rbSizeEventClass;
typedef rb::Class<rbKeyEvent> rbKeyEventClass;
typedef rb::Class<rbMouseButtonEvent> rbMouseButtonEventClass;
typedef rb::Class<rbMouseMoveEvent> rbMouseMoveEventClass;
typedef rb::Class<rbMouseWheelEvent> rbMouseWheelEventClass;
typedef rb::Class<rbMouseWheelScrollEvent> rbMouseWheelScrollEventClass;
typedef rb::Class<rbSensorEvent> rbSensorEventClass;
typedef rb::Class<rbTextEvent> rbTextEventClass;
typedef rb::Class<rbTouchEvent> rbTouchEventClass;

class rbEvent : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbEvent* createEvent(const sf::Event& event);

	rbEvent();
	~rbEvent();

	void initialize();

	int getType() const;

protected:
	static rbEventClass ourEventDefinition;

	sf::Event myObject;
};

class rbJoystickButtonEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getJoystickId() const;
	void setJoystickId(unsigned int value);

	unsigned int getButton() const;
	void setButton(unsigned int value);

protected:
	friend class rbEvent;

	static rbJoystickButtonEventClass ourJoystickButtonDefinition;
};

class rbJoystickConnectEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getJoystickId() const;
	void setJoystickId(unsigned int value);

protected:
	friend class rbEvent;

	static rbJoystickConnectEventClass ourJoystickConnectDefinition;
};

class rbJoystickMoveEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getJoystickId() const;
	void setJoystickId(unsigned int value);

	unsigned int getAxis() const;
	void setAxis(unsigned int value);

	float getPosition() const;
	void setPosition(float value);

protected:
	friend class rbEvent;

	static rbJoystickMoveEventClass ourJoystickMoveDefinition;
};

class rbKeyEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getCode() const;
	void setCode(unsigned int value);

	bool getAlt() const;
	void setAlt(bool value);

	bool getControl() const;
	void setControl(bool value);

	bool getShift() const;
	void setShift(bool value);

	bool getSystem() const;
	void setSystem(bool value);

protected:
	friend class rbEvent;

	static rbKeyEventClass ourKeyDefinition;
};

class rbMouseButtonEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getButton() const;
	void setButton(unsigned int value);
 	
	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

protected:
	friend class rbEvent;

	static rbMouseButtonEventClass ourMouseButtonDefinition;
};

class rbMouseMoveEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

protected:
	friend class rbEvent;

	static rbMouseMoveEventClass ourMouseMoveDefinition;
};

class rbMouseWheelEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	int getDelta() const;
	void setDelta(int value);

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

protected:
	friend class rbEvent;

	static rbMouseWheelEventClass ourMouseWheelDefinition;
};

class rbMouseWheelScrollEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getWheel() const;
	void setWheel(unsigned int value);

	int getDelta() const;
	void setDelta(int value);

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

protected:
	friend class rbEvent;

	static rbMouseWheelScrollEventClass ourMouseWheelScrollDefinition;
};

class rbSensorEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getSensorType() const;
	void setSensorType(unsigned int value);

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

	int getZ() const;
	void setZ(int value);

protected:
	friend class rbEvent;

	static rbSensorEventClass ourSensorDefinition;
};

class rbSizeEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	int getWidth() const;
	void setWidth(int value);

	int getHeight() const;
	void setHeight(int value);

protected:
	friend class rbEvent;

	static rbSizeEventClass ourSizeDefinition;
};

class rbTextEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	sf::Uint32 getUnicode() const;
	void setUnicode(sf::Uint32 value);

protected:
	friend class rbEvent;

	static rbTextEventClass ourTextDefinition;
};

class rbTouchEvent : public rbEvent
{
public:
	static void defineClass(const rb::Value& sfml);

	unsigned int getFinger() const;
	void setFinger(unsigned int value);

	int getX() const;
	void setX(int value);

	int getY() const;
	void setY(int value);

protected:
	friend class rbEvent;

	static rbTouchEventClass ourTouchDefinition;
};

namespace rb
{
	template<>
	rbEvent* Value::to() const;
	template<>
	const rbEvent* Value::to() const;
}

#endif // RBSFML_RBEVENT_HPP_
