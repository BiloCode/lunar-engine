#pragma once

#include <SDL3/SDL.h>

class Runtime
{
public:
   static void start();
   static void update();
   static void finish();
   static bool running();
   static SDL_Window* get_window();
   static SDL_Renderer* get_renderer();

private:
   inline static bool is_running = false;
   inline static SDL_Window* window = nullptr;
   inline static SDL_Renderer* renderer = nullptr;
};
