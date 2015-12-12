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

#include "rbblendmode.hpp"
#include "error.hpp"

namespace 
{
	constexpr char symVarColorSrcFactor[] = "@color_src_factor";
	constexpr char symVarColorDstFactor[] = "@color_dst_factor";
	constexpr char symVarColorEquation[]  = "@color_equation";
	constexpr char symVarAlphaSrcFactor[] = "@alpha_src_factor";
	constexpr char symVarAlphaDstFactor[] = "@alpha_dst_factor";
	constexpr char symVarAlphaEquation[]  = "@alpha_equation";
}

rbBlendModeClass rbBlendMode::ourDefinition;

void rbBlendMode::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbBlendModeClass::defineClassUnder<rb::RubyObjAllocator>("BlendMode", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbBlendMode::initialize);
	ourDefinition.defineMethod<1>("==", &rbBlendMode::equal);
	ourDefinition.defineMethod<2>("inspect", &rbBlendMode::inspect);

	ourDefinition.defineAttribute("color_src_factor", true, true);
	ourDefinition.defineAttribute("color_dst_factor", true, true);
	ourDefinition.defineAttribute("color_equation", true, true);
	ourDefinition.defineAttribute("alpha_src_factor", true, true);
	ourDefinition.defineAttribute("alpha_dst_factor", true, true);
	ourDefinition.defineAttribute("alpha_equation", true, true);

	ourDefinition.aliasMethod("inspect", "to_s");

	ourDefinition.defineConstant("Zero", rb::Value(sf::BlendMode::Zero));
	ourDefinition.defineConstant("One", rb::Value(sf::BlendMode::One));
	ourDefinition.defineConstant("SrcColor", rb::Value(sf::BlendMode::SrcColor));
	ourDefinition.defineConstant("OneMinusSrcColor", rb::Value(sf::BlendMode::OneMinusSrcColor));
	ourDefinition.defineConstant("DstColor", rb::Value(sf::BlendMode::DstColor));
	ourDefinition.defineConstant("OneMinusDstColor", rb::Value(sf::BlendMode::OneMinusDstColor));
	ourDefinition.defineConstant("SrcAlpha", rb::Value(sf::BlendMode::SrcAlpha));
	ourDefinition.defineConstant("OneMinusSrcAlpha", rb::Value(sf::BlendMode::OneMinusSrcAlpha));
	ourDefinition.defineConstant("DstAlpha", rb::Value(sf::BlendMode::DstAlpha));
	ourDefinition.defineConstant("OneMinusDstAlpha", rb::Value(sf::BlendMode::OneMinusDstAlpha));
	ourDefinition.defineConstant("Add", rb::Value(sf::BlendMode::Add));
	ourDefinition.defineConstant("Subtract", rb::Value(sf::BlendMode::Subtract));
}

const rbBlendModeClass& rbBlendMode::getDefinition()
{
	return ourDefinition;
}

rb::Value rbBlendMode::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	switch( args.size() )
    {
        case 0:
        	self.setVar<symVarColorSrcFactor>(sf::BlendMode::SrcAlpha);
        	self.setVar<symVarColorDstFactor>(sf::BlendMode::OneMinusSrcAlpha);
        	self.setVar<symVarColorEquation>(sf::BlendMode::Add);
        	self.setVar<symVarAlphaSrcFactor>(sf::BlendMode::One);
        	self.setVar<symVarAlphaDstFactor>(sf::BlendMode::OneMinusSrcAlpha);
        	self.setVar<symVarAlphaEquation>(sf::BlendMode::Add);
            break;
        case 3:
        	self.setVar<symVarColorSrcFactor>(args[0]);
        	self.setVar<symVarColorDstFactor>(args[1]);
        	self.setVar<symVarColorEquation>(args[2]);
        	self.setVar<symVarAlphaSrcFactor>(args[0]);
        	self.setVar<symVarAlphaDstFactor>(args[1]);
        	self.setVar<symVarAlphaEquation>(args[2]);
            break;
        case 6:
        	self.setVar<symVarColorSrcFactor>(args[0]);
        	self.setVar<symVarColorDstFactor>(args[1]);
        	self.setVar<symVarColorEquation>(args[2]);
        	self.setVar<symVarAlphaSrcFactor>(args[3]);
        	self.setVar<symVarAlphaDstFactor>(args[4]);
        	self.setVar<symVarAlphaEquation>(args[5]);
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 3 or 6" );
        	break;
    }

	return self;
}

bool rbBlendMode::equal(const rb::Value& self, const rb::Value& other)
{
	if(!other.isKindOf(rb::Value(ourDefinition)))
		return false;

	if(!self.getVar<symVarColorSrcFactor>().equal(other.getVar<symVarColorSrcFactor>())) return false;
	if(!self.getVar<symVarColorDstFactor>().equal(other.getVar<symVarColorDstFactor>())) return false;
	if(!self.getVar<symVarColorEquation>().equal(other.getVar<symVarColorEquation>())) return false;
	if(!self.getVar<symVarAlphaSrcFactor>().equal(other.getVar<symVarAlphaSrcFactor>())) return false;
	if(!self.getVar<symVarAlphaDstFactor>().equal(other.getVar<symVarAlphaDstFactor>())) return false;
	if(!self.getVar<symVarAlphaEquation>().equal(other.getVar<symVarAlphaEquation>())) return false;
	return true;
}

std::string rbBlendMode::inspect(const rb::Value& self)
{
	std::string colorSrcFactor = macro::toString(self.getVar<symVarColorSrcFactor, sf::BlendMode::Factor>());
	std::string colorDstFactor = macro::toString(self.getVar<symVarColorDstFactor, sf::BlendMode::Factor>());
	std::string colorEquation = macro::toString(self.getVar<symVarColorEquation, sf::BlendMode::Equation>());
	std::string alphaSrcFactor = macro::toString(self.getVar<symVarAlphaSrcFactor, sf::BlendMode::Factor>());
	std::string alphaDstFactor = macro::toString(self.getVar<symVarAlphaDstFactor, sf::BlendMode::Factor>());
	std::string alphaEquation = macro::toString(self.getVar<symVarAlphaEquation, sf::BlendMode::Equation>());
	return ourDefinition.getName() + "(" + colorSrcFactor + ", " + colorDstFactor + ", " + colorEquation + 
									 ", " + alphaSrcFactor + ", " + alphaDstFactor + ", " + alphaEquation + ")";
}

namespace macro
{

template<>
std::string toString(const sf::BlendMode::Factor& value)
{
	switch(value)
	{
	case sf::BlendMode::Zero:
		return "Zero";
	case sf::BlendMode::One:
		return "One";
	case sf::BlendMode::SrcColor:
		return "SrcColor";
	case sf::BlendMode::OneMinusSrcColor:
		return "OneMinusSrcColor";
	case sf::BlendMode::DstColor:
		return "DstColor";
	case sf::BlendMode::SrcAlpha:
		return "SrcAlpha";
	case sf::BlendMode::OneMinusSrcAlpha:
		return "OneMinusSrcAlpha";
	case sf::BlendMode::DstAlpha:
		return "DstAlpha";
	case sf::BlendMode::OneMinusDstAlpha:
		return "OneMinusDstAlpha";
	}
	return "InvalidFactor";
}

template<>
std::string toString(const sf::BlendMode::Equation& value)
{
	switch(value)
	{
	case sf::BlendMode::Add:
		return "Add";
	case sf::BlendMode::Subtract:
		return "Subtract";
	}
}

}

namespace rb
{

template<>
sf::BlendMode::Factor Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::BlendMode::Factor>(value);
}

template<>
Value Value::create( sf::BlendMode::Factor value )
{
	return create(static_cast<unsigned int>(value));
}

template<>
sf::BlendMode::Equation Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::BlendMode::Equation>(value);
}

template<>
Value Value::create( sf::BlendMode::Equation value )
{
	return create(static_cast<unsigned int>(value));
}

template<>
sf::BlendMode Value::to() const
{
	errorHandling(T_OBJECT);
	sf::BlendMode mode(
		getVar<symVarColorSrcFactor, sf::BlendMode::Factor>(),
        getVar<symVarColorDstFactor, sf::BlendMode::Factor>(),
        getVar<symVarColorEquation, sf::BlendMode::Equation>(),
        getVar<symVarAlphaSrcFactor, sf::BlendMode::Factor>(),
        getVar<symVarAlphaDstFactor, sf::BlendMode::Factor>(),
        getVar<symVarAlphaEquation, sf::BlendMode::Equation>()
    );
	return mode;
}

template<>
Value Value::create( const sf::BlendMode& value )
{

	rb::Value object = rbBlendMode::getDefinition().newObject(
		value.colorSrcFactor, value.colorDstFactor, value.colorEquation,
		value.alphaSrcFactor, value.alphaDstFactor, value.alphaEquation
	);
	return object;
}

}