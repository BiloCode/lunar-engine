#include <Engine/singletons/interpreter.h>
#include <Engine/utils/path.h>
#include <fstream>
#include <iostream>

namespace Path = Engine::Path;

void Interpreter::load()
{
   if (mrb != nullptr) {
      std::cerr << "[Interpreter]: Ruby runtime already initialized" << std::endl;
      return;
   }

   auto basepath = Path::get_executable_dir() / "scripts/load_order.txt";

   if (!std::filesystem::exists(basepath)) {
      throw std::runtime_error("[Interpreter]: Failed to load scripts/load_order.txt");
   }

   std::fstream file(basepath);

   if (file.is_open()) {
      std::string line;

      while (std::getline(file, line))
      {
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
   if (mrb_paths.empty()) {
      std::cerr << "[Interpreter]: No scripts to load" << std::endl;
      return;
   }

   for (const auto& path : mrb_paths)
   {
      FILE* file = fopen(path.string().c_str(), "r");

      if (!file) {
         std::cerr << "[Interpreter]: Script " << path.filename() << " error" << "\n";
         continue;
      }

      mrb_load_file(mrb, file);

      if (mrb->exc)
      {
         mrb_value exc = mrb_obj_value(mrb->exc);
         std::cout << "[Interpreter]: " << mrb_str_to_cstr(mrb, mrb_inspect(mrb, exc)) << std::endl;
         mrb->exc = nullptr;
         throw std::runtime_error("[Interpreter]: #<InterpreterLoadFileException>");
      }
   }
}

void Interpreter::finish()
{
   if (mrb != nullptr) {
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
