#include <Engine/singletons/runtime.h>
#include <Engine/singletons/project.h>
#include <string>
#include <iostream>

void Runtime::load()
{
   if (!SDL_Init(SDL_INIT_VIDEO)) {
      throw std::runtime_error("[Runtime]: Failed to initialize SDL: " + std::string(SDL_GetError()));
   }

   auto screen_w = Project::get_settings<unsigned int>("screen_w", 1280);
   auto screen_h = Project::get_settings<unsigned int>("screen_h", 720);
   auto viewport_w = Project::get_settings<unsigned int>("viewport_w", 640);
   auto viewport_h = Project::get_settings<unsigned int>("viewport_h", 480);
   auto win_title = Project::get_settings<std::string>("win_title", "Lunar Engine");
   auto win_resizable = Project::get_settings<bool>("win_resizable", true);
   auto win_fullscreen = Project::get_settings<bool>("win_fullscreen", false);
   auto fps = Project::get_settings<int>("fps", 60);
   auto vsync = Project::get_settings<bool>("vsync", true);

   window = SDL_CreateWindow(win_title.c_str(), screen_w, screen_h, SDL_WINDOW_HIGH_PIXEL_DENSITY);

   if (!window) {
      throw std::runtime_error("[Runtime]: Failed to create SDL window: " + std::string(SDL_GetError()));
   }

   SDL_SetWindowResizable(window, win_resizable);
   SDL_SetWindowFullscreen(window, win_fullscreen);

   renderer = SDL_CreateRenderer(window, nullptr);

   if (!renderer) {
      throw std::runtime_error("[Runtime]: Failed to create SDL renderer: " + std::string(SDL_GetError()));
   }

   SDL_SetRenderVSync(renderer, vsync);
   SDL_SetRenderLogicalPresentation(renderer, viewport_w, viewport_h, SDL_LOGICAL_PRESENTATION_LETTERBOX);

   is_running = true;
}

void Runtime::update()
{
   SDL_Event event;

   while (SDL_PollEvent(&event))
   {
      if (event.type == SDL_EVENT_QUIT) {
         is_running = false;
      }
   }

   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);
}

void Runtime::finish()
{
   if (renderer) {
      SDL_DestroyRenderer(renderer);
      renderer = nullptr;
   }
   
   if (window) {
      SDL_DestroyWindow(window);
      window = nullptr;
   }

   SDL_Quit();
}

bool Runtime::running()
{
   return is_running;
}

void Runtime::on_input(const SDL_Event& event)
{
}

void Runtime::on_resize(const SDL_Event& event)
{
}
