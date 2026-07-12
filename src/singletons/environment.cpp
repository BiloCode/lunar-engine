#include <Engine/singletons/environment.h>

#include <Engine/singletons/runtime.h>

void Environment::update()
{
    if (color.has_value()) {
        SDL_SetRenderDrawColor(Runtime::get_renderer(), color->r, color->g, color->b, color->a);
        SDL_RenderClear(Runtime::get_renderer());
    }
}

void Environment::set_background(Color color)
{
    Environment::color = color;
}