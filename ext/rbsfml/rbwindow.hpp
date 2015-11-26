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

#ifndef RBSFML_RBWINDOW_HPP_
#define RBSFML_RBWINDOW_HPP_

#include <SFML/Window/Window.hpp>
#include "class.hpp"
#include "object.hpp"

class rbWindow;
class rbContextSettings;
class rbEvent;

typedef rb::Class<rbWindow> rbWindowClass;

class rbWindow : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);

	rbWindow();
	~rbWindow();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& arguments);
	static rb::Value create(rb::Value self, const std::vector<rb::Value>& arguments);

	void close();
	bool isOpen() const;

	rbContextSettings* getSettings() const;

	void setPosition(sf::Vector2i position);
	sf::Vector2i getPosition() const;

	void setSize(sf::Vector2u size);
	sf::Vector2u getSize() const;

	void setTitle(const std::string& title);

	void setIcon(unsigned int width, unsigned int height, const std::vector<rb::Value>& pixels);

	void setVisible(bool enabled);
	void setVerticalSyncEnabled(bool enabled);
	void setMouseCursorVisible(bool enabled);
	void setKeyRepeatEnabled(bool enabled);
	void setFramerateLimit(unsigned int limit);
	void setJoystickThreshold(float treshold);
	static rb::Value setActive(rb::Value self, const std::vector<rb::Value>& arguments);
	void requestFocus();
	bool hasFocus() const;
	void display();
	sf::WindowHandle getSystemHandle() const;

	rbEvent* pollEvent();
	rbEvent* waitEvent();

	rb::Value eachEvent();

private:
	friend class rb::Value;

	static rbWindowClass ourDefinition;

	sf::Window myObject;
};

namespace rb
{
	template<>
	rbWindow* Value::to() const;
	template<>
	const rbWindow* Value::to() const;

	template<>
	sf::Window& Value::to() const;
	template<>
	const sf::Window& Value::to() const;
}

#endif // RBSFML_RBWINDOW_HPP_
