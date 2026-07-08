#include <Engine/singletons/timestamp.h>

void Timestamp::update()
{
   frame_last_time = frame_current_time;
   frame_current_time = SDL_GetPerformanceCounter();
}

float Timestamp::get_delta_time()
{
   float dt = (float)(frame_current_time - frame_last_time) / (float)SDL_GetPerformanceFrequency();

   if (dt > 0.1f) {
      return 0.1f;
   }

   return dt;
}

float Timestamp::get_frame_rate()
{
   float dt = get_delta_time();

   if (dt > 0.0f) {
      return 1.f / dt;
   }

   return 0.f;
}
