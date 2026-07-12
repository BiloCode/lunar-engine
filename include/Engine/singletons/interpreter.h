#pragma once

#include <mruby.h>
#include <string>
#include <vector>
#include <filesystem>

class Interpreter
{
public:
   static void load();
   static void start();
   static void finish();
   static mrb_state* get_state();
   static RClass* get_class(const std::string& name);
   static RClass* get_module(const std::string& name);
   static RClass* bind_class(const std::string& name);
   static RClass* bind_module(const std::string& name);
   static void bind_const(RClass* ref, const std::string& name, mrb_value value);
   static void bind_instance_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec);
   static void bind_singleton_method(RClass* ref, const std::string& name, mrb_func_t method, mrb_aspec aspec);
   static void bind_global_const(const std::string& name, mrb_value value);
   static void bind_global_method(const std::string& name, mrb_func_t method, mrb_aspec aspec);
   static void bind_global_variable(const std::string& name, mrb_value value);
   template<typename T> static void bind_property(RClass* ref, const std::string& name, T* value);
   template<typename... Args> static mrb_value call(mrb_value ref, const std::string& name, Args... args);

private:
   inline static mrb_state* mrb = nullptr;
   inline static std::vector<std::filesystem::path> mrb_paths = {};
};

#include "interpreter.hpp"
