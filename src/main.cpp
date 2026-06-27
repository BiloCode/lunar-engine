#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/fonts_loader.h>
#include <Engine/resources/settings_loader.h>
#include <Engine/resources/graphics_loader.h>
#include <Engine/bindings/r_font.h>
#include <Engine/bindings/r_fonts.h>
#include <Engine/bindings/r_color.h>
#include <Engine/bindings/r_audio.h>
#include <Engine/bindings/r_input.h>
#include <Engine/bindings/r_bitmap.h>
#include <Engine/bindings/r_sprite.h>
#include <Engine/bindings/r_graphics.h>
#include <Engine/core/render.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
   try {
      RubyLoader r_loader;
      FontsLoader f_loader("fonts");
      GraphicsLoader g_loader("graphics");

      SettingsLoader s_loader("game.cfg");
      Settings settings = s_loader.get_settings();

      FontsCache fonts = f_loader.get_cache();
      GraphicsCache graphics = g_loader.get_cache();

      r_loader.open();
      r_loader.preload();

      r_font { r_loader };
      r_fonts { r_loader, fonts };
      r_input { r_loader };
      r_color { r_loader };
      r_audio { r_loader };
      r_bitmap { r_loader };
      r_sprite { r_loader };
      r_graphics { r_loader, graphics };

      sf::RenderWindow window(sf::VideoMode({ settings.screen_w, settings.screen_h }),
         settings.win_title,
         settings.win_resizable ? sf::Style::Default : (sf::Style::Titlebar | sf::Style::Close),
         settings.win_fullscreen ? sf::State::Fullscreen : sf::State::Windowed
      );

      r_loader.initialize();

      window.setFramerateLimit(settings.fps);
      window.setVerticalSyncEnabled(settings.vsync);

      while (window.isOpen())
      {
         while (const std::optional<sf::Event> event = window.pollEvent())
         {
            if (event->is<sf::Event::Closed>())
            {
               window.close();
            }
         }

         window.clear();
         Render::update(window);
         window.display();
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
