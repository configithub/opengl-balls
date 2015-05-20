#ifndef _POSITION_H_
#define _POSITION_H_

#include "constants.h"
#include "component.h"

class Entity;

class Position : public Component {
public:
  int x;
  int y;
  float theta;
  Position(): x(0), y(0), theta(0.0) {}
};


class Speed : public Component {
public:
  int vx;
  int vy;
  float omega;
  Speed(): vx(0), vy(0), omega(0.0) {}
};


void update_position(Entity& entity);
void update_position_angular(Entity& entity);


#endif
