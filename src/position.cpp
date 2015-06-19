#include "position.h"
#include "entity.h"
#include "constants.h"

int sgn(int val) {
  return (0 < val) - (val < 0);
}


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


void update_position_inertial(Entity& entity) {
  if( entity.accel == NULL ) {
    update_position_angular(entity);
    return;
  }
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.accel == NULL
   || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  Accel& accel = *(entity.accel);
  AABB& mask = *(entity.mask);
  speed.vx += accel.ax - sgn(speed.vx)*accel.friction;
  speed.vy += accel.ay - sgn(speed.vy)*accel.friction;
  if(!(entity.flags & SPECULATIVE_COLLIDE)) {
    // entity does not collide with the tilemap
    pos.x += speed.vx;
    pos.y += speed.vy;
  } // position of entities that can collide with the tilemap 
    //through speculative contact are updated later in collision system
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


void update_position_speculative(Entity& entity) {
  if( entity.accel == NULL ) {
    update_position_angular(entity);
    return;
  }
  if(!(entity.flags & SPECULATIVE_COLLIDE)) {
    update_position_inertial(entity);
    return;
  }
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.accel == NULL
   || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  Accel& accel = *(entity.accel);
  AABB& mask = *(entity.mask);
  speed.vx += accel.ax - sgn(speed.vx)*accel.friction;
  speed.vy += accel.ay - sgn(speed.vy)*accel.friction;
  // update speculative position
  pos.sx = pos.x; pos.sy = pos.y;
  pos.sx += speed.vx;
  pos.sy += speed.vy;
  if(pos.sx <= mask.w/2 || pos.sx >= WWIDTH-mask.w/2) {
    speed.vx *= -1;
    // avoid area evasion bug at collisions 
    pos.sx = pos.sx <= mask.w/2 ? mask.w/2+1 : WWIDTH-mask.w/2-1;
  }
  if(pos.sy <= mask.h/2 || pos.sy >= WHEIGHT-mask.h/2) {
    speed.vy *= -1;
    pos.sy = pos.sy <= mask.h/2 ? mask.h/2+1 : WHEIGHT-mask.h/2-1;
  }
  // update rotation angle
  pos.theta += speed.omega;
  pos.theta = pos.theta > 2*PI ? pos.theta - 2*PI : pos.theta;

}
