#pragma once

#include <SFML/Graphics.hpp>

class Runtime
{
public:
   static void load();
   static void update();
   static bool running();

private:
   static sf::RenderWindow window;
};
