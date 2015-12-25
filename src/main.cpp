#include "main.h"
#include "collision_system.h"
#include <iostream>

SDL_Event events;
bool running;

const int speed_factor = 4;
const int size_factor = 20;
const int speed_cap = 5;

bool tile_map_active = true;

//const int starting_entity_nb = 0;
const int starting_entity_nb = 1;

bool left_pushed = false;
bool right_pushed = false;
bool up_pushed = false;
bool down_pushed = false;

bool a_pushed = false;
bool w_pushed = false;
bool s_pushed = false;
bool d_pushed = false;

int mode = CONTACT_TREE_BALL_SPAWN; 
// Area area(2,1);
Area area;
Accel gravity;
Entity camera;
Entity* player = NULL;

void manage_inputs() {
  while(SDL_PollEvent(&events)) {
    if(events.type == SDL_QUIT)
      running = false;
    if(events.type ==  SDL_KEYUP) 
      key_up(events.key.keysym.sym,events.key.keysym.mod,
                       events.key.keysym.unicode);
    if(events.type ==  SDL_KEYDOWN) 
      key_down(events.key.keysym.sym,events.key.keysym.mod,
                       events.key.keysym.unicode);
  }
}


void key_up(SDLKey sym, SDLMod mod, Uint16 unicode) { 
  switch(sym) {
    case SDLK_SPACE:
      switch(mode) {
        case FIXED_BALL_SPAWN:
          add_ball();
        break;
        case RANDOM_BALL_SPAWN:
          add_random_ball();
        break;
        case FIXED_HARD_BALL_SPAWN:
          add_hard_ball();
        break;
        case RANDOM_HARD_BALL_SPAWN:
          add_random_hard_ball();
        break;
        case RANDOM_ROTATED_BALL_SPAWN:
          add_random_rotated_ball();
        break;
        case RANDOM_ROTATING_BALL_SPAWN:
          add_random_rotating_ball();
        break;
        case RANDOM_FALLING_BALL_SPAWN:
          add_falling_ball();
        break;
        case SPECU_COLLIDING_BALL_SPAWN:
          add_specu_colliding_ball();
        break;
        case CONTACT_TREE_BALL_SPAWN:
          add_contact_tree_ball();
        break;
        case EPHEMERAL_BALL_SPAWN:
          add_ephemeral_ball();
        break;
        case FIREWORK_SPAWN:
          add_firework();
        break;
      }
    break;
    case SDLK_m:
      switch_mode();
    break;
    case SDLK_n:
      switch_mode(-1);
    break;
    case SDLK_t:
      spawn();
    break;
    case SDLK_r:
      respawn();
    break;
    case SDLK_c:
      clear_all();
    break;
    case SDLK_y:
      if(tile_map_active) {
        clear_tile_map();
      }else{
        set_square_tile_map();
        //init_tile_map();
      }
    break;
    case SDLK_u:
      remove_random_ball();
    break;
    case SDLK_i:
      set_gravity(0, -2);
    break;
    case SDLK_j:
      set_gravity(-2, 0);
    break;
    case SDLK_k:
      set_gravity(0, 2);
    break;
    case SDLK_l:
      set_gravity(2, 0);
    break;
    case SDLK_o:
      set_gravity(0, 0);
    break;
    case SDLK_w:
      w_pushed = false;
    break;
    case SDLK_a:
      a_pushed = false;
    break;
    case SDLK_s:
      s_pushed = false;
    break;
    case SDLK_d:
      d_pushed = false;
    break;
    case SDLK_LEFT:
      left_pushed = false;
    break;
    case SDLK_RIGHT:
      right_pushed = false;
    break;
    case SDLK_DOWN:
      down_pushed = false;
    break;
    case SDLK_UP:
      up_pushed = false;
    break;
  }
}


void key_down(SDLKey sym, SDLMod mod, Uint16 unicode) { 
  switch(sym) {
    case SDLK_w:
      w_pushed = true;
    break;
    case SDLK_a:
      a_pushed = true;
    break;
    case SDLK_s:
      s_pushed = true;
    break;
    case SDLK_d:
      d_pushed = true;
    break;
    case SDLK_LEFT:
      left_pushed = true;
    break;
    case SDLK_RIGHT:
      right_pushed = true;
    break;
    case SDLK_DOWN:
      down_pushed = true;
    break;
    case SDLK_UP:
      up_pushed = true;
    break;
  }
}


void init_camera() {
  camera.position = position_factory.create();
  camera.speed = speed_factory.create();
  camera.accel = accel_factory.create();
  camera.shape = shape_factory.create();
  camera.position->x = 0;
  camera.position->y = 0;
  camera.shape->w = WWIDTH;
  camera.shape->h = WHEIGHT;
  camera.flags = GHOST;
  camera.accel->friction = 1.0;
}


void add_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = 0;
  entity.position->y = 0;
  entity.speed->vx = speed_factor;
  entity.speed->vy = speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.flags = GHOST;
}


void add_random_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.flags = GHOST;
}


void add_hard_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = 1;
  entity.position->y = 1;
  entity.speed->vx = speed_factor;
  entity.speed->vy = speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
}


void add_random_hard_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
}


void add_random_rotated_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
}


void add_random_rotating_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed->omega = PI *( (float) (rand() % 20) / 250);
}


void add_falling_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.accel = accel_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.flags = GRAVITY_BOUND;
  entity.accel->friction = 1;
}


void add_ephemeral_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.accel = accel_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed->omega = PI *( (float) (rand() % 20) / 250);
  entity.flags = GRAVITY_BOUND | EPHEMERAL;
  entity.lifespan = 100; // entity will live 100 frames
  entity.accel->friction = 1.0;
}


void add_firework() {
  int x = rand() % WWIDTH;
  int y = rand() % WHEIGHT;
  int n = 5 + rand() % 5;
  for(int i =0; i< n; ++i) {
    Entity& entity = entity_factory.create();
    entity.position = position_factory.create();
    entity.speed = speed_factory.create();
    entity.shape = shape_factory.create();
    entity.mask = mask_factory.create();
    entity.accel = accel_factory.create();
    entity.position->x = x;
    entity.position->y = y;
    entity.speed->vx = rand() % 20*speed_factor - 10*speed_factor;
    entity.speed->vy = rand() % 20*speed_factor - 10*speed_factor;
    entity.shape->w = size_factor;
    entity.shape->h = size_factor;
    entity.mask->w = size_factor;
    entity.mask->h = size_factor;
    entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
    entity.speed->omega = PI *( (float) (rand() % 20) / 250);
    entity.flags = GRAVITY_BOUND | EPHEMERAL | GHOST;
    entity.lifespan = 50; 
    entity.accel->friction = 0.5;
  }
}


void add_specu_colliding_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.accel = accel_factory.create();
  entity.position->x = WWIDTH / 2;
  entity.position->y = WHEIGHT / 2;
  entity.speed->vx = 0;
  entity.speed->vy = 0;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.flags = GRAVITY_BOUND | SPECULATIVE_COLLIDE;
  entity.accel->friction = 1;
}


void add_contact_tree_ball() {
  Entity& entity = entity_factory.create();
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.accel = accel_factory.create();
  entity.position->x = WWIDTH / 2;
  entity.position->y = 2*WHEIGHT / 3;
  entity.speed->vx = 0;
  entity.speed->vy = 0;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.flags = GRAVITY_BOUND | SPECULATIVE_COLLIDE | CONTACT_TREE;
  entity.accel->friction = 1;
}


void init_player() {
  Entity& player_entity = entity_factory.create();
  player = &player_entity;
  player->position = position_factory.create();
  player->speed = speed_factory.create();
  player->shape = shape_factory.create();
  player->mask = mask_factory.create();
  player->accel = accel_factory.create();
  player->position->x = WWIDTH / 2;
  player->position->y = WHEIGHT / 2;
  player->speed->vx = 0;
  player->speed->vy = 0;
  player->shape->w = size_factor;
  player->shape->h = 2*size_factor;
  player->mask->w = size_factor;
  player->mask->h = 2*size_factor;
  player->flags = GRAVITY_BOUND | SPECULATIVE_COLLIDE | CONTACT_TREE 
                  | PLAYER | CAN_JUMP;
  player->accel->friction = 1;
}


void remove_random_ball() {
  if(entity_factory.nb_obj <= 0) { return; }
  int id_to_remove = rand() % entity_factory.nb_obj;
  Entity& entity_to_remove = entity_factory.objs[id_to_remove];
  entity_factory.remove(entity_to_remove);
}


void switch_mode(int val) {
  mode += val;
  mode = mode < 0 ? mode = (int)MAX_MODE -1 : mode;
  mode = mode % (int)MAX_MODE;
  printf("switch to mode : %d\n", mode);
}


void init_entities() {
  for (int i = 0; i < starting_entity_nb; i++) {
    switch(mode) {
      case FIXED_BALL_SPAWN:
        add_ball();
      break;
      case RANDOM_BALL_SPAWN:
        add_random_ball();
      break;
      case FIXED_HARD_BALL_SPAWN:
        add_hard_ball();
      break;
      case RANDOM_HARD_BALL_SPAWN:
        add_random_hard_ball();
      break;
      case RANDOM_ROTATED_BALL_SPAWN:
        add_random_rotated_ball();
      break;
      case RANDOM_ROTATING_BALL_SPAWN:
        add_random_rotating_ball();
      break;
      case RANDOM_FALLING_BALL_SPAWN:
        add_falling_ball();
      break;
      case SPECU_COLLIDING_BALL_SPAWN:
        add_specu_colliding_ball();
      break;
      case CONTACT_TREE_BALL_SPAWN:
        add_contact_tree_ball();
      break;
      case EPHEMERAL_BALL_SPAWN:
        add_ephemeral_ball();
      break;
      case FIREWORK_SPAWN:
        add_firework();
      break;
    }
  }
}


void init_tile_map() {
  printf("initializing tilemap\n");
  int width = WWIDTH / tile_size;
  int height = WHEIGHT / tile_size;
  int half_tile = tile_size / 2;
  area.width =1; area.height =1;
  for(int k = 0; k < area.width*area.height; ++k) {
    Map tm;
    tm.tiles.reserve(height*width);
    for(int j = 0; j < height; ++j) {
      for(int i = 0; i < width; ++i) {
        Tile tile;
        tile.flags = (j==0 || j==screen_height-1
                   || i==0 || i==screen_width-1) ? SOLID : VOID;
        tile.position = tposition_factory.create();       
        tile.position->x = ((k%area.width)*width+i)*tile_size+half_tile;
        tile.position->y = ((k/area.width)*height+j)*tile_size+half_tile;
        //if(tile.flags == SOLID) { 
          tile.shape = tshape_factory.create();       
          tile.mask = tmask_factory.create();       
          tile.shape->w = tile_size;
          tile.shape->h = tile_size;
          tile.mask->w = tile_size;
          tile.mask->h = tile_size;
        //}
        tm.tiles.push_back(tile);
      }
    } 
    area.tilemaps.push_back(tm);
  }
  tile_map_active = true;
}


void load_tile_map() {
  area = Area();
  area.load_from_tmx("data/tileset/basic.tmx");
  // area.load_from_tmx("data/tileset/basic2.tmx");
  tile_map_active = true;
}


void clear_tile_map() {
  printf("clearing tilemap\n");
  int width = WWIDTH / tile_size;
  int height = WHEIGHT / tile_size;
  for(int k = 0; k < area.width*area.height; ++k) {
    for(int j = 0; j < height; ++j) {
      for(int i = 0; i < width; ++i) {
        Tile& tile = area.tilemaps[k].tiles[width*j+i];
        tile.flags = VOID;
      }
    } 
  }
  tile_map_active = false;
}


void set_square_tile_map() {
  printf("setting tilemap\n");
  int width = WWIDTH / tile_size;
  int height = WHEIGHT / tile_size;
  area.width =1; area.height =1;
  for(int k = 0; k < area.width*area.height; ++k) {
    area.tilemaps[k].texture->loaded = false;
    for(int j = 0; j < height; ++j) {
      for(int i = 0; i < width; ++i) {
        Tile& tile = area.tilemaps[k].tiles[width*j+i];
        tile.flags = (j==0 || j==screen_height-1
                   || i==0 || i==screen_width-1) ? SOLID : VOID;
        tile.tileset_part = -1;
      }
    } 
  }
  tile_map_active = true;
}


void set_gravity(int ax, int ay) {
  gravity.ax = ax; gravity.ay = ay;
  printf("gravity set to (%d, %d)\n", (int)gravity.ax, (int)gravity.ay);
}


void spawn() {
  init_entities();
}


void respawn() {
  int entity_nb = entity_factory.nb_obj;
  for (int i = 0; i < entity_nb; ++i) {
    Entity& entity = entity_factory.objs[i];
    entity_factory.remove(entity);
  }
  init_entities();
}


void clear_all() {
  int entity_nb = entity_factory.nb_obj;
  for (int i = 0; i < entity_nb; ++i) {
    Entity& entity = entity_factory.objs[i];
    entity_factory.remove(entity);
  }
  player = NULL;
}


void apply_gravity() {
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if(entity.accel == NULL) { continue; }
    entity.speed->vx = entity.flags & GRAVITY_BOUND ? entity.speed->vx+gravity.ax : 0;
    entity.speed->vy = entity.flags & GRAVITY_BOUND ? entity.speed->vy+gravity.ay : 0;
  }
  if(player != NULL) { 
    if(!(player->flags & DEAD)) {
      player->speed->vx = player->flags & GRAVITY_BOUND ? player->speed->vx+gravity.ax : 0;
      player->speed->vy = player->flags & GRAVITY_BOUND ? player->speed->vy+gravity.ay : 0;
    }
  }
}


void cap_player_speed() {
  if(player == NULL) { return; }
  if(player->flags & DEAD) { return; }
  cap_speed(*player, speed_cap);
}


void cap_all_entities_speeds() {
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    cap_speed(entity, speed_cap);
  }
  if(player == NULL) { return; }
  if(!(player->flags & DEAD)) {
    cap_player_speed();
  }
}


void update_positions() {
  update_position_inertial(camera);
  realize_motion(camera);
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    update_position_inertial(entity);
  }
}


void do_collisions() {
  collision_loop(area);
}


void do_render() {
  if(tile_map_active) {
    area.render(camera); 
  }
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    render_rotated(entity, camera);
  }
}


void process_ephemerals() {
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if(!(entity.flags & EPHEMERAL)) { continue; }
    entity.lifespan--;
    if(entity.lifespan == 0) {
      entity_factory.remove(entity);
    }
  }
}


void apply_player_moves() {
  if(player == NULL) { return; }
  if(player->flags & DEAD) {
    return;
  }
  if(left_pushed) {
    player->accel->ax = -5;
  }
  if(right_pushed) {
    player->accel->ax = 5;
  }
  if(up_pushed) {
    if(player->flags & CAN_JUMP) {
      if(player->speed->can_jump) {
        player->accel->ay = -15; 
        player->speed->can_jump = false;
      }
    }else{
      player->accel->ay = -5;
    }
  }
  if(down_pushed) {
    if(!(player->flags & CAN_JUMP))
      player->accel->ay = 5;
  }
}


void apply_camera_moves() {
  if(a_pushed) {
    camera.accel->ax = -5;
  }
  if(d_pushed) {
    camera.accel->ax = 5;
  }
  if(w_pushed) {
    camera.accel->ay = -5;
  }
  if(s_pushed) {
    camera.accel->ay = 5;
  }
}


void loop() {
  running = true;
  while(running) { 
    clear_screen();
    apply_gravity();
    manage_inputs();
    apply_player_moves();
    apply_camera_moves();
    cap_player_speed();
    update_positions();
    do_collisions();
    process_ephemerals();
    do_render();
    SDL_GL_SwapBuffers(); // refresh screen
  }
}


int main(int argc, char** argv) {
  init_sdl();
  init_camera();
  init_entities();
  init_player();
  init_tile_map();
  load_tile_map();
  set_gravity(0, 2);
  printf("starting pong\n"); 
  loop();
  printf("stopping pong\n");
  return 0;
}
