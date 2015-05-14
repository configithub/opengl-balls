#ifndef _AABB_COLLISION_H_
#define _AABB_COLLISION_H_

#include "constants.h"

class AABB { // AABB collision mask
public:
  int w;
  int h;
  AABB() {
    w=0;
    h=0;
  }
};

void check_collision(int entity);

void do_collision(int entity, int other);

extern AABB aabbs[max_entity_nb];

#endif
