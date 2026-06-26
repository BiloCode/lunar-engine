#pragma once

#include <string>

struct Settings
{
   std::string win_title;
   bool win_resizable;
   bool win_fullscreen;
   unsigned int screen_w;
   unsigned int screen_h;
   unsigned int viewport_w;
   unsigned int viewport_h;
   unsigned int fps;
   bool vsync;
   bool show_fps;
};
