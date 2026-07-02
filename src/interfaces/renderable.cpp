#include <Engine/interfaces/renderable.h>
#include <Engine/singletons/renderer.h>

float Renderable::get_x() const
{
   return x;
}

float Renderable::get_y() const
{
   return y;
}

float Renderable::get_z() const
{
   return z;
}

void Renderable::set_x(float x)
{
   this->x = x;
}

void Renderable::set_y(float y)
{
   this->y = y;
}

void Renderable::set_z(float z)
{
   this->z = z;
   Renderer::refresh();
}

bool Renderable::is_visible() const
{
   return visible;
}

void Renderable::set_visible(bool visible)
{
   this->visible = visible;
}
