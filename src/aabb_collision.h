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

void check_collision(Entity& entity);

void do_collision(Entity& entity, Entity& other);

void do_collision_repulse(Entity& entity, Entity& other);

class AABBFactory {
public:
  AABBFactory(): nb_aabb(0) {}
  AABB* create();
private:
  int nb_aabb;
  AABB aabbs[max_entity_nb];
};

#endif
