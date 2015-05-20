#include "position.h"
#include "aabb_collision.h"
#include "entity.h"
#include "constants.h"

void update_position(Entity& entity) {
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  AABB& mask = *(entity.mask);
  pos.x += speed.vx;
  pos.y += speed.vy;
  if(pos.x <= mask.w/2 || pos.x >= WWIDTH-mask.w/2) {
    speed.vx *= -1;
    // avoid area evasion bug at collisions 
    pos.x = pos.x <= mask.w/2 ? mask.w/2+1 : WWIDTH-mask.w/2-1;
  }
  if(pos.y <= mask.h/2 || pos.y >= WHEIGHT-mask.h/2) {
    speed.vy *= -1;
    pos.y = pos.y <= mask.h/2 ? mask.h/2+1 : WHEIGHT-mask.h/2-1;
  }
}


void update_position_angular(Entity& entity) {
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  AABB& mask = *(entity.mask);
  pos.x += speed.vx;
  pos.y += speed.vy;
  if(pos.x <= mask.w/2 || pos.x >= WWIDTH-mask.w/2) {
    speed.vx *= -1;
    // avoid area evasion bug at collisions 
    pos.x = pos.x <= mask.w/2 ? mask.w/2+1 : WWIDTH-mask.w/2-1;
  }
  if(pos.y <= mask.h/2 || pos.y >= WHEIGHT-mask.h/2) {
    speed.vy *= -1;
    pos.y = pos.y <= mask.h/2 ? mask.h/2+1 : WHEIGHT-mask.h/2-1;
  }
  // update rotation angle
  pos.theta += speed.omega;
  pos.theta = pos.theta > 2*PI ? pos.theta - 2*PI : pos.theta;

}
