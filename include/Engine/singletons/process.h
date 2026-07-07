#pragma once

#include <SDL3/SDL.h>

class Process
{
public:
   static void update();
   static float get_delta_time();
   static float get_frame_rate();

private:
   inline static Uint64 frame_last_time = 0u;
   inline static Uint64 frame_current_time = 0u;
};
