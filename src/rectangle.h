#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "constants.h"

class Rectangle {
public:
  int w;
  int h;
};

void render(int entity);

extern Rectangle rectangles[max_entity_nb];

#endif
