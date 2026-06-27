#include <Engine/resources/ruby_loader.h>
#include <Engine/utils/paths.h>
#include <fstream>
#include <iostream>

namespace Paths = Engine::Paths;

void RubyLoader::open()
{
   mrb = mrb_open();
}

void RubyLoader::close()
{
   mrb_close(mrb);
}

void RubyLoader::preload()
{
   auto order_path = Paths::get_executable_dir() / "scripts/load_order.txt";

   if (!std::filesystem::exists(order_path)) {
      std::cerr << "[RubyLoader]: Failed to preload Ruby runtime" << std::endl;
      return;
   }

   std::fstream order_file(order_path);

   if (order_file.is_open()) {
      std::string line;

      while (std::getline(order_file, line))
      {
         if (line.empty()) {
            continue;
         }
         auto path = Paths::get_executable_dir() / ("scripts/" + line);
         scripts_paths.push_back(path);
      }

      order_file.close();
   }
}

void RubyLoader::initialize()
{
   if (scripts_paths.empty()) {
      std::cerr << "[RubyLoader]: Failed to initialize Ruby runtime" << std::endl;
      return;
   }

   for (const auto& path : scripts_paths)
   {
      FILE* file = fopen(path.string().c_str(), "r");

      if (!file) {
         std::cerr << "[RubyLoader]: Script " << path.filename() << " error" << "\n";
         continue;
      }

      mrb_load_file(mrb, file);

      if (mrb->exc)
      {
         mrb_value exc = mrb_obj_value(mrb->exc);
         std::cout << "[RubyLoader]: " << mrb_str_to_cstr(mrb, mrb_inspect(mrb, exc)) << std::endl;
      }
   }
}

mrb_state* RubyLoader::get_state() const
{
   return mrb;
}

RClass* RubyLoader::get_class(const std::string& name) const
{
   return mrb_class_get(mrb, name.c_str());
}

RClass* RubyLoader::get_module(const std::string& name) const
{
   return mrb_module_get(mrb, name.c_str());
}

RClass* RubyLoader::bind_class(const std::string& name)
{
   struct RClass* klass = mrb_define_class(mrb, name.c_str(), mrb->object_class);
   return klass;
}

RClass* RubyLoader::bind_module(const std::string& name)
{
   struct RClass* module = mrb_define_module(mrb, name.c_str());
   return module;
}

void RubyLoader::bind_const(RClass* ref, const std::string& name, mrb_value value)
{
   mrb_define_const(mrb, ref, name.c_str(), value);
}

void RubyLoader::bind_global_const(const std::string& name, mrb_value value)
{
   mrb_define_global_const(mrb, name.c_str(), value);
}

void RubyLoader::bind_global_method(const std::string& name, mrb_func_t method, mrb_aspec aspec)
{
   struct RClass* kernel = mrb->kernel_module;
   mrb_define_module_function(mrb, kernel, name.c_str(), method, aspec);
}

void RubyLoader::bind_instance_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec)
{
   mrb_define_method(mrb, ref, name.c_str(), method, aspec);
}

void RubyLoader::bind_singleton_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec)
{
   mrb_define_class_method(mrb, ref, name.c_str(), method, aspec);
}

void RubyLoader::bind_global_variable(const std::string& name, mrb_value value)
{
   mrb_gv_set(mrb, mrb_intern_cstr(mrb, name.c_str()), value);
}
