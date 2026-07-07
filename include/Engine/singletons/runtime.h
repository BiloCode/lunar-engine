#pragma once

#include <SDL3/SDL.h>

class Runtime
{
public:
   static void load();
   static void update();
   static void finish();
   static bool running();

private:
   inline static bool is_running = false;
   inline static SDL_Window* window = nullptr;
   inline static SDL_Renderer* renderer = nullptr;
   static void on_input(const SDL_Event& event);
   static void on_resize(const SDL_Event& event);
};
