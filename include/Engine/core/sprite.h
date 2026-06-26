#pragma once

#include <SFML/Graphics.hpp>
#include "bitmap.h"

class Sprite
{
public:
   Bitmap* bitmap; // memory leak!!
   float x;
   float y;
   Sprite() = default;
   void draw(sf::RenderTarget& render);
};
