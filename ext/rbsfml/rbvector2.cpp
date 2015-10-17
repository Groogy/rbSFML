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

#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"

namespace 
{
	constexpr char symVarX[] = "@x";
	constexpr char symVarY[] = "@y";
}

rbVector2Class rbVector2::ourDefinition;

void rbVector2::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbVector2Class::defineClassUnder<rb::RubyObjAllocator>("Vector2", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbVector2::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbVector2::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbVector2::marshalDump);
	ourDefinition.defineMethod<2>("marshal_load", &rbVector2::marshalLoad);
}

rb::Value rbVector2::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	switch( args.size() )
    {
        case 0:
        	self.setVar<symVarX>(0);
        	self.setVar<symVarY>(0);
            break;
        case 1:
        	rbVector2::initializeCopy(self, args[0]);
            break;
        case 2:
        	self.setVar<symVarX>(args[0]);
        	self.setVar<symVarY>(args[0]);
            break;
        default:
        	break;
            //INVALID_ARGUMENT_LIST( argc, "0..2" );
    }

	return self;
}

rb::Value rbVector2::initializeCopy(const rb::Value& self, const rb::Value& value)
{
	std::string type = self.getClassName();
	rb::raise(rb::RuntimeError, "%s can not be copied!", type.c_str());
	return rb::Nil;
}

rb::Value rbVector2::marshalDump(const rb::Value& self)
{
	std::string type = self.getClassName();
	rb::raise(rb::TypeError, "can't dump %s", type.c_str());
	return rb::Nil;
}

rb::Value rbVector2::marshalLoad(const rb::Value& self)
{
	std::string type = self.getClassName();
	rb::raise(rb::TypeError, "can't dump %s", type.c_str());
	return rb::Nil;
}
