#ifndef _COLLISION_SYSTEM_H_
#define _COLLISION_SYSTEM_H_

class Entity;
class Area;

void check_collision(Entity& entity);

void do_collision(Entity& entity, Entity& other);

void do_collision_repulse(Entity& entity, Entity& other);

void speculative_contact(Entity& entity, Area& area);

#endif
