#pragma once

#include <optional>
#include <Engine/core/color.h>

class Environment
{
public:
    static void update();
    static void set_background(Color color);

private:
    inline static std::optional<Color> color;
};