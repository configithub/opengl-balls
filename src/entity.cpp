#include "entity.h"
#include <stdio.h>


EntityFactory entity_factory;
// component factories
ComponentFactory<Position> position_factory;
ComponentFactory<Speed> speed_factory;
ComponentFactory<Accel> accel_factory;
ComponentFactory<Rectangle> shape_factory;
ComponentFactory<AABB> mask_factory;


void Entity::remove() {
  flags = DEAD;
  if(position != NULL) {
    position_factory.remove(position);
    position = NULL;
  }
  if(speed != NULL) {
    speed_factory.remove(speed);
    speed = NULL;
  }
  if(accel != NULL) {
    accel_factory.remove(accel);
    accel = NULL;
  }
  if(shape != NULL) {
    shape_factory.remove(shape);
    shape = NULL;
  }
  if(mask != NULL) {
    mask_factory.remove(mask);
    mask = NULL;
  }
}


Entity& EntityFactory::create() {
  Entity& entity = entities[nb_entity];
  entity = Entity();
  entity.id = nb_entity;
  ++nb_entity;
  return entity;
}


void EntityFactory::remove(Entity& entity) {
  if(nb_entity <= 0) { return; }
  entity.remove();
  entity = entities[nb_entity-1];
  --nb_entity;
}





