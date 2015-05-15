#include "aabb_collision.h"
#include "position.h"
#include "entity.h"

#include "main.h"
#include <math.h>

AABB aabbs[max_entity_nb];


void check_collision(Entity& entity) {
  if ( entity.position == NULL 
    || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  AABB& mask = *(entity.mask);
  if(mask.w == 0 && mask.h == 0) { return; } // ghost object
  int x1 = pos.x; int y1 = pos.y;
  int x2 = pos.x+mask.w; int y2 = pos.y+mask.h;
  for(int i= 0; i < entity_nb; ++i) {
    Entity& other = entities[i];
    if(other.id <= entity.id) { continue; } // prevent self and double collision
    if ( other.position == NULL 
      || other.mask == NULL) { continue; }
    Position& opos = *(other.position);
    AABB& omask = *(other.mask);
    int ox1 = opos.x; int oy1 = opos.y;
    int ox2 = opos.x+omask.w; int oy2 = opos.y+omask.h;
    if( ox2 < x1 || x2 < ox1 || oy2 < y1 || y2 < oy1 ) {
      continue; // no collision
    }else{ // collision happens
      do_collision_repulse(entity, other);
    }
  }
}


void do_collision(Entity& entity, Entity& other) {
  // elastic collision
  Speed& speed = *(entity.speed);
  Speed& ospeed = *(other.speed);
  int vx = speed.vx;
  int vy = speed.vy;
  speed.vx = ospeed.vx;
  speed.vy = ospeed.vy;
  ospeed.vx = vx;
  ospeed.vy = vy;
}


void do_collision_repulse(Entity& entity, Entity& other) {
  // elastic collision
  Speed& speed = *(entity.speed);
  Speed& ospeed = *(other.speed);
  int vx = speed.vx;
  int vy = speed.vy;
  speed.vx = ospeed.vx;
  speed.vy = ospeed.vy;
  ospeed.vx = vx;
  ospeed.vy = vy;
  // repulsion to avoid interlock
  Position& pos = *(entity.position);
  AABB& mask = *(entity.mask);
  int x1 = pos.x; int y1 = pos.y;
  int x2 = pos.x+mask.w; int y2 = pos.y+mask.h;
  Position& opos = *(other.position);
  AABB& omask = *(other.mask);
  int ox1 = opos.x; int oy1 = opos.y;
  int ox2 = opos.x+omask.w; int oy2 = opos.y+omask.h;
  // collision depth, can be negative depending on relative positions
  int cx = x1 <= ox2 ? (ox2 - x1) : (x2 - ox1); 
  int cy = y1 <= oy2 ? (oy2 - y1) : (y2 - oy1);
  // repulsion impulse
  int dx = x1 <= ox2 ? 1 : -1; 
  int dy = y1 <= oy2 ? 1 : -1;
  if(fabs(cx) < fabs(cy)) {
    pos.x += dx*fabs(speed.vx);
    opos.x -= dx*fabs(ospeed.vx);;
  }else{
    pos.y += dy*fabs(speed.vy);
    opos.y -= dy*fabs(ospeed.vy);
  }
}


AABB* AABBFactory::create() {
  AABB& mask = aabbs[nb_aabb];
  ++nb_aabb;
  return &mask;
}
