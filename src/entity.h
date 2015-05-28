#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "constants.h"
#include "component.h"

#include "position.h"
#include "aabb_collision.h"
#include "rectangle.h"

// component factories
extern ComponentFactory<Position> position_factory;
extern ComponentFactory<Speed> speed_factory;
extern ComponentFactory<Accel> accel_factory;
extern ComponentFactory<Rectangle> shape_factory;
extern ComponentFactory<AABB> mask_factory;

typedef enum {
  DEAD =  2,
  GHOST = 4,
  GRAVITY_BOUND = 8
  //DEAD = 1 << 0,
  //GHOST = 2 << 0,
  //GRAVITY_BOUND = 4 << 0,
} EN_Flag;

class Entity {
public:
  Position* position;
  Speed* speed;
  Rectangle* shape;
  AABB* mask;
  Accel* accel;

  int id;
  int flags; // bitset

  // init all components to null
  Entity(): id(0), position(NULL), 
            speed(NULL),
            shape(NULL),
            mask(NULL),
            accel(NULL), 
            flags(0) {};

  void remove();

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
