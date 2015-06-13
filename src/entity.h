#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "constants.h"

class Component;

class Position;
class Speed;
class Accel;
class AABB;
class Rectangle;


class Entity {
public:
  int comp_id[MAX_COMPONENT_TYPE];
  int lifespan;

  int id;
  int flags; // bitset

  // init all components to null
  Entity();

  void remove();
  void restore_compo_pointers();

  int& position_id();
  Position* position();

  int& speed_id();
  Speed* speed();

  int& shape_id();
  Rectangle* shape();

  int& accel_id();
  Accel* accel();

  int& mask_id();
  AABB* mask();

};


class EntityFactory {
public:

  EntityFactory(): nb_entity(0) {}

  Entity& create();
  void remove(Entity& entity);

  Entity entities[max_entity_nb];
  int nb_entity;

  static int next_id;

};


extern EntityFactory entity_factory;

#endif
