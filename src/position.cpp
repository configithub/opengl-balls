#include "position.h"
#include "aabb_collision.h"
#include "entity.h"

void update_position(Entity& entity) {
  if( entity.position == NULL 
   || entity.speed == NULL
   || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  Speed& speed = *(entity.speed);
  AABB& mask = *(entity.mask);
  pos.x += speed.vx;
  pos.y += speed.vy;
  if(pos.x <= 0 || pos.x >= WWIDTH-mask.w) {
    speed.vx *= -1;
    // avoid area evasion bug at collisions 
    pos.x = pos.x <= 0 ? 1 : WWIDTH-mask.w-1;
  }
  if(pos.y <= 0 || pos.y >= WHEIGHT-mask.h) {
    speed.vy *= -1;
    pos.y = pos.y <= 0 ? 1 : WHEIGHT-mask.h-1;
  }
}


Position* PositionFactory::create() {
  Position& pos = positions[nb_position];
  ++nb_position;
  return &pos;
}

Speed* SpeedFactory::create() {
  Speed& pos = speeds[nb_speed];
  ++nb_speed;
  return &pos;
}
