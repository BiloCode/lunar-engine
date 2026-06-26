#include <Engine/bindings/r_fonts_cache.h>
#include <Engine/bindings/r_types.h>

namespace
{
   mrb_value fonts_cache_new(mrb_state* mrb, mrb_value self)
   {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Fonts cannot be instantiated");
      return mrb_nil_value();
   }

   mrb_value fonts_cache_operator(mrb_state* mrb, mrb_value self)
   {
      const char* key;
      mrb_get_args(mrb, "z", &key);
      auto f_class = mrb_class_get(mrb, "Font");
      auto f_cache = static_cast<FontsCache*>(mrb_data_get_ptr(mrb, self, &r_fonts_cache_type));
      auto f_font = new Font(f_cache->get(key));
      return mrb_obj_value(
         mrb_data_object_alloc(mrb, f_class, f_font, &r_font_type)
      );
   }
}

r_fonts_cache::r_fonts_cache(RubyLoader& ruby, FontsCache& fonts) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("FontsCache");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   this->ruby.bind_singleton_method(ref, "new", fonts_cache_new, MRB_ARGS_NONE());
   this->ruby.bind_instance_method(ref, "[]", fonts_cache_operator, MRB_ARGS_REQ(1));
   this->ruby.bind_global_variable("$fonts", mrb_obj_value(
      mrb_data_object_alloc(this->ruby.get_state(), ref, const_cast<FontsCache*>(&fonts), &r_fonts_cache_type)
   ));
}
