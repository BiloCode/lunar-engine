#pragma once

#include <SFML/Graphics.hpp>
#include <mruby.h>
#include <vector>

class Scene
{
public:
   static mrb_value current;
   static void update(sf::RenderTarget& target);
};
