#include "debug.h"

#include <SDL3/SDL.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <sstream>
#include <iostream>
#include <stdexcept>

template<typename... Args>
void Engine::Debug::print(const Args&... args)
{
   (std::cout << ... << args) << "\n";
}

template<typename... Args>
void Engine::Debug::print_error(const Args&... args)
{
   (std::cerr << ... << args) << "\n";
}

template<typename... Args>
void Engine::Debug::print_exception(const Args&... args)
{
   std::ostringstream stream;
   (stream << ... << args);
   throw std::runtime_error(stream.str());
}

template<typename... Args>
void Engine::Debug::print_exception(mrb_state* mrb, const Args&... args)
{
   mrb_value exc = mrb_obj_value(mrb->exc);
   mrb_value exc_class = mrb_funcall(mrb, exc, "class", 0);
   mrb_value exc_error = mrb_funcall(mrb, exc_class, "to_s", 0);
   mrb_value exc_message = mrb_funcall(mrb, exc, "message", 0);
   mrb_value exc_backtrace = mrb_funcall(mrb, exc, "backtrace", 0);

   std::ostringstream stream;

   stream << "\n";
   stream << "============================================================" << "\n";
   (stream << ... << args) << "\n";
   stream << "============================================================" << "\n";
   stream << "Type      : " << mrb_str_to_cstr(mrb, exc_error) << '\n';
   stream << "Message   : " << mrb_str_to_cstr(mrb, exc_message) << '\n';

   if (mrb_array_p(exc_backtrace))
   {
      stream << "Backtrace : " << "\n";

      for (mrb_int i = 0; i < RARRAY_LEN(exc_backtrace); ++i)
      {
         mrb_value line = mrb_ary_ref(mrb, exc_backtrace, i);
         stream << "  at " << mrb_str_to_cstr(mrb, line) << '\n';
      }
   }

   stream << "============================================================" << "\n";

   mrb->exc = nullptr;

   throw std::runtime_error(stream.str());
}