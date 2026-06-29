#include <Engine/singletons/project.h>
#include <Engine/singletons/runtime.h>
#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/fonts_loader.h>
#include <Engine/resources/graphics_loader.h>
#include <Engine/bindings/r_font.h>
#include <Engine/bindings/r_fonts.h>
#include <Engine/bindings/r_color.h>
#include <Engine/bindings/r_audio.h>
#include <Engine/bindings/r_input.h>
#include <Engine/bindings/r_vector_int.h>
#include <Engine/bindings/r_vector_float.h>
#include <Engine/bindings/r_bitmap.h>
#include <Engine/bindings/r_sprite.h>
#include <Engine/bindings/r_graphics.h>
#include <iostream>

int main()
{
   try {
      Project::load();
      Runtime::load();

      RubyLoader r_loader;
      FontsLoader f_loader("fonts");
      GraphicsLoader g_loader("graphics");

      FontsCache fonts = f_loader.get_cache();
      GraphicsCache graphics = g_loader.get_cache();

      r_loader.open();
      r_loader.preload();

      ruby::bind_font(r_loader);
      ruby::bind_input(r_loader);
      ruby::bind_color(r_loader);
      ruby::bind_audio(r_loader);
      ruby::bind_bitmap(r_loader);
      ruby::bind_sprite(r_loader);
      ruby::bind_fonts(r_loader, fonts);
      ruby::bind_graphics(r_loader, graphics);
      ruby::bind_vector_int(r_loader);
      ruby::bind_vector_float(r_loader);

      r_loader.initialize();

      while(Runtime::running())
      {
         Runtime::update();
      }

      r_loader.close();
   }
   catch(const std::exception& e) {
      std::cerr << e.what() << std::endl;
      std::cerr << "Exit with code 1" << std::endl;
      return EXIT_FAILURE;
   }

   std::cout << "Exit with code 0" << std::endl;
	return EXIT_SUCCESS;
}
