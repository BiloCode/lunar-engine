#pragma once

#include <mruby.h>

class Scene
{
public:
   static void update();
   static void set_current(const mrb_value& scene);
   static const mrb_value& get_current();

private:
   inline static mrb_value current = mrb_nil_value();
};
