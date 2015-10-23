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

#ifndef RBSFML_RBVIDEOMODE_HPP_
#define RBSFML_RBVIDEOMODE_HPP_

#include <SFML/Window/VideoMode.hpp>
#include "class.hpp"
#include "object.hpp"

class rbVideoMode;

typedef rb::Class<rbVideoMode> rbVideoModeClass;

class rbVideoMode : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);

	rbVideoMode();
	~rbVideoMode();

	static rbVideoMode* getDesktopMode();
	static std::vector<rb::Value> getFullscreenModes();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbVideoMode* initializeCopy(const rbVideoMode* value);

	bool isValid() const;

	void setWidth(unsigned int value);
	unsigned int getWidth() const;

	void setHeight(unsigned int value);
	unsigned int getHeight() const;

	void setBitsPerPixel(unsigned int value);
	unsigned int getBitsPerPixel() const;

	rb::Value marshalDump() const;
	std::string inspect() const;

	int compare(const rbVideoMode* other) const;

private:
	static rbVideoModeClass ourDefinition;

	sf::VideoMode myObject;
};

namespace rb
{
	template<>
	rbVideoMode* Value::to() const;
	template<>
	const rbVideoMode* Value::to() const;
}

#endif // RBSFML_RBVIDEOMODE_HPP_
