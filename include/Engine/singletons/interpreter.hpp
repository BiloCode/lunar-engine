#include "interpreter.h"

#include <Engine/utils/debug.h>

namespace Debug = Engine::Debug;

template<typename T>
void Interpreter::bind_property(RClass* ref, const std::string& name, T* value)
{
   mrb_iv_set(mrb, mrb_obj_value(ref), mrb_intern_cstr(mrb, name.c_str()), mrb_cptr_value(mrb, value));
}

template<typename... Args>
mrb_value Interpreter::call(mrb_value receiver, const std::string& name, Args... args)
{
   auto result = mrb_funcall(mrb, receiver, name.c_str(), sizeof...(Args), args...);

   if (mrb->exc)
   {
      Debug::print_exception(mrb, "[Interpreter]: RubyCallException");
   }

   return result;
}