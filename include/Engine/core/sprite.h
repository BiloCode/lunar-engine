#pragma once

#include <Engine/interfaces/renderable.h>
#include "bitmap.h"

class Sprite : public Renderable
{
public:
   Bitmap* bitmap = nullptr;
   Sprite();
   ~Sprite() override;
   void draw(sf::RenderTarget& target) override;

protected:
   void on_dispose() override;
};
