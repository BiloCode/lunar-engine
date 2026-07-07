#include <Engine/singletons/process.h>

void Process::update()
{
   frame_last_time = frame_current_time;
   frame_current_time = SDL_GetPerformanceCounter();
}

float Process::get_delta_time()
{
   if (frame_last_time == 0u) {
      return 0.f;
   }

   float dt = (float)(frame_current_time - frame_last_time) / (float)SDL_GetPerformanceFrequency();

   if (dt > 0.1f) {
      return 0.1f;
   }

   return dt;
}

float Process::get_frame_rate()
{
   float dt = get_delta_time();

   if (dt > 0.0f) {
      return 1.f / dt;
   }

   return 0.f;
}
