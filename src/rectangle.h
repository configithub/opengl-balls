#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "constants.h"
#include "component.h"

class Entity;

class Rectangle : public Component {
public:
  int w;
  int h;
  Rectangle(): w(0), h(0) {}
};

void render_basic(Entity& entity);
void render(Entity& entity);

extern ComponentFactory<Rectangle> shape_factory;

#endif
