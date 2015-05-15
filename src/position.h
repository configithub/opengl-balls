#ifndef _POSITION_H_
#define _POSITION_H_

#include "constants.h"
#include "component.h"

class Entity;

class Position : public Component {
public:
  int x;
  int y;
};


class Speed : public Component {
public:
  int vx;
  int vy;
};


void update_position(Entity& entity);


class PositionFactory {
public:
  PositionFactory(): nb_position(0) {}
  Position* create();
private:
  int nb_position;
  Position positions[max_entity_nb];
};


class SpeedFactory {
public:
  SpeedFactory(): nb_speed(0) {}
  Speed* create();
private:
  int nb_speed;
  Speed speeds[max_entity_nb];
};


#endif
