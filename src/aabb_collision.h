#ifndef _AABB_COLLISION_H_
#define _AABB_COLLISION_H_

#include "constants.h"
#include "component.h"

class Entity;

class AABB : public Component { // AABB collision mask
public:
  int w;
  int h;
  AABB() {
    w=0;
    h=0;
  }
};



#endif
