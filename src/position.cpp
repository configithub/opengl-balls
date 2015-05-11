#include "position.h"

Position positions[max_entity_nb];
Speed speeds[max_entity_nb];

void update_position(int entity) {
  Position& pos = positions[entity];
  Speed& speed = speeds[entity];
  pos.x += speed.vx;
  pos.y += speed.vy;
  if(pos.x <= 0 || pos.x >= WWIDTH) {
    speed.vx *= -1;
  }
  if(pos.y <= 0 || pos.y >= WHEIGHT) {
    speed.vy *= -1;
  }
}
