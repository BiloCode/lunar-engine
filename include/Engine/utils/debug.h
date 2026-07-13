#pragma once

#include <mruby.h>

namespace Engine::Debug
{
    template<typename... Args> void print(const Args&... args);
    template<typename... Args> void print_error(const Args&... args);
    template<typename... Args> void print_exception(const Args&... args);
    template<typename... Args> void print_exception(mrb_state* mrb, const Args&... args);
};

#include "debug.hpp"