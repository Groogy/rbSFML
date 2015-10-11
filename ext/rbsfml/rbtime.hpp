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

#include <SFML/System/Time.hpp>
#include <string>
#include "class.hpp"
#include "object.hpp"

class rbTime;
class rbClock;

typedef rb::Class<rbTime> rbTimeClass;

class rbTime : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);

	static rbTime* seconds(float val);
	static rbTime* milliseconds(sf::Int32 val);
	static rbTime* microseconds(sf::Int64 val);

	rbTime();
	~rbTime();

	rbTime* initializeCopy(const rbTime* value);

	float asSeconds() const;
	sf::Int32 asMilliseconds() const;
	sf::Int64 asMicroseconds() const;

	rb::Value marshalDump() const;
	std::string inspect() const;

	rbTime* negate() const;
	rbTime* addition(const rbTime* other) const;
	rbTime* subtract(const rbTime* other) const;
	rbTime* multiply(const rb::Value& other) const;
	rb::Value divide(const rb::Value& other) const;

	int compare(const rbTime* other) const;

private:
	friend class rbClock;

	static rbTimeClass ourDefinition;

	sf::Time myObject;
};

namespace rb
{
	template<>
	rbTime* Value::to() const;
	template<>
	const rbTime* Value::to() const;
}