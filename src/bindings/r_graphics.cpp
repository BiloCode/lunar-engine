#include <Engine/bindings/r_graphics.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

void ruby::bind_graphics(GraphicsCache& graphics)
{
   auto ref = Interpreter::bind_module("Graphics");
}
