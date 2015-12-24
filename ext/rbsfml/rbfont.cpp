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

#include "rbfont.hpp"
#include "rbrect.hpp"
#include "rbtexture.hpp"
#include "error.hpp"
#include "macros.hpp"

rbFontClass rbFont::ourDefinition;
rbFontInfoClass rbFont::ourInfoDefinition;
rbGlyphClass rbFont::ourGlyphDefinition;

namespace
{
    constexpr char symVarFamily[] = "@family";
    constexpr char symVarAdvance[] = "@advance";
    constexpr char symVarBounds[] = "@bounds";
    constexpr char symVarTextureRect[] = "@texture_rect";

    constexpr char symVarInternalTexture[] = "@__internal__texture";
    constexpr char symVarInternalTextureSize[] = "@__internal__texture_size";

    rb::Value rbFontInfo_initialize(rb::Value self, const std::vector<rb::Value>& args)
    {
        switch(args.size())
        {
            case 0:
                break;
            case 1:
                self.setVar<symVarFamily>(args[0]);
                break;
            default:
                rb::expectedNumArgs(args.size(), 0, 1);
        }
        return self;
    }

    rb::Value rbGlyph_initialize(rb::Value self, const std::vector<rb::Value>& args)
    {
        switch(args.size())
        {
            case 0:
                break;
            case 3:
                self.setVar<symVarAdvance>(args[0]);
                self.setVar<symVarBounds>(args[1]);
                self.setVar<symVarTextureRect>(args[2]);
                break;
            default:
                rb::expectedNumArgs(args.size(), "0 or 3");
        }
        return self;
    }
}

void rbFont::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbFontClass::defineClassUnder("Font", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbFont::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbFont::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbFont::marshalDump);
    ourDefinition.defineMethod<3>("load_from_file", &rbFont::loadFromFile);
    ourDefinition.defineMethod<4>("load_from_memory", &rbFont::loadFromMemory);
    ourDefinition.defineMethod<5>("info", &rbFont::getInfo);
    ourDefinition.defineMethod<6>("get_glyph", &rbFont::getGlyph);
    ourDefinition.defineMethod<7>("get_kerning", &rbFont::getKerning);
    ourDefinition.defineMethod<8>("get_line_spacing", &rbFont::getLineSpacing);
    ourDefinition.defineMethod<9>("get_underline_position", &rbFont::getUnderlinePosition);
    ourDefinition.defineMethod<10>("get_underline_thickness", &rbFont::getUnderlineThickness);
    ourDefinition.defineMethod<11>("get_texture", &rbFont::getTexture);

    ourInfoDefinition = rbFontInfoClass::defineClassUnder<rb::RubyObjAllocator>("Info", rb::Value(ourDefinition));
    ourInfoDefinition.defineMethod<0>("initialize", rbFontInfo_initialize);
    ourInfoDefinition.defineAttribute("family", true, true);

    ourGlyphDefinition = rbGlyphClass::defineClassUnder<rb::RubyObjAllocator>("Glyph", sfml);
    ourGlyphDefinition.defineMethod<0>("initialize", rbGlyph_initialize);
    ourGlyphDefinition.defineAttribute("advance", true, true);
    ourGlyphDefinition.defineAttribute("bounds", true, true);
    ourGlyphDefinition.defineAttribute("texture_rect", true, true);
}

rbFontClass& rbFont::getDefinition()
{
    return ourDefinition;
}

rbFont::rbFont()
: rb::Object()
, myObject()
{
}

rbFont::~rbFont()
{
}

rb::Value rbFont::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
    self.setVar<symVarInternalTexture>(rb::Nil);
    self.setVar<symVarInternalTextureSize>(0);

	rbFont* object = self.to<rbFont*>();
	switch(args.size())
    {
        case 0:
            break;
        case 1:
            if(args[0].getType() == rb::ValueType::Array)
                object->loadFromMemory(args[0].to<std::vector<rb::Value>>());
            else
                object->loadFromFile(args[0].to<const std::string&>());
            break;
        default:
        	rb::expectedNumArgs(args.size(), 0, 1);
        	break;
    }

	return self;
}

rbFont* rbFont::initializeCopy(const rbFont* value)
{
    rb::Value self(this);
    self.setVar<symVarInternalTexture>(rb::Nil);
    self.setVar<symVarInternalTextureSize>(0);
	myObject = value->myObject;
	return this;
}

rb::Value rbFont::marshalDump() const
{
    rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str());
    return rb::Nil;
}

bool rbFont::loadFromFile(const std::string& filename)
{
    return myObject.loadFromFile(filename);
}

bool rbFont::loadFromMemory(std::vector<rb::Value> data)
{
    sf::Uint8* rawData = new sf::Uint8[data.size()];
    for(int index = 0, size = data.size(); index < size; index++)
    {
        rawData[index] = data[index].to<sf::Uint8>();
    }
    bool result = myObject.loadFromMemory(rawData, data.size());
    delete[] rawData;
    return result;
}

const sf::Font::Info& rbFont::getInfo() const
{
    return myObject.getInfo();
}

const sf::Glyph& rbFont::getGlyph(unsigned int codePoint, unsigned int characterSize, bool bold) const
{
    return myObject.getGlyph(codePoint, characterSize, bold);
}

float rbFont::getKerning(unsigned int first, unsigned int second, unsigned int characterSize) const
{
    return myObject.getKerning(first, second, characterSize);
}

float rbFont::getLineSpacing(unsigned int characterSize) const
{
    return myObject.getLineSpacing(characterSize);
}

float rbFont::getUnderlinePosition(unsigned int characterSize) const
{
    return myObject.getUnderlinePosition(characterSize);
}

float rbFont::getUnderlineThickness(unsigned int characterSize) const
{
    return myObject.getUnderlineThickness(characterSize);
}

rb::Value rbFont::getTexture(unsigned int characterSize) const
{
    rb::Value self(this);
    if(self.getVar<symVarInternalTextureSize, unsigned int>() == characterSize) // Cache so we don't create a bunch of temporary textures
        return self.getVar<symVarInternalTexture>();

    rb::Value object = rbTexture::getDefinition().newObject();
    object.to<sf::Texture&>() = myObject.getTexture(characterSize);
    self.setVar<symVarInternalTexture>(object);
    self.setVar<symVarInternalTextureSize>(characterSize);
    return object;
}

namespace rb
{

template<>
rbFont* Value::to() const
{
	errorHandling(T_DATA);
	rbFont* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbFont, object);
	return object;
}

template<>
const rbFont* Value::to() const
{
	errorHandling(T_DATA);
	const rbFont* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbFont, object);
	return object;
}

template<>
sf::Font& Value::to() const
{
    return to<rbFont*>()->myObject;
}

template<>
const sf::Font& Value::to() const
{
    return to<const rbFont*>()->myObject;
}

template<>
sf::Font::Info Value::to() const
{
    sf::Font::Info info;
    info.family = getVar<symVarFamily, std::string>();
    return info;
}

template<>
sf::Glyph Value::to() const
{
    sf::Glyph glyph;
    glyph.advance = getVar<symVarAdvance, float>();
    glyph.bounds = getVar<symVarBounds, sf::FloatRect>();
    glyph.textureRect = getVar<symVarTextureRect, sf::IntRect>();
    return glyph;
}

template<>
Value Value::create(const sf::Font::Info& info)
{
    return rbFont::ourInfoDefinition.newObject(info.family);
}

template<>
Value Value::create(sf::Font::Info info)
{
    return rbFont::ourInfoDefinition.newObject(info.family);
}

template<>
Value Value::create(const sf::Glyph& glyph)
{
    return rbFont::ourGlyphDefinition.newObject(glyph.advance, glyph.bounds, glyph.textureRect);
}

template<>
Value Value::create(sf::Glyph glyph)
{
    return rbFont::ourGlyphDefinition.newObject(glyph.advance, glyph.bounds, glyph.textureRect);
}

}