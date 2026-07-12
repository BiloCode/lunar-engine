#include <Engine/core/sprite.h>

#include <Engine/core/bitmap.h>
#include <Engine/singletons/runtime.h>
#include <Engine/singletons/renderer.h>

Sprite::Sprite()
{
   Renderer::attach(this);
}

Sprite::~Sprite()
{
   dispose();
}

void Sprite::draw()
{
   if (bitmap != nullptr) {
      SDL_Texture* texture = bitmap->get_texture();
      SDL_FRect dst;
      dst.x = x;
      dst.y = y;
      dst.w = bitmap->get_width();
      dst.h = bitmap->get_height();
      SDL_RenderTexture(Runtime::get_renderer(), texture, nullptr, &dst);
   }
}

void Sprite::on_dispose()
{
   bitmap = nullptr;
}
