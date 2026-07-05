#pragma once

#include <SFML/Graphics.hpp>

class Runtime
{
public:
   static void load();
   static void update();
   static bool running();

private:
   inline static sf::RenderWindow window = {};
   static void on_input(const std::optional<sf::Event>& event);
   static void on_resize(const std::optional<sf::Event>& event);
};
