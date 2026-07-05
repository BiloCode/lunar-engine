#include <Engine/singletons/room.h>
#include <Engine/singletons/process.h>
#include <Engine/singletons/interpreter.h>

void Room::update(sf::RenderTarget& target)
{
   if (!mrb_nil_p(current)) {
      Interpreter::call(current, "process", mrb_float_value(Interpreter::get_state(), Process::get_delta_time()));
   }
}

const mrb_value& Room::get_current()
{
   return Room::current;
}

void Room::set_current(const mrb_value& room)
{
   Room::current = room;
}
