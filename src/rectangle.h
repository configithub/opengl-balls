#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "constants.h"
#include "component.h"

class Entity;

class Rectangle : public Component {
public:
  int w;
  int h;
};

void render(Entity& entity);

class RectangleFactory {
public:
  RectangleFactory(): nb_rectangle(0) {}
  Rectangle* create();
private:
  int nb_rectangle;
  Rectangle rectangles[max_entity_nb];
};

#endif
