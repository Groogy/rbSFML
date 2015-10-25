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

#ifndef RBSFML_RBCONTEXTSETTINGS_HPP_
#define RBSFML_RBCONTEXTSETTINGS_HPP_

#include <SFML/Config.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include "class.hpp"
#include "object.hpp"

class rbContextSettings;

typedef rb::Class<rbContextSettings> rbContextSettingsClass;

class rbContextSettings : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);

	rbContextSettings();
	~rbContextSettings();

	static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	rbContextSettings* initializeCopy(const rbContextSettings* value);

	void setDepthBits(unsigned int value);
	unsigned int getDepthBits() const;
	void setStencilBits(unsigned int value);
	unsigned int getStencilBits() const;
	void setAntialiasingLevel(unsigned int value);
	unsigned int getAntialiasingLevel() const;
	void setMajorVersion(unsigned int value);
	unsigned int getMajorVersion() const;
	void setMinorVersion(unsigned int value);
	unsigned int getMinorVersion() const;
	void setAttributeFlags(unsigned int value);
	unsigned int getAttributeFlags() const;

	rb::Value marshalDump() const;
	std::string inspect() const;

private:
	friend class rbContext;
	
	static rbContextSettingsClass ourDefinition;

	sf::ContextSettings myObject;
};

namespace rb
{
	template<>
	rbContextSettings* Value::to() const;
	template<>
	const rbContextSettings* Value::to() const;
}

#endif // RBSFML_RBCONTEXTSETTINGS_HPP_
