#pragma once

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class Render
{
public:
   static void add(Sprite* sprite);
   static void remove(Sprite* sprite);
   static void update(sf::RenderTarget& target);

private:
   static std::vector<Sprite*> sprites;
};
