#include <Engine/singletons/runtime.h>
#include <Engine/singletons/scene.h>
#include <Engine/singletons/canvas.h>
#include <Engine/singletons/project.h>

sf::RenderWindow Runtime::window = sf::RenderWindow();

void Runtime::load()
{
   auto screen_w = Project::get_settings<unsigned int>("screen_w", 1080);
   auto screen_h = Project::get_settings<unsigned int>("screen_h", 720);
   auto win_title = Project::get_settings<std::string>("win_title", "Lunar Engine");
   auto win_resizable = Project::get_settings<bool>("win_resizable", true);
   auto win_fullscreen = Project::get_settings<bool>("win_fullscreen", false);
   auto fps = Project::get_settings<int>("fps", 60);
   auto vsync = Project::get_settings<bool>("vsync", true);

   window = sf::RenderWindow(sf::VideoMode({ screen_w, screen_h }),
      win_title,
      win_resizable ? sf::Style::Default : (sf::Style::Titlebar | sf::Style::Close),
      win_fullscreen ? sf::State::Fullscreen : sf::State::Windowed
   );
   window.setFramerateLimit(fps);
   window.setVerticalSyncEnabled(vsync);
}

void Runtime::update()
{
   while (const std::optional<sf::Event> event = window.pollEvent())
   {
      if (event->is<sf::Event::Closed>())
      {
         window.close();
      }
   }

   window.clear();
   Scene::update(window);
   Canvas::update(window);
   window.display();
}

bool Runtime::running()
{
   return window.isOpen();
}
