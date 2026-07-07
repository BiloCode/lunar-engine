#pragma once

#include <Engine/interfaces/renderable.h>
#include <vector>

class Renderer
{
public:
   static void attach(Renderable* element);
   static void detach(Renderable* element);
   //static void update(sf::RenderTarget& target);
   static void refresh();

private:
   inline static std::vector<Renderable*> elements = {};
   //static void draw(sf::RenderTarget& target);
   //static void draw_cleanup();
};
