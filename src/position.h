#ifndef _POSITION_H_
#define _POSITION_H_

#include "constants.h"
#include "component.h"

class Entity;

class Position : public Component {
public:
  int x;
  int y;
  float theta;
  Position(): x(0), y(0), theta(0.0) {}
};


class Speed : public Component {
public:
  float vx;
  float vy;
  float omega;
  Speed(): vx(0), vy(0), omega(0.0) {}
};


class Accel : public Component {
public:
  float ax;
  float ay;
  float friction; // for inelastic rebound
  Accel() : ax(0), ay(0), friction(0) {}
};


int sgn(int val); // helper function to get the sign of an int
void update_position(Entity& entity);
void update_position_angular(Entity& entity);
void update_position_inertial(Entity& entity);


extern ComponentFactory<Position> position_factory;
extern ComponentFactory<Speed> speed_factory;
extern ComponentFactory<Accel> accel_factory;

#endif
