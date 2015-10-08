namespace rb
{

template<typename Type>
Type Value::to() const
{
	static_assert(false, "Conversion has not been defined!");
}

}