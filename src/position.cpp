#include "position.h"
#include "entity.h"
#include "constants.h"
#include "math.h"


void update_position_ghost(Entity& entity) {
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.accel == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  Accel& accel = *(entity.accel);
  pos.sx = pos.x; pos.sy = pos.y;
  speed.vx += accel.ax - sgn(speed.vx)*accel.friction;
  speed.vy += accel.ay - sgn(speed.vy)*accel.friction;
  pos.sx += speed.vx;
  pos.sy += speed.vy;
  // do realize motion now, as there is no collision anyway
  pos.x = pos.sx; pos.y = pos.sy;
}


void update_position(Entity& entity) {
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  AABB& mask = *(entity.mask);
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


void update_position_inertial(Entity& entity) {
  if(entity.accel == NULL &&
     entity.mask != NULL) {
    update_position(entity);
    return;
  }else if(entity.mask == NULL) {
    update_position_ghost(entity);
    return;
  }else if(entity.position == NULL 
   || entity.speed == NULL
   || entity.accel == NULL) { return; }
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


void cap_speed(Entity& entity, const int& cap) {
  Speed& speed = *(entity.speed);
  speed.vx = fabs(speed.vx) > cap ? sgn(speed.vx)*cap : speed.vx;
  speed.vy = fabs(speed.vy) > cap ? sgn(speed.vy)*cap : speed.vy;
}


