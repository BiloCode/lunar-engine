#pragma once

#include <SFML/Graphics.hpp>
#include <mruby.h>
#include <vector>

class Room
{
public:
   static void update(sf::RenderTarget& target);
   static void set_current(const mrb_value& room);
   static const mrb_value& get_current();

private:
   inline static mrb_value current = mrb_nil_value();
};
