#include "component.h"
#include "entity.h"

void Component::restore_entity_id(int comp_id) {
  entity->comp_id[type] = comp_id;
}
