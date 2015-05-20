#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "constants.h"

class Position;
class Speed;
class Rectangle;
class AABB;
class Accel;

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

};

#endif
