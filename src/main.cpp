#include <Engine/singletons/project.h>
#include <Engine/singletons/runtime.h>
#include <Engine/singletons/timestamp.h>
#include <Engine/singletons/interpreter.h>
#include <Engine/resources/font_manager.h>
#include <Engine/resources/texture_manager.h>
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
#include <Engine/bindings/r_texture.h>
#include <Engine/bindings/r_textures.h>
#include <iostream>

int main()
{
   try {
      Project::load();
      Interpreter::load();

      auto fonts = FontManager();
      auto textures = TextureManager();

      ruby::bind_font();
      ruby::bind_input();
      ruby::bind_color();
      ruby::bind_audio();
      ruby::bind_bitmap();
      ruby::bind_sprite();
      ruby::bind_kernel();
      ruby::bind_texture();
      ruby::bind_fonts(fonts);
      ruby::bind_textures(textures);
      ruby::bind_vector_int();
      ruby::bind_vector_float();

      Runtime::start();
      Interpreter::start();

      while(Runtime::running())
      {
         Runtime::update();
         Timestamp::update();
      }

      Runtime::finish();
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
