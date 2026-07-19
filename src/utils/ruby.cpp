#include <Engine/utils/ruby.h>

int Engine::Ruby::to_int(mrb_state* mrb, mrb_value value)
{
    if (mrb_float_p(value)) {
        return static_cast<int>(mrb_float(value));
    }
    if (mrb_integer_p(value)) {
        return static_cast<int>(mrb_integer(value));
    }
    mrb_raise(mrb, E_TYPE_ERROR, "Expected int args");
    return 0;
}

float Engine::Ruby::to_float(mrb_state* mrb, mrb_value value)
{
    if (mrb_float_p(value)) {
        return static_cast<float>(mrb_float(value));
    }
    if (mrb_integer_p(value)) {
        return static_cast<float>(mrb_integer(value));
    }
    mrb_raise(mrb, E_TYPE_ERROR, "Expected float args");
    return 0.f;
}