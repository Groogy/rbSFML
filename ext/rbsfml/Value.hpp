#include <ruby.h>
#include <string>

namespace rb
{
	class Value
	{
	public:
		Value();
		explicit Value(VALUE value);
		explicit Value(const std::string& value);
		~Value();

		template<typename Type>
		Type to() const;

	private:
		void errorHandling(int rubyType) const;

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
