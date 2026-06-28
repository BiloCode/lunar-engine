#pragma once

#include <SFML/Graphics.hpp>
#include "bitmap.h"

class Sprite
{
public:
   Bitmap* bitmap;
   float x;
   float y;
   Sprite();
   ~Sprite();
   void draw(sf::RenderTarget& target);
   void dispose();
};
