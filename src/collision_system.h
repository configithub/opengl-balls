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
  void update();
  Collision(): entity(NULL), other(NULL), cx(0), cy(0) {}
};

void check_collision(Entity& entity);

void check_collision_speculative(Entity& entity, 
                  std::vector<Collision>& collisions);

void do_collision(Entity& entity, Entity& other);

void do_collision_repulse(Entity& entity, Entity& other);

void do_collision_speculative(Entity& entity, Entity& other);

void do_collision_speculative_tree(Entity& entity, Entity& other,
                  std::vector<Collision>& collisions);

void speculative_contact(Entity& entity, Area& area);

void speculative_contact_tree(Entity& entity, Area& area);


Point standing_on(Entity& entity);

void collision_loop(Area& area);

void collision_iteration(Area& area, int it_nb);

void create_collision_tree(std::vector<Collision> collisions);

void resolve_collisions(std::vector<Collision> collisions);

void resolve_collisions_by_rank(std::vector<Collision> collisions);

int calculate_tree_rank(Entity& entity);

#endif
