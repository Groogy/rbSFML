#include <ruby.h>
#include <string>

namespace rb
{
	class Value
	{
	public:
		Value();
		Value(VALUE value);
		Value(const std::string& value);
		~Value();

		template<typename Type>
		Type to() const;

	private:
		VALUE myValue;
		mutable std::string myCachedStr;
	};

	template<>
	VALUE Value::to() const;

	template<>
	std::string Value::to() const;

	template<>
	const std::string& Value::to() const;
}
