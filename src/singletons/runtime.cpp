#include <Engine/singletons/runtime.h>
#include <Engine/singletons/debug.h>
#include <Engine/singletons/scene.h>
#include <Engine/singletons/canvas.h>
#include <Engine/singletons/project.h>
#include <string>

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
   Debug::update(window);

   while (const std::optional<sf::Event> event = window.pollEvent())
   {
      if (event->is<sf::Event::Closed>()) {
         window.close();
      }

      if (event->is<sf::Event::Resized>()) {
         on_resize(event);
      }

      on_input(event);
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

void Runtime::on_input(const std::optional<sf::Event>& event)
{
}

void Runtime::on_resize(const std::optional<sf::Event>& event)
{
   auto viewport_w = Project::get_settings<float>("viewport_w", 640.f);
   auto viewport_h = Project::get_settings<float>("viewport_h", 480.f);

   sf::View view(sf::FloatRect({ 0.f, 0.f }, { viewport_w, viewport_h }));

   float view_ratio = viewport_w / viewport_h;
   float window_ratio = float(window.getSize().x) / window.getSize().y;

   float pos_x = 0.f, pos_y = 0.f;
   float size_x = 1.f, size_y = 1.f;

   if (window_ratio > view_ratio) {
      size_x = view_ratio / window_ratio;
      pos_x = (1.f - size_x) / 2.f;
   }
   else {
      size_y = window_ratio / view_ratio;
      pos_y = (1.f - size_y) / 2.f;
   }

   view.setViewport(sf::FloatRect({ pos_x, pos_y }, { size_x, size_y }));
   window.setView(view);
}
