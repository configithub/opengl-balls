#ifndef _AABB_COLLISION_H_
#define _AABB_COLLISION_H_

#include "constants.h"
#include "component.h"

class Entity;

class AABB : public Component { // AABB collision mask
public:
  int w; int h;
  int down_rk;
  Entity* stand_on;
  AABB(): w(0), h(0), down_rk(-1), stand_on(NULL) {}
};



#endif
