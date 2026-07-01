#pragma once

#include <SFML/Graphics.hpp>
#include <Engine/core/sprite.h>
#include <vector>
#include <algorithm>

class Canvas
{
public:
   static void add(Sprite* sprite);
   static void update(sf::RenderTarget& target);

private:
   static std::vector<Sprite*> elements;
   static void render(sf::RenderTarget& target);
   static void cleanup();
};
