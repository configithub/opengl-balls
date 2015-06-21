#ifndef _COLLISION_SYSTEM_H_
#define _COLLISION_SYSTEM_H_

#include "constants.h"
#include <vector>

class Entity;
class Area;
class Point;

class Collision {
public:
  Entity* entity;
  Entity* other;
  int cx;
  int cy;
  int rk;
  void update();
  Collision(): entity(NULL), other(NULL), cx(0), cy(0) {}
};

// used for all entities
void check_collision(Entity& entity, 
                  std::vector<Collision>& collisions);

// rudimentary collision resolution, not used currently
void do_collision(Entity& entity, Entity& other);

// used for entities not under contact tree collision mode
void do_collision_speculative(Entity& entity, Entity& other);

// speculative position value given to true position
void realize_motion(Entity& entity);

// speculative contact with the tilemap
void speculative_contact(Entity& entity, Area& area);

// collision objects created for contact tree collisions
void do_collision_speculative_tree(Entity& entity, Entity& other,
                  std::vector<Collision>& collisions);

// rank the entity in the contact tree
int calculate_tree_rank(Entity& entity);

// propagate the entities' rank to the collisions
void create_collision_tree(std::vector<Collision> collisions);

// resolve collisions for one given rank
void resolve_collisions_for_rank(std::vector<Collision> collisions, int rank);

// called in main loop
void collision_loop(Area& area);

// one iteration of the collision system
void collision_iteration(Area& area, int it_nb);

#endif
