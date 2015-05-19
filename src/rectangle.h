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
void render_rotated(Entity& entity);


#endif
