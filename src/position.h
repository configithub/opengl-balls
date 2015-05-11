#ifndef _POSITION_H_
#define _POSITION_H_

#include "constants.h"

class Position {
public:
  int x;
  int y;
};


class Speed {
public:
  int vx;
  int vy;
};

void update_position(int entity);

extern Position positions[max_entity_nb];
extern Speed speeds[max_entity_nb];

#endif
