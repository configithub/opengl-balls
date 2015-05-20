#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "constants.h"

class Position;
class Speed;
class Rectangle;
class AABB;
class Angle;
class AngularSpeed;

class Entity {
public:
  Position* position;
  Speed* speed;
  Rectangle* shape;
  AABB* mask;
  Angle* angle;
  AngularSpeed* ang_speed;

  int id;

  // init all components to null
  Entity(): id(0), position(NULL), 
            speed(NULL),
            shape(NULL),
            mask(NULL),
            angle(NULL),
            ang_speed(NULL) {};

};

#endif