#include "entity.h"
#include <stdio.h>

#include "position.h"
#include "rectangle.h"
#include "aabb_collision.h"


EntityFactory entity_factory;

int EntityFactory::next_id = 0;

Entity::Entity(): id(0), flags(0), lifespan(-1) {
  for(int i = 0; i < MAX_COMPONENT_TYPE; ++i) {
    comp_id[i] = -1;
  }
}

void Entity::remove() {
  flags = DEAD;
  if(position() != NULL) {
    position_factory.remove(comp_id[POSITION]);
  }
  if(speed() != NULL) {
    speed_factory.remove(comp_id[SPEED]);
  }
  if(accel() != NULL) {
    accel_factory.remove(comp_id[ACCEL]);
  }
  if(shape() != NULL) {
    shape_factory.remove(comp_id[SHAPE]);
  }
  if(mask() != NULL) {
    mask_factory.remove(comp_id[MASK]);
  }
  for(int i = 0; i < MAX_COMPONENT_TYPE; ++i) {
    comp_id[i] = -1;
  }
}


void Entity::restore_compo_pointers() {
  if(position() != NULL) {
    position_factory.components[comp_id[POSITION]].entity = this;
  }
  if(speed() != NULL) {
    speed_factory.components[comp_id[SPEED]].entity = this;
  }
  if(accel() != NULL) {
    accel_factory.components[comp_id[ACCEL]].entity = this;
  }
  if(shape() != NULL) {
    shape_factory.components[comp_id[SHAPE]].entity = this;
  }
  if(mask() != NULL) {
    mask_factory.components[comp_id[MASK]].entity = this;
  }
}


int& Entity::position_id() {
  return comp_id[POSITION];
}

Position* Entity::position() {
  return comp_id[POSITION] != -1 ?
           &(position_factory.components[comp_id[POSITION]]) : NULL;
}

int& Entity::speed_id() {
  return comp_id[SPEED];
}

Speed* Entity::speed() {
  return comp_id[SPEED] != -1 ?
          &(speed_factory.components[comp_id[SPEED]]) : NULL;
}

int& Entity::accel_id() {
  return comp_id[ACCEL];
}

Accel* Entity::accel() {
  return comp_id[ACCEL] != -1 ?
          &(accel_factory.components[comp_id[ACCEL]]) : NULL;
}

int& Entity::shape_id() {
  return comp_id[SHAPE];
}

Rectangle* Entity::shape() {
  return comp_id[SHAPE] != -1 ?
          &(shape_factory.components[comp_id[SHAPE]]) : NULL;
}

int& Entity::mask_id() {
  return comp_id[MASK];
}

AABB* Entity::mask() {
  return comp_id[MASK] != -1 ?
          &(mask_factory.components[comp_id[MASK]]) : NULL;
}


Entity& EntityFactory::create() {
  Entity& entity = entities[nb_entity];
  entity = Entity();
  entity.id = next_id;
  printf("adding entity : %d\n", entity.id);
  ++next_id;
  ++nb_entity;
  return entity;
}


void EntityFactory::remove(Entity& entity) {
  if(nb_entity <= 0) { return; }
  printf("removing entity : %d\n", entity.id);
  entity.remove();
  entity = entities[nb_entity-1];
  entity.restore_compo_pointers();
  --nb_entity;
}




