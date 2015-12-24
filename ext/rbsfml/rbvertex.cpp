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

#include "rbvertex.hpp"
#include "rbvector2.hpp"
#include "rbcolor.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

namespace 
{
	constexpr char symVarPosition[] = "@position";
	constexpr char symVarColor[] = "@color";
	constexpr char symVarTexCoords[] = "@tex_coords";
}

rbVertexClass rbVertex::ourDefinition;

void rbVertex::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbVertexClass::defineClassUnder<rb::RubyObjAllocator>("Vertex", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbVertex::initialize);
	ourDefinition.defineMethod<2>("marshal_dump", &rbVertex::marshalDump);

	ourDefinition.defineAttribute("position", true, true);
	ourDefinition.defineAttribute("color", true, true);
	ourDefinition.defineAttribute("tex_coords", true, true);
}

const rbVertexClass& rbVertex::getDefinition()
{
	return ourDefinition;
}

rb::Value rbVertex::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
    self.setVar<symVarPosition>(rbVector2::getDefinition().newObject());
    self.setVar<symVarColor>(rbColor::getDefinition().newObject());
    self.setVar<symVarTexCoords>(rbVector2::getDefinition().newObject());
	switch( args.size() )
    {
        case 0:
            break;
        case 3:
            self.setVar<symVarTexCoords>(args[2]);
        case 2:
            self.setVar<symVarColor>(args[1]);
        case 1:
            self.setVar<symVarPosition>(args[0]);
            break;
        default:
        	rb::expectedNumArgs( args.size(), 0, 3);
        	break;
    }

	return self;
}

rb::Value rbVertex::marshalDump(const rb::Value& self)
{
    std::vector<rb::Value> data;
    data.push_back(self.getVar<symVarPosition>());
    data.push_back(self.getVar<symVarColor>());
    data.push_back(self.getVar<symVarTexCoords>());
	return rb::Value::create(data);
}

void rbVertex::marshalLoad(rb::Value self, const std::vector<rb::Value>& data)
{
    self.setVar<symVarPosition>(data[0]);
    self.setVar<symVarColor>(data[1]);
    self.setVar<symVarTexCoords>(data[2]);
}

namespace rb
{

template<>
sf::Vertex Value::to() const
{
    errorHandling(T_OBJECT);
    sf::Vertex vertex(
        getVar<symVarPosition, sf::Vector2f>(), getVar<symVarColor, sf::Color>(), getVar<symVarTexCoords, sf::Vector2f>()
    );
    return vertex;
}

template<>
Value Value::create(sf::Vertex vertex)
{
    return rbVertex::getDefinition().newObject(rb::Value::create(vertex.position), rb::Value::create(vertex.color), rb::Value::create(vertex.texCoords));
}

template<>
Value Value::create(const sf::Vertex& vertex)
{
    return rbVertex::getDefinition().newObject(rb::Value::create(vertex.position), rb::Value::create(vertex.color), rb::Value::create(vertex.texCoords));
}

}