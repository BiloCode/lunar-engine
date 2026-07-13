#include <Engine/singletons/interpreter.h>

#include <fstream>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/compile.h>
#include <mruby/variable.h>
#include <Engine/utils/path.h>
#include <Engine/utils/debug.h>

namespace Path = Engine::Path;
namespace Debug = Engine::Debug;

void Interpreter::load()
{
   if (mrb != nullptr)
   {
      Debug::print_error("[Interpreter]: Ruby runtime already initialized");
      return;
   }

   auto basepath = Path::get_executable_dir() / "scripts/load_order.txt";

   if (!std::filesystem::exists(basepath))
   {
      Debug::print_exception("[Interpreter]: Failed to load scripts/load_order.txt");
   }

   std::fstream file(basepath);

   if (file.is_open())
   {
      std::string line;

      while (std::getline(file, line)) {
         if (line.empty()) {
            continue;
         }
         auto path = Path::get_executable_dir() / ("scripts/" + line);
         mrb_paths.push_back(path);
      }

      file.close();
   }

   mrb = mrb_open();
}

void Interpreter::start()
{
   if (mrb_paths.empty())
   {
      Debug::print_error("[Interpreter]: No scripts to load");
      return;
   }

   for (const auto& path : mrb_paths)
   {
      FILE* file = fopen(path.string().c_str(), "r");

      if (!file) {
         Debug::print_error("[Interpreter]: Script ", path.filename(), " error");
         continue;
      }

      mrb_load_file(mrb, file);

      if (mrb->exc) {
         Debug::print_exception(mrb, "[Interpreter]: LoadFileException");
      }
   }
}

void Interpreter::finish()
{
   if (mrb != nullptr)
   {
      mrb_close(mrb);
   }
}

mrb_state* Interpreter::get_state()
{
   return mrb;
}

RClass* Interpreter::get_class(const std::string& name)
{
   return mrb_class_get(mrb, name.c_str());
}

RClass* Interpreter::get_module(const std::string& name)
{
   return mrb_module_get(mrb, name.c_str());
}

RClass* Interpreter::bind_class(const std::string& name)
{
   struct RClass* klass = mrb_define_class(mrb, name.c_str(), mrb->object_class);
   return klass;
}

RClass* Interpreter::bind_module(const std::string& name)
{
   struct RClass* module = mrb_define_module(mrb, name.c_str());
   return module;
}

void Interpreter::bind_const(RClass* ref, const std::string& name, mrb_value value)
{
   mrb_define_const(mrb, ref, name.c_str(), value);
}

void Interpreter::bind_global_const(const std::string& name, mrb_value value)
{
   mrb_define_global_const(mrb, name.c_str(), value);
}

void Interpreter::bind_global_method(const std::string& name, mrb_func_t method, mrb_aspec aspec)
{
   struct RClass* kernel = mrb->kernel_module;
   mrb_define_module_function(mrb, kernel, name.c_str(), method, aspec);
}

void Interpreter::bind_instance_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec)
{
   mrb_define_method(mrb, ref, name.c_str(), method, aspec);
}

void Interpreter::bind_singleton_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec)
{
   mrb_define_class_method(mrb, ref, name.c_str(), method, aspec);
}

void Interpreter::bind_global_variable(const std::string& name, mrb_value value)
{
   mrb_gv_set(mrb, mrb_intern_cstr(mrb, name.c_str()), value);
}
