#include <Engine/singletons/project.h>
#include <Engine/singletons/runtime.h>
#include <Engine/singletons/interpreter.h>
#include <Engine/resources/fonts_loader.h>
#include <Engine/resources/graphics_loader.h>
#include <Engine/bindings/r_font.h>
#include <Engine/bindings/r_fonts.h>
#include <Engine/bindings/r_color.h>
#include <Engine/bindings/r_audio.h>
#include <Engine/bindings/r_input.h>
#include <Engine/bindings/r_kernel.h>
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
      Interpreter::load();

      FontsLoader f_loader("fonts");
      GraphicsLoader g_loader("graphics");

      FontsCache fonts = f_loader.get_cache();
      GraphicsCache graphics = g_loader.get_cache();

      ruby::bind_font();
      ruby::bind_input();
      ruby::bind_color();
      ruby::bind_audio();
      ruby::bind_bitmap();
      ruby::bind_sprite();
      ruby::bind_kernel();
      ruby::bind_fonts(fonts);
      ruby::bind_graphics(graphics);
      ruby::bind_vector_int();
      ruby::bind_vector_float();

      Interpreter::start();

      while(Runtime::running())
      {
         Runtime::update();
      }

      Interpreter::finish();
   }
   catch(const std::exception& e) {
      std::cerr << e.what() << std::endl;
      std::cerr << "Exit with code 1" << std::endl;
      return EXIT_FAILURE;
   }

   std::cout << "Exit with code 0" << std::endl;
	return EXIT_SUCCESS;
}
