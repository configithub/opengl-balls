#include "aabb_collision.h"
#include "position.h"

#include "main.h"

AABB aabbs[max_entity_nb];


void check_collision(int entity) {
  Position& pos = positions[entity];
  AABB& mask = aabbs[entity];
  if(mask.w == 0 && mask.h == 0) { return; } // ghost object
  int x1 = pos.x; int y1 = pos.y;
  int x2 = pos.x+mask.w; int y2 = pos.y+mask.h;
  for(int other= 0; other < entity_nb; ++other) {
    if(other <= entity) { continue; } // prevent self and double collision
    Position& opos = positions[other];
    AABB& omask = aabbs[other];
    int ox1 = opos.x; int oy1 = opos.y;
    int ox2 = opos.x+omask.w; int oy2 = opos.y+omask.h;
    if( ox2 < x1 || x2 < ox1 || oy2 < y1 || y2 < oy1 ) {
      continue; // no collision
    }else{ // collision happens
      do_collision(entity, other);
    }
  }
}


void do_collision(int entity, int other) {
  // elastic collision
  Speed& speed = speeds[entity];
  Speed& ospeed = speeds[other];
  int vx = speed.vx;
  int vy = speed.vy;
  speed.vx = ospeed.vx;
  speed.vy = ospeed.vy;
  ospeed.vx = vx;
  ospeed.vy = vy;
}
