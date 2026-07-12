#pragma once

#include <vector>

class Renderable;

class Renderer
{
public:
   static void attach(Renderable* element);
   static void detach(Renderable* element);
   static void update();
   static void refresh();

private:
   inline static std::vector<Renderable*> elements = {};
   static void draw();
   static void draw_cleanup();
};
