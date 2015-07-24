#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "constants.h"
#include "object.h"
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
  GRAVITY_BOUND = 8,
  SPECULATIVE_COLLIDE = 16,
  CONTACT_TREE = 32,
  PLAYER = 64,
  EPHEMERAL = 128,
  CAN_JUMP = 256
} EN_Flag;

class Entity : public Object {
public:
  Position* position;
  Speed* speed;
  Rectangle* shape;
  AABB* mask;
  Accel* accel;

  // init all components to null
  Entity(): position(NULL), 
            speed(NULL),
            shape(NULL),
            mask(NULL),
            accel(NULL) {};

  void remove();

};


extern Factory<Entity> entity_factory;

#endif
