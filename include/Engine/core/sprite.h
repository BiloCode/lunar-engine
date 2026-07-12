#pragma once

#include <Engine/interfaces/renderable.h>

class Bitmap;

class Sprite : public Renderable
{
public:
   Bitmap* bitmap = nullptr;
   Sprite();
   ~Sprite() override;
   void draw() override;

protected:
   void on_dispose() override;
};
