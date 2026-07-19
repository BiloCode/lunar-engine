#include <Engine/bindings/r_vector_int.h>

#include <mruby.h>
#include <mruby/class.h>
#include <Engine/core/vector.h>
#include <Engine/utils/string.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace String = Engine::String;

namespace
{
   mrb_value vector_initialize(mrb_state* mrb, mrb_value self)
   {
      mrb_int args_c = mrb_get_argc(mrb);

      if (args_c == 0) {
         auto vector = new Vector<int>();
         mrb_data_init(self, vector, &r_vector2i_type);
      }
      else if (args_c == 1) {
         mrb_value obj;
         mrb_get_args(mrb, "o", &obj);
         if (DATA_TYPE(obj) == &r_vector2f_type) {
            auto v_vector = static_cast<Vector<float>*>(mrb_data_get_ptr(mrb, obj, &r_vector2f_type));
            auto n_vector = new Vector<int>(*v_vector);
            mrb_data_init(self, n_vector, &r_vector2i_type);
         }
         else if (DATA_TYPE(obj) == &r_vector2i_type) {
            auto v_vector = static_cast<Vector<int>*>(mrb_data_get_ptr(mrb, obj, &r_vector2i_type));
            auto n_vector = new Vector<int>(*v_vector);
            mrb_data_init(self, n_vector, &r_vector2i_type);
         }
         else {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "Unsupported type");
         }
      }
      else if (args_c == 2) {
         mrb_int x, y;
         mrb_get_args(mrb, "ii", &x, &y);
         auto vector = new Vector<int>(x, y);
         mrb_data_init(self, vector, &r_vector2i_type);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid arguments");
      }

      return self;
   }

   mrb_value vector_x(mrb_state* mrb, mrb_value self)
   {
      auto vector = static_cast<Vector<int>*>(mrb_data_get_ptr(mrb, self, &r_vector2i_type));
      return mrb_int_value(mrb, vector->x);
   }

   mrb_value vector_x_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int x;
      mrb_get_args(mrb, "i", &x);
      auto vector = static_cast<Vector<int>*>(mrb_data_get_ptr(mrb, self, &r_vector2i_type));
      vector->x = x;
      return mrb_nil_value();
   }

   mrb_value vector_y(mrb_state* mrb, mrb_value self)
   {
      auto vector = static_cast<Vector<int>*>(mrb_data_get_ptr(mrb, self, &r_vector2i_type));
      return mrb_int_value(mrb, vector->y);
   }

   mrb_value vector_y_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int y;
      mrb_get_args(mrb, "i", &y);
      auto vector = static_cast<Vector<int>*>(mrb_data_get_ptr(mrb, self, &r_vector2i_type));
      vector->y = y;
      return mrb_nil_value();
   }

   mrb_value vector_to_string(mrb_state* mrb, mrb_value self)
   {
      auto vector = static_cast<Vector<int>*>(mrb_data_get_ptr(mrb, self, &r_vector2i_type));
      auto output = String::format_object("#<Vector2i>", {
         { "x", std::to_string(vector->x) },
         { "y", std::to_string(vector->y) }
      });
      return mrb_str_new_cstr(mrb, output.c_str());
   }
}

void ruby::bind_vector_int()
{
   auto ref = Interpreter::bind_class("Vector2i");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_instance_method(ref, "initialize", vector_initialize, MRB_ARGS_ARG(0, 2));
   Interpreter::bind_instance_method(ref, "x", vector_x, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "x=", vector_x_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "y", vector_y, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "y=", vector_y_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "to_s", vector_to_string, MRB_ARGS_NONE());
}
