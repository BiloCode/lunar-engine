#pragma once

#include <SFML/Graphics.hpp>
#include <Engine/interfaces/disposable.h>
#include "bitmap.h"

class Sprite : public Disposable
{
public:
   Bitmap* bitmap;
   float x;
   float y;
   Sprite();
   ~Sprite();
   void draw(sf::RenderTarget& target);

protected:
   void on_dispose() override;
};
