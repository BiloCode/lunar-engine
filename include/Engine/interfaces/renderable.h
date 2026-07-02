#pragma once

#include <SFML/Graphics.hpp>
#include "disposable.h"

class Renderable : public Disposable
{
public:
   float get_x() const;
   float get_y() const;
   float get_z() const;
   void set_x(float x);
   void set_y(float y);
   void set_z(float z);
   bool is_visible() const;
   void set_visible(bool visible);
   virtual void draw(sf::RenderTarget& target) = 0;

protected:
   float x = 0;
   float y = 0;
   float z = 0;
   bool visible = true;
};
