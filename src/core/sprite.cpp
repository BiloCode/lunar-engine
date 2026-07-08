#include <Engine/core/sprite.h>
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
}

void Sprite::on_dispose()
{
   bitmap = nullptr;
}
