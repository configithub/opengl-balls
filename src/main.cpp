#include "main.h"
#include "collision_system.h"

SDL_Event events;
bool running;

const int speed_factor = 4;
const int size_factor = 20;

bool tile_map_active = true;

//const int starting_entity_nb = 0;
const int starting_entity_nb = 15;

int mode = CONTACT_TREE_BALL_SPAWN; 
Area area(2,1);
Accel gravity;
Entity camera;


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
  }
}


void key_down(SDLKey sym, SDLMod mod, Uint16 unicode) { 
  switch(sym) {
    case SDLK_w:
      camera.accel->ay = -0.2;
    break;
    case SDLK_a:
      camera.accel->ax = -0.2;
    break;
    case SDLK_s:
      camera.accel->ay = 0.2;
    break;
    case SDLK_d:
      camera.accel->ax = 0.2;
    break;
  }
}


void init_camera() {
  camera.position = position_factory.create();
  camera.speed = speed_factory.create();
  camera.accel = accel_factory.create();
  camera.shape = shape_factory.create();
  //camera.mask = mask_factory.create();
  camera.position->x = 15;
  camera.position->y = 0;
  camera.shape->w = WWIDTH;
  camera.shape->h = WHEIGHT;
  //camera.mask->w = WWIDTH;
  //camera.mask->h = WHEIGHT;
  camera.flags = GHOST;
  camera.accel->friction = 1;
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
  entity.position->x = 0;
  entity.position->y = 0;
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
  entity.position->y = WHEIGHT / 2;
  entity.speed->vx = 0;
  entity.speed->vy = 0;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.flags = GRAVITY_BOUND | SPECULATIVE_COLLIDE | CONTACT_TREE;
  entity.accel->friction = 1;
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
  for(int k = 0; k < area.width*area.height; ++k) {
    TileMap tm;
    tm.tiles.reserve(height*width);
    for(int j = 0; j < height; ++j) {
      for(int i = 0; i < width; ++i) {
        Tile tile;
        tile.flags = (j==0 || j==screen_height-1
                   || i==0 || i==screen_width-1) ? SOLID : VOID;
        tile.position = tposition_factory.create();       
        tile.position->x = ((k%area.width)*width+i)*tile_size+half_tile;
        tile.position->y = ((k/area.width)*height+j)*tile_size+half_tile;
        if(tile.flags == SOLID) { 
          tile.shape = tshape_factory.create();       
          tile.mask = tmask_factory.create();       
          tile.shape->w = tile_size;
          tile.shape->h = tile_size;
          tile.mask->w = tile_size;
          tile.mask->h = tile_size;
        }
        tm.tiles.push_back(tile);
      }
    } 
    area.tilemaps.push_back(tm);
  }
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
  for(int k = 0; k < area.width*area.height; ++k) {
    for(int j = 0; j < height; ++j) {
      for(int i = 0; i < width; ++i) {
        Tile& tile = area.tilemaps[k].tiles[width*j+i];
        tile.flags = (j==0 || j==screen_height-1
                   || i==0 || i==screen_width-1) ? SOLID : VOID;
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
}


void apply_gravity() {
  for (int i = 0; i < entity_factory.nb_obj; ++i) {
    Entity& entity = entity_factory.objs[i];
    if(entity.accel == NULL) { continue; }
    entity.accel->ax = entity.flags & GRAVITY_BOUND ? gravity.ax : 0;
    entity.accel->ay = entity.flags & GRAVITY_BOUND ? gravity.ay : 0;
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
  area.render(camera); 
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


void loop() {
  running = true;
  while(running) { 
    clear_screen();
    manage_inputs();
    apply_gravity();
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
  init_tile_map();
  set_gravity(0, 2);
  printf("starting pong\n"); 
  loop();
  printf("stopping pong\n");
  return 0;
}
