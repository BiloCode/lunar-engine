#pragma once

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/compile.h>
#include <mruby/variable.h>
#include <string>
#include <vector>
#include <filesystem>

class RubyLoader
{
public:
   void open();
   void close();
   void preload();
   void initialize();
   mrb_state* get_state() const;
   RClass* get_class(const std::string& name) const;
   RClass* get_module(const std::string& name) const;
   RClass* bind_class(const std::string& name);
   RClass* bind_module(const std::string& name);
   void bind_const(RClass* ref, const std::string& name, mrb_value value);
   void bind_instance_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec);
   void bind_singleton_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec);
   void bind_global_const(const std::string& name, mrb_value value);
   void bind_global_method(const std::string& name, mrb_func_t method, mrb_aspec aspec);
   void bind_global_variable(const std::string& name, mrb_value value);

private:
   mrb_state* mrb;
   std::vector<std::filesystem::path> scripts_paths;
};
