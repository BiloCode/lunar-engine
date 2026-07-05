#include <Engine/singletons/process.h>

void Process::update()
{
   delta_time = clock.restart().asSeconds();
   frame_rate = 1.f / delta_time;
}

float Process::get_delta_time()
{
   return delta_time;
}

float Process::get_frame_rate()
{
   return frame_rate;
}
