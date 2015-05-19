#ifndef _POSITION_H_
#define _POSITION_H_

#include "constants.h"
#include "component.h"

class Entity;

class Position : public Component {
public:
  int x;
  int y;
};


class Speed : public Component {
public:
  int vx;
  int vy;
};


void update_position(Entity& entity);


#endif
