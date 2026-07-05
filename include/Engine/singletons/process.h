#pragma once

#include <SFML/Graphics.hpp>

class Process
{
public:
   static void update();
   static float get_delta_time();
   static float get_frame_rate();

private:
   inline static sf::Clock clock = {};
   inline static float delta_time = 0.f;
   inline static float frame_rate = 0.f;
};
