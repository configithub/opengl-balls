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
  GHOST = 1 << 0,
  GRAVITY_BOUND = 2 << 0,
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


#endif
