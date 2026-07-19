#pragma once

#include <mruby.h>

namespace Engine::Ruby
{
   int to_int(mrb_state* mrb, mrb_value value);
   float to_float(mrb_state* mrb, mrb_value value);
}