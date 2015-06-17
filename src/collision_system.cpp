#include "collision_system.h"
#include "entity.h"
#include "tile.h"
#include <math.h>

void check_collision(Entity& entity) {
  if(entity.flags & GHOST) { return; }
  if ( entity.position == NULL 
    || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  AABB& mask = *(entity.mask);
  if(mask.w == 0 && mask.h == 0) { return; } // ghost object
  int w = mask.w/2; int h = mask.h/2;
  int x1 = pos.x-w; int y1 = pos.y-h;
  int x2 = pos.x+w; int y2 = pos.y+h;
  for(int i= 0; i < entity_factory.nb_obj; ++i) {
    Entity& other = entity_factory.objs[i];
    if(other.id <= entity.id) { continue; } // prevent self and double collision
    if ( other.position == NULL 
      || other.mask == NULL) { continue; }
    Position& opos = *(other.position);
    AABB& omask = *(other.mask);
    int ow = omask.w/2; int oh = omask.h/2;
    int ox1 = opos.x-ow; int oy1 = opos.y-oh;
    int ox2 = opos.x+ow; int oy2 = opos.y+oh;
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
  int w = mask.w/2; int h = mask.h/2;
  int x1 = pos.x-w; int y1 = pos.y-h;
  int x2 = pos.x+w; int y2 = pos.y+h;
  Position& opos = *(other.position);
  AABB& omask = *(other.mask);
  int ow = omask.w/2; int oh = omask.h/2;
  int ox1 = opos.x-ow; int oy1 = opos.y-oh;
  int ox2 = opos.x+ow; int oy2 = opos.y+oh;
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


void speculative_contact(Entity& entity, Area& area) {
  if(entity.position == NULL || entity.mask == NULL ||
     entity.speed == NULL) { return; }
  //standing_on(entity); // adjust player entity position if it stands on something else
  
  // check for horizontal collision, for now none of it
  // check all position between current position and destination position step by step
  // if one of the position is not valid, stop there and realize the motion to this position
  // else go to the destination position
  // could be optimized with normal vectors
  int step_x = entity.speed->vx > 0 ? 1 : (entity.speed->vx < 0 ? -1 : 0);
  int step_y = entity.speed->vy > 0 ? 1 : (entity.speed->vy < 0 ? -1 : 0);
  int speculative_x = entity.position->x;  int speculative_y = entity.position->y;
  int dist_x = entity.speed->vx;           int dist_y = entity.speed->vy;
  while(true) {
    speculative_x += step_x;
    if(!area.valid_map_position(speculative_x, speculative_y, entity)) {
      entity.speed->vx = 0;
      speculative_x -= step_x;
      step_x = 0;
    }else{
      dist_x -= step_x;
    }
    speculative_y += step_y;
    if(!area.valid_map_position(speculative_x, speculative_y, entity)) {
      // if(entity.speed->vy > 0) { entity.motion.can_jump = true; } // falling collision, entity can now jump
      entity.speed->vy = 0;
      speculative_y -= step_y;
      step_y = 0;
    }else{
      dist_y -= step_y;
    }
    if(dist_x == 0) { step_x = 0; }
    if(dist_y == 0) { step_y = 0; }
    if(step_x ==0 && step_y == 0) { break; }
  }
  entity.position->x = speculative_x; entity.position->y = speculative_y;
}
