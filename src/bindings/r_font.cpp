#include <Engine/bindings/r_font.h>
#include <Engine/bindings/r_types.h>

namespace
{
   mrb_value font_new(mrb_state* mrb, mrb_value self)
   {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Font cannot be instantiated");
      return mrb_nil_value();
   }

   mrb_value font_size(mrb_state* mrb, mrb_value self)
   {
      auto font = static_cast<Font*>(mrb_data_get_ptr(mrb, self, &r_font_type));
      return mrb_int_value(mrb, font->size);
   }

   mrb_value font_size_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int size;
      mrb_get_args(mrb, "i", &size);
      auto font = static_cast<Font*>(mrb_data_get_ptr(mrb, self, &r_font_type));
      if (size < 1) {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "Font size expects an integer >= 1");
      }
      font->size = static_cast<unsigned int>(size);
      return mrb_nil_value();
   }
}

r_font::r_font(RubyLoader& ruby) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("Font");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   this->ruby.bind_singleton_method(ref, "new", font_new, MRB_ARGS_NONE());
   this->ruby.bind_instance_method(ref, "size", font_size, MRB_ARGS_NONE());
   this->ruby.bind_instance_method(ref, "size=", font_size_set, MRB_ARGS_REQ(1));
}
