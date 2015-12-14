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

#ifndef RBSFML_VALUE_HEADER_
#define RBSFML_VALUE_HEADER_

#include <ruby.h>
#include <string>
#include <vector>

namespace rb
{
	template<typename Base, int MaxFunctions>
	class Module;
	class Object;

	enum class ValueType
	{
		None, Object, Class, Module,
		Float, String, Regexp, Array, 
		Hash, Struct, Bignum, File, 
		Data, Match, Complex, Rational,
		Nil, Bool, Symbol, Fixnum,
		Unknown
	};

	class Value
	{
	public:
		template<typename Type>
		static Value create(Type value);

		Value();
		explicit Value(VALUE value);
		explicit Value(const std::string& value);
		explicit Value(unsigned char value);
		explicit Value(int value);
		explicit Value(float value);
		explicit Value(long long int value);
		explicit Value(unsigned int value);
		explicit Value(bool value);
		explicit Value(rb::Object* object);
		explicit Value(const std::vector<Value>& collection);

		template<typename Base, int MaxFunctions>
		explicit Value(const Module<Base, MaxFunctions>& module);

		~Value();

		template<typename Type>
		Type to() const;

		ValueType getType() const;
		std::string getClassName() const;

		bool isKindOf(const Value& klass) const;

		bool isNil() const;
		bool isFrozen() const;

		bool equal(const Value& other) const;
		bool operator==(const Value& other) const;

		int getArrayLength() const;

		void freeze();

		template<const char* Name, typename ReturnType = Value, typename ...Args>
		ReturnType call(Args... args);

		template<const char* Name, typename ValueType>
		void setVar(ValueType value);
		template<const char* Name, typename ValueType = Value>
		ValueType getVar() const;

	private:
		void errorHandling(int rubyType) const;
		void errorHandling(int type1, int type2) const;

		VALUE myValue;
		mutable std::string myCachedStr;
		mutable std::vector<Value> myCachedArray;
	};

	extern Value Nil;
	extern Value True;
	extern Value False;

	template<>
	VALUE Value::to() const;

	template<>
	const Value& Value::to() const;
	template<>
	Value Value::to() const;

	template<>
	std::string Value::to() const;
	template<>
	const std::string& Value::to() const;

	template<>
	std::vector<Value> Value::to() const;
	template<>
	const std::vector<Value>& Value::to() const;

	template<>
	unsigned char Value::to() const;
	template<>
	int Value::to() const;
	template<>
	float Value::to() const;
	template<>
	long long int Value::to() const;
	template<>
	unsigned int Value::to() const;
	template<>
	bool Value::to() const;
}

#include "value.inc"

#endif // RBSFML_VALUE_HEADER_