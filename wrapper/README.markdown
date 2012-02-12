This is a C++ interface for Ruby, mainly inspired by Rice, but using powerful
features from C++11 (`-std=c++0x` on gcc). The basic idea is to provide a
easy-to-use API, wrapping Ruby's C API. For example:

With Ruby:

	p Object.new
	A = Class.new
	puts A.new.object_id

With C Ruby:

	rb_funcall2(rb_mKernel, rb_intern("p"), 1, (VALUE[]){rb_class_new_instance(0, NULL, rb_cObject)});
	VALUE rb_cA = rb_define_class("A", rb_cObject);
	rb_funcall2(rb_mKernel, rb_intern("puts"), 1, (VALUE[]){rb_funcall2(rb_mKernel, rb_class_new_instance(0, NULL, rb_cObject), rb_intern("object_id"), 0, NULL});

With C++ Ruby:

	p(cObject.New());
	Class A = Class::Define("A");
	puts(A.New().object_id());

As you can see, the C++ version is much closer to the Ruby one. It is also
smaller and easier to read than the C one.

It was only tested with MRI 1.9.3 on Windows. To try by yourself just edit
`test.cpp` and run `rake`.