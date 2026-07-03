#include "interpreter.h"
#include <iostream>

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
      mrb_value exc = mrb_obj_value(mrb->exc);
      std::cout << "[Interpreter]: " << mrb_str_to_cstr(mrb, mrb_inspect(mrb, exc)) << std::endl;
      mrb->exc = nullptr;
      throw std::runtime_error("[Interpreter]: #<InterpreterCallException>");
   }

   return result;
}
