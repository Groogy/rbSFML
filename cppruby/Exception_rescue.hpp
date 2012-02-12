#pragma once

namespace rb
{
    
    class Exception;
    
    namespace priv
    {
        
        VALUE rescue_rescue_block(VALUE data, VALUE ex)
        {
            VALUE* out = (VALUE*)data;
            *out = ex;
            return Qnil;
        }
        
        template<typename RetT, RetT(*Func)()>
        VALUE rescue_begin_body(VALUE data)
        {
            void** ptr = (void**)data;
            RetT* out = reinterpret_cast<RetT*>(ptr[0]);
            *out = Func();
            return Qnil;
        }
        
        template<typename RetT, typename Arg1T, RetT(*Func)(Arg1T)>
        VALUE rescue_begin_body(VALUE data)
        {
            void** ptr = (void**)data;
            RetT* out = reinterpret_cast<RetT*>(ptr[0]);
            Arg1T* arg1 = reinterpret_cast<Arg1T*>(ptr[1]);
            *out = Func(*arg1);
            return Qnil;
        }
        
        template<typename RetT, typename Arg1T, typename Arg2T, RetT(*Func)(Arg1T, Arg2T)>
        VALUE rescue_begin_body(VALUE data)
        {
            void** ptr = (void**)data;
            RetT* out = reinterpret_cast<RetT*>(ptr[0]);
            Arg1T* arg1 = reinterpret_cast<Arg1T*>(ptr[1]);
            Arg2T* arg2 = reinterpret_cast<Arg2T*>(ptr[2]);
            *out = Func(*arg1, *arg2);
            return Qnil;
        }
        
        template<typename RetT, typename Arg1T, typename Arg2T, typename Arg3T, RetT(*Func)(Arg1T, Arg2T, Arg3T)>
        VALUE rescue_begin_body(VALUE data)
        {
            void** ptr = (void**)data;
            RetT* out = reinterpret_cast<RetT*>(ptr[0]);
            Arg1T* arg1 = reinterpret_cast<Arg1T*>(ptr[1]);
            Arg2T* arg2 = reinterpret_cast<Arg2T*>(ptr[2]);
            Arg3T* arg3 = reinterpret_cast<Arg3T*>(ptr[3]);
            *out = Func(*arg1, *arg2, *arg3);
            return Qnil;
        }
        
        template<typename RetT, typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, RetT(*Func)(Arg1T, Arg2T, Arg3T, Arg4T)>
        VALUE rescue_begin_body(VALUE data)
        {
            void** ptr = (void**)data;
            RetT* out = reinterpret_cast<RetT*>(ptr[0]);
            Arg1T* arg1 = reinterpret_cast<Arg1T*>(ptr[1]);
            Arg2T* arg2 = reinterpret_cast<Arg2T*>(ptr[2]);
            Arg3T* arg3 = reinterpret_cast<Arg3T*>(ptr[3]);
            Arg4T* arg4 = reinterpret_cast<Arg4T*>(ptr[4]);
            *out = Func(*arg1, *arg2, *arg3, *arg4);
            return Qnil;
        }
        
        template<typename RetT, RetT(*Func)()>
        void rescue(RetT* out)
        {
            auto f1 = rescue_begin_body<RetT, Func>;
            auto f2 = rescue_rescue_block;
            void* data[1];
            data[0] = reinterpret_cast<void*>(out);
            VALUE ex = Qnil;
            rb_rescue2((VALUE(*)(...))f1, (VALUE)data, (VALUE(*)(...))f2, (VALUE)&ex, rb_eException, 0);
            if (ex != Qnil)
                throw Exception(ex);
        }
        
        template<typename RetT, typename Arg1T, RetT(*Func)(Arg1T)>
        void rescue(RetT* out, Arg1T* arg1)
        {
            auto f1 = rescue_begin_body<RetT, Arg1T, Func>;
            auto f2 = rescue_rescue_block;
            void* data[2];
            data[0] = reinterpret_cast<void*>(out);
            data[1] = reinterpret_cast<void*>(arg1);
            VALUE ex = Qnil;
            rb_rescue2((VALUE(*)(...))f1, (VALUE)data, (VALUE(*)(...))f2, (VALUE)&ex, rb_eException, 0);
            if (ex != Qnil)
                throw Exception(ex);
        }
        
        template<typename RetT, typename Arg1T, typename Arg2T, RetT(*Func)(Arg1T, Arg2T)>
        void rescue(RetT* out, Arg1T* arg1, Arg2T* arg2)
        {
            auto f1 = rescue_begin_body<RetT, Arg1T, Arg2T, Func>;
            auto f2 = rescue_rescue_block;
            void* data[3];
            data[0] = reinterpret_cast<void*>(out);
            data[1] = reinterpret_cast<void*>(arg1);
            data[2] = reinterpret_cast<void*>(arg2);
            VALUE ex = Qnil;
            rb_rescue2((VALUE(*)(...))f1, (VALUE)data, (VALUE(*)(...))f2, (VALUE)&ex, rb_eException, 0);
            if (ex != Qnil)
                throw Exception(ex);
        }
        
        template<typename RetT, typename Arg1T, typename Arg2T, typename Arg3T, RetT(*Func)(Arg1T, Arg2T, Arg3T)>
        void rescue(RetT* out, Arg1T* arg1, Arg2T* arg2, Arg3T* arg3)
        {
            auto f1 = rescue_begin_body<RetT, Arg1T, Arg2T, Arg3T, Func>;
            auto f2 = rescue_rescue_block;
            void* data[4];
            data[0] = reinterpret_cast<void*>(out);
            data[1] = reinterpret_cast<void*>(arg1);
            data[2] = reinterpret_cast<void*>(arg2);
            data[3] = reinterpret_cast<void*>(arg3);
            VALUE ex = Qnil;
            rb_rescue2((VALUE(*)(...))f1, (VALUE)data, (VALUE(*)(...))f2, (VALUE)&ex, rb_eException, 0);
            if (ex != Qnil)
                throw Exception(ex);
        }
        
        template<typename RetT, typename Arg1T, typename Arg2T, typename Arg3T, typename Arg4T, RetT(*Func)(Arg1T, Arg2T, Arg3T, Arg4T)>
        void rescue(RetT* out, Arg1T* arg1, Arg2T* arg2, Arg3T* arg3, Arg4T* arg4)
        {
            auto f1 = rescue_begin_body<RetT, Arg1T, Arg2T, Arg3T, Arg4T, Func>;
            auto f2 = rescue_rescue_block;
            void* data[5];
            data[0] = reinterpret_cast<void*>(out);
            data[1] = reinterpret_cast<void*>(arg1);
            data[2] = reinterpret_cast<void*>(arg2);
            data[3] = reinterpret_cast<void*>(arg3);
            data[4] = reinterpret_cast<void*>(arg4);
            VALUE ex = Qnil;
            rb_rescue2((VALUE(*)(...))f1, (VALUE)data, (VALUE(*)(...))f2, (VALUE)&ex, rb_eException, 0);
            if (ex != Qnil)
                throw Exception(ex);
        }
        
    }
}
