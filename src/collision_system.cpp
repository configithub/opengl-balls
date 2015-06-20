#include "collision_system.h"
#include "entity.h"
#include "tile.h"
#include <math.h>
#include <map>
#include <vector>

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


void check_collision_speculative(Entity& entity, std::vector<Collision>& collisions ) {
  if(entity.flags & GHOST) { return; }
  if(!(entity.flags & SPECULATIVE_COLLIDE)) { check_collision(entity); return; }
  if ( entity.position == NULL 
    || entity.mask == NULL) { return; }
  Position& pos = *(entity.position);
  AABB& mask = *(entity.mask);
  if(mask.w == 0 && mask.h == 0) { return; } // ghost object
  int w = mask.w/2; int h = mask.h/2;
  int x1 = pos.sx-w; int y1 = pos.sy-h;
  int x2 = pos.sx+w; int y2 = pos.sy+h;
  for(int i= 0; i < entity_factory.nb_obj; ++i) {
    Entity& other = entity_factory.objs[i];
    if(other.id <= entity.id) { continue; } // prevent self and double collision
    if ( other.position == NULL 
      || other.mask == NULL) { continue; }
    Position& opos = *(other.position);
    AABB& omask = *(other.mask);
    int ow = omask.w/2; int oh = omask.h/2;
    int ox1 = opos.sx-ow; int oy1 = opos.sy-oh;
    int ox2 = opos.sx+ow; int oy2 = opos.sy+oh;
    if( ox2 < x1 || x2 < ox1 || oy2 < y1 || y2 < oy1 ) {
      continue; // no collision
    }else{ // collision happens
      if(entity.flags & CONTACT_TREE) {
        do_collision_speculative_tree(entity, other, collisions);
      }else{
        do_collision_speculative(entity, other);
      }
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
  int cx = x1 <= ox2 ? (x1 - ox2) : (x2 - ox1); 
  int cy = y1 <= oy2 ? (y1 - oy2) : (y2 - oy1);
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


void do_collision_speculative(Entity& entity, Entity& other) {
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
  int ox1 = opos.sx-ow; int oy1 = opos.sy-oh;
  int ox2 = opos.sx+ow; int oy2 = opos.sy+oh;
  // collision depth, can be negative depending on relative positions
  int cx = x1 <= ox2 ? (x1 - ox2) : (x2 - ox1); 
  int cy = y1 <= oy2 ? (y1 - oy2) : (y2 - oy1);
  // repulsion impulse, applied on speculative positions
  // printf("cx: %d, cy: %d\n", cx, cy);
  // TODO bug : sometimes cy = -42
  if(fabs(cx) < fabs(cy)) {
    pos.sx -= cx / 2;
    opos.sx += cx / 2;;
  }else{
    pos.sy -= cy / 2 ;
    opos.sy += cy / 2;
  }
}


void do_collision_speculative_tree(Entity& entity, Entity& other, std::vector<Collision>& collisions) {
  Collision col;
  col.entity = &entity;
  col.other = &other;
  collisions.push_back(col);
}


void speculative_contact(Entity& entity, Area& area) {
  if(entity.position == NULL || entity.mask == NULL ||
     entity.speed == NULL) { return; }
  
  // check for horizontal collision, for now none of it
  // check all position between current position and destination position step by step
  // if one of the position is not valid, stop there and realize the motion to this position
  // else go to the destination position
  // could be optimized with normal vectors
  int step_x = sgn(entity.position->sx - entity.position->x);
  int step_y = sgn(entity.position->sy - entity.position->y);
  int speculative_x = entity.position->x;  int speculative_y = entity.position->y;
  int dist_x = entity.position->sx - entity.position->x;
  int dist_y = entity.position->sy - entity.position->y;
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


void speculative_contact_tree(Entity& entity, Area& area) {
  if(entity.position == NULL || entity.mask == NULL ||
     entity.speed == NULL) { return; }
  
  // check for horizontal collision, for now none of it
  // check all position between current position and destination position step by step
  // if one of the position is not valid, stop there and realize the motion to this position
  // else go to the destination position
  // could be optimized with normal vectors
  int step_x = sgn(entity.position->sx - entity.position->x);
  int step_y = sgn(entity.position->sy - entity.position->y);
  int speculative_x = entity.position->x;  int speculative_y = entity.position->y;
  int dist_x = entity.position->sx - entity.position->x;
  int dist_y = entity.position->sy - entity.position->y;
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
  // swap position and speculative position, sx and sy are now the historical coords
  entity.position->x = speculative_x; entity.position->y = speculative_y;
  entity.position->sx = entity.position->x; entity.position->sy = entity.position->y;
}


int calculate_tree_rank(Entity& entity) {
  if(entity.mask->stand_on == NULL) {
    entity.mask->down_rk = 0;
  }else{
    entity.mask->down_rk = (calculate_tree_rank(*(entity.mask->stand_on)) + 1);
  }
  return entity.mask->down_rk;
}


/*Point standing_on(Entity& entity) {
  Point result;
  if(entity.mask->stand_on != NULL) { // entity is standing on another entity
    result.x = (entity.mask->stand_on->position->x - entity.mask->stand_on->position->sx);
    result.y = (entity.mask->stand_on->position->y - entity.mask->stand_on->position->sy);
  }
  return result;
}*/


void create_collision_tree(std::vector<Collision> collisions) {
  for(std::vector<Collision>::iterator itCol = collisions.begin(); 
    itCol != collisions.end(); ++itCol) { 
    if(fabs(itCol->cx) >= fabs(itCol->cy) /*&& itCol->cy !=0*/) {
      if(itCol->cy <= 0) {
        // other stands on entity
        itCol->other->mask->stand_on = itCol->entity;
      }else if(itCol->cy >0){
        // entity stands on other
        itCol->entity->mask->stand_on = itCol->other;
      }
    }
  }  
}


void Collision::update() {
  Position& pos = *(entity->position);
  AABB& mask = *(entity->mask);
  int w = mask.w/2; int h = mask.h/2;
  int x1 = pos.sx-w; int y1 = pos.sy-h;
  int x2 = pos.sx+w; int y2 = pos.sy+h;
  Position& opos = *(other->position);
  AABB& omask = *(other->mask);
  int ow = omask.w/2; int oh = omask.h/2;
  int ox1 = opos.sx-ow; int oy1 = opos.sy-oh;
  int ox2 = opos.sx+ow; int oy2 = opos.sy+oh;
  // collision depth, can be negative depending on relative positions
  cx = pos.x < opos.x ? (x2 - ox1) : (x1 - ox2); 
  cy = pos.y < opos.y ? (y2 - oy1) : (y1 - oy2);
  // printf("entity: #%d, other: #%d, updating cy: %d\n", entity->id, other->id, cy);
}


void resolve_collisions_for_rank(std::vector<Collision> collisions, int rank) {
  for(int i = 0; i < collision_resolve_nb; ++i) {
    std::map<int, std::vector<Collision*> > ranked_cols; 
    for(std::vector<Collision>::iterator itCol = collisions.begin(); 
      itCol != collisions.end(); ++itCol) { 
      int& rk = itCol->entity->mask->down_rk;
      int& ork = itCol->other->mask->down_rk;
      itCol->rk = rk < ork ? rk : ork;
      if(itCol->rk == rank) {
        itCol->update();
      }
    }
    for(std::vector<Collision>::iterator itCol = collisions.begin(); 
      itCol != collisions.end(); ++itCol) { 
      if(itCol->rk == rank) {
        if(fabs(itCol->cx) > fabs(itCol->cy) /*&& itCol->cy !=0*/) {
          if(itCol->entity->mask->down_rk < itCol->other->mask->down_rk) {
            itCol->other->position->sy += itCol->cy+2;
            itCol->other->speed->vy = 0;
          }else if(itCol->entity->mask->down_rk > itCol->other->mask->down_rk) {
            itCol->entity->position->sy += itCol->cy+2;
            itCol->entity->speed->vy = 0;
          }
        }else{
          itCol->other->position->sx += itCol->cx / 2;
          itCol->entity->position->sx -= itCol->cx / 2;
        }
      }
    }  
  }
}


void collision_loop(Area& area) {
  for(int i = 0; i < collision_iteration_nb; ++i) {
    collision_iteration(area, i);
  }
}


void collision_iteration(Area& area, int it_nb) {
  std::vector<Collision> collisions; 
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    entity.mask->down_rk = -1;
    entity.mask->stand_on = NULL;
    check_collision_speculative(entity, collisions);
  }
  create_collision_tree(collisions);
  std::map<int, std::vector<Entity*> > tree;
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if(entity.flags & CONTACT_TREE) {
      int rk = calculate_tree_rank(entity);
      tree[rk].push_back(&entity);
    }
  }
  // rank by rank speculative contact in the tree
  for(std::map<int,std::vector<Entity*> >::iterator itRk = tree.begin(); 
    itRk != tree.end(); ++itRk) { 
    printf("rank %d : %d entities\n", itRk->first, itRk->second.size());
    for(std::vector<Entity*>::iterator itEntity = itRk->second.begin(); 
      itEntity != itRk->second.end(); ++itEntity) { 
      printf("    rank %d : entity #%d\n", itRk->first, (*itEntity)->id);
      if((*itEntity)->mask->down_rk == itRk->first) {
        speculative_contact_tree(**itEntity, area); 
      }
      resolve_collisions_for_rank(collisions, itRk->first);
    }  
  } 
}
