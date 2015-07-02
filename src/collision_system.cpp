#include "collision_system.h"
#include "entity.h"
#include "tile.h"
#include <math.h>
#include <map>
#include <vector>

// 0
//    0->0 => do nothing
//    0->1 => do collision (entity : 0, other : 1)

// 1
//    1->0 => do nothing
//    1->1 => do nothing

void check_collision(Entity& entity, 
                 std::vector<Collision>& collisions ) {
  if(entity.flags & GHOST) { return; }
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
      if((entity.flags & CONTACT_TREE) && (other.flags & CONTACT_TREE)) {
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
  int x1 = pos.sx-w; int y1 = pos.sy-h;
  int x2 = pos.sx+w; int y2 = pos.sy+h;
  Position& opos = *(other.position);
  AABB& omask = *(other.mask);
  int ow = omask.w/2; int oh = omask.h/2;
  int ox1 = opos.sx-ow; int oy1 = opos.sy-oh;
  int ox2 = opos.sx+ow; int oy2 = opos.sy+oh;
  // collision depth, can be negative depending on relative positions
  int cx = x1 <= ox2 ? (x1 - ox2) : (x2 - ox1); 
  int cy = y1 <= oy2 ? (y1 - oy2) : (y2 - oy1);
  // repulsion impulse, applied on speculative positions
  if(fabs(cx) < fabs(cy)) {
    pos.sx -= cx / 2;
    opos.sx += cx / 2;;
  }else{
    pos.sy -= cy / 2 ;
    opos.sy += cy / 2;
  }
}


void realize_motion(Entity& entity) {
  entity.position->x = entity.position->sx; 
  entity.position->y = entity.position->sy;
}


void speculative_contact(Entity& entity, const Area& area) {
  if(entity.position == NULL || entity.mask == NULL ||
     entity.speed == NULL) { return; }
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
  entity.position->sx = entity.position->x; 
  entity.position->sy = entity.position->y;
}


void do_collision_speculative_tree(Entity& entity, Entity& other, 
                              std::vector<Collision>& collisions) {
  Collision col;
  col.entity = &entity;
  col.other = &other;
  collisions.push_back(col);
}


int calculate_tree_rank(Entity& entity) {
  if(entity.mask->down_rk != -1) { return entity.mask->down_rk; } // perf 
  if(entity.mask->stand_on == NULL) {
    entity.mask->down_rk = 0;
  }else{
    entity.mask->down_rk = (calculate_tree_rank(*(entity.mask->stand_on)) + 1);
  }
  return entity.mask->down_rk;
}


void create_collision_tree(std::vector<Collision>& collisions) {
  for(std::vector<Collision>::iterator itCol = collisions.begin(); 
    itCol != collisions.end(); ++itCol) { 
    if(fabs(itCol->cx) >= fabs(itCol->cy)) {
      if(itCol->entity->position->y > itCol->other->position->y) {
        // other stands on entity
        itCol->other->mask->stand_on = itCol->entity;
      }else if(itCol->entity->position->y < itCol->other->position->y) {
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
}


void rank_collisions(std::vector<Collision>& collisions, 
              std::map<int, std::vector<Collision*> >&  ranked_cols) {
  for(std::vector<Collision>::iterator itCol = collisions.begin(); 
    itCol != collisions.end(); ++itCol) { 
    int& rk = itCol->entity->mask->down_rk;
    int& ork = itCol->other->mask->down_rk;
    int col_rk = rk < ork ? rk : ork;
    ranked_cols[col_rk].push_back(&(*itCol));
  }
}


void reset_contacts(Entity& entity) {
  if(entity.mask == NULL) { return; }
  entity.mask->down_rk = -1;
  entity.mask->stand_on = NULL;
}


void resolve_collisions_for_one_rank(const std::vector<Collision*>& collisions) {
  for(int i = 0; i < collision_resolve_nb; ++i) {
    for(std::vector<Collision*>::const_iterator itCol = collisions.begin(); 
      itCol != collisions.end(); ++itCol) { 
      (*itCol)->update();
    }
    for(std::vector<Collision*>::const_iterator itCol = collisions.begin(); 
      itCol != collisions.end(); ++itCol) { 
      if(fabs((*itCol)->cx) > fabs((*itCol)->cy)) {
        if((*itCol)->entity->mask->down_rk < (*itCol)->other->mask->down_rk) {
          (*itCol)->other->position->sy += (*itCol)->cy;
          (*itCol)->other->speed->vy = 0;
        }else if((*itCol)->entity->mask->down_rk > (*itCol)->other->mask->down_rk) {
          (*itCol)->entity->position->sy -= (*itCol)->cy;
          (*itCol)->entity->speed->vy = 0;
        }
      }else{
        (*itCol)->other->position->sx += (*itCol)->cx / 2;
        (*itCol)->entity->position->sx -= (*itCol)->cx / 2;
      }
    }  
  }
}


void resolve_basic_collisions() {
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if(!(entity.flags & SPECULATIVE_COLLIDE)) {
      // basic entity, just swap position with specu position
      realize_motion(entity);
    }
  }
}


void resolve_speculative_collide_collisions(const Area& area) {
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if((entity.flags & SPECULATIVE_COLLIDE)
        && !(entity.flags & CONTACT_TREE)) {
      // speculative position to be tested against the tilemap
      speculative_contact(entity, area); 
    }
  }
}


void resolve_contact_tree_collisions(const Area& area,
                           std::vector<Collision>& collisions) {
  create_collision_tree(collisions);
  std::map<int, std::vector<Entity*> > tree;
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if(entity.flags & CONTACT_TREE) {
      // contact tree entity, will be resolved later in rank by rank fashion
      int rk = calculate_tree_rank(entity);
      tree[rk].push_back(&entity);
    }
  }
  // rank the collisions as well
  std::map<int, std::vector<Collision*> > ranked_cols;
  rank_collisions(collisions, ranked_cols);
  // contact tree entity resolution : rank by rank speculative contact in the tree
  for(std::map<int,std::vector<Entity*> >::iterator itRk = tree.begin(); 
                                   itRk != tree.end(); ++itRk) { 
    for(std::vector<Entity*>::const_iterator itEntity = itRk->second.begin(); 
      itEntity != itRk->second.end(); ++itEntity) { 
      // speculative position to be tested against the tilemap, lower rank first
      speculative_contact(**itEntity, area); 
      // resolve collisions for this rank, push the next rank
      resolve_collisions_for_one_rank(ranked_cols[itRk->first]);
    }  
  } 
}


void collision_loop(const Area& area) {
  // check for entity collisions
  std::vector<Collision> collisions; 
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    reset_contacts(entity);
    check_collision(entity, collisions);
  }
  // resolve collisions according to collision modes
  resolve_basic_collisions();
  resolve_speculative_collide_collisions(area);
  resolve_contact_tree_collisions(area, collisions);
}
