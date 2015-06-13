#include "main.h"
#include <stdio.h>

#include "rectangle.h"
#include "position.h"
#include "aabb_collision.h"
#include "entity.h"

SDL_Event events;
bool running;

const int speed_factor = 4;
const int size_factor = 20;

const int starting_entity_nb = 15;

//int mode = FIREWORK_SPAWN; 
int mode = 6; 



void manage_inputs() {
  while(SDL_PollEvent(&events)) {
    if(events.type == SDL_QUIT)
      running = false;
    if(events.type ==  SDL_KEYUP) 
      key_up(events.key.keysym.sym,events.key.keysym.mod,
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
    case SDLK_r:
      respawn();
    break;
    case SDLK_d:
      remove_random_ball();
    break;
    case SDLK_p:
      print_debug_info();
    break;
  }
}


void add_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.position()->x = 0;
  entity.position()->y = 0;
  entity.speed()->vx = speed_factor;
  entity.speed()->vy = speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
  entity.flags = GHOST;
}


void add_random_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.position()->x = rand() % WWIDTH;
  entity.position()->y = rand() % WHEIGHT;
  entity.speed()->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed()->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
  entity.flags = GHOST;
}


void add_hard_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.position()->x = 0;
  entity.position()->y = 0;
  entity.speed()->vx = speed_factor;
  entity.speed()->vy = speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
}


void add_random_hard_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.position()->x = rand() % WWIDTH;
  entity.position()->y = rand() % WHEIGHT;
  entity.speed()->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed()->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
}


void add_random_rotated_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.position()->x = rand() % WWIDTH;
  entity.position()->y = rand() % WHEIGHT;
  entity.speed()->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed()->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
  entity.position()->theta = 2 * PI * (float) (rand() % 100) / 100;
}


void add_random_rotating_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.position()->x = rand() % WWIDTH;
  entity.position()->y = rand() % WHEIGHT;
  entity.speed()->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed()->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
  entity.position()->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed()->omega = PI *( (float) (rand() % 20) / 250);
}


void add_falling_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.accel_id() = accel_factory.create(entity);
  entity.position()->x = rand() % WWIDTH;
  entity.position()->y = rand() % WHEIGHT;
  entity.speed()->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed()->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
  entity.position()->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed()->omega = PI *( (float) (rand() % 20) / 250);
  entity.flags = GRAVITY_BOUND;
  entity.accel()->friction = 1;
}


void add_ephemeral_ball() {
  Entity& entity = entity_factory.create();
  entity.position_id() = position_factory.create(entity);
  entity.speed_id() = speed_factory.create(entity);
  entity.shape_id() = shape_factory.create(entity);
  entity.mask_id() = mask_factory.create(entity);
  entity.accel_id() = accel_factory.create(entity);
  entity.position()->x = rand() % WWIDTH;
  entity.position()->y = rand() % WHEIGHT;
  entity.speed()->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed()->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape()->w = size_factor;
  entity.shape()->h = size_factor;
  entity.mask()->w = size_factor;
  entity.mask()->h = size_factor;
  entity.position()->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed()->omega = PI *( (float) (rand() % 20) / 250);
  entity.flags = GRAVITY_BOUND | EPHEMERAL;
  entity.lifespan = 100; // entity will live 100 frames
  entity.accel()->friction = 1.0;
}


void add_firework() {
  int x = rand() % WWIDTH;
  int y = rand() % WHEIGHT;
  int n = 5 + rand() % 5;
  for(int i =0; i< n; ++i) {
    Entity& entity = entity_factory.create();
    entity.position_id() = position_factory.create(entity);
    entity.speed_id() = speed_factory.create(entity);
    entity.shape_id() = shape_factory.create(entity);
    entity.mask_id() = mask_factory.create(entity);
    entity.accel_id() = accel_factory.create(entity);
    entity.position()->x = x;
    entity.position()->y = y;
    entity.speed()->vx = rand() % 20*speed_factor - 10*speed_factor;
    entity.speed()->vy = rand() % 20*speed_factor - 10*speed_factor;
    entity.shape()->w = size_factor;
    entity.shape()->h = size_factor;
    entity.mask()->w = size_factor;
    entity.mask()->h = size_factor;
    entity.position()->theta = 2 * PI * (float) (rand() % 100) / 100;
    entity.speed()->omega = PI *( (float) (rand() % 20) / 250);
    entity.flags = GRAVITY_BOUND | EPHEMERAL | GHOST;
    entity.lifespan = 50; 
    entity.accel()->friction = 0.5;
  }
}


void remove_random_ball() {
  if(entity_factory.nb_entity <= 0) { return; }
  int id_to_remove = rand() % entity_factory.nb_entity;
  Entity& entity_to_remove = entity_factory.entities[id_to_remove];
  entity_factory.remove(entity_to_remove);
}


void print_debug_info() {
  for (int i = 0; i < entity_factory.nb_entity; ++i) {
    printf("entity %d, address %d :\n", i, &(entity_factory.entities[i]));
    for (int c = 0; c < MAX_COMPONENT_TYPE; ++c) {
      printf("  comp_id[%d] = %d", c, entity_factory.entities[i].comp_id[c]);
    }
    printf("\n");
    printf("  point_back %d\n", entity_factory.entities[i].position()->entity);
  }
}


void switch_mode() {
  ++mode;
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
      case EPHEMERAL_BALL_SPAWN:
        add_ephemeral_ball();
      break;
      case FIREWORK_SPAWN:
        add_firework();
      break;
    }
  }
}


void respawn() {
  int entity_nb = entity_factory.nb_entity;
  for (int i = 0; i < entity_nb; ++i) {
    Entity& entity = entity_factory.entities[i];
    entity_factory.remove(entity);
  }
  init_entities();
}


void apply_gravity() {
  for (int i = 0; i < entity_factory.nb_entity; ++i) {
    Entity& entity = entity_factory.entities[i];
    if(entity.accel() == NULL) { continue; }
    entity.accel()->ay = entity.flags & GRAVITY_BOUND ? 2 : 0;
  }
}


void update_positions() {
  for (int i = 0; i < entity_factory.nb_entity; ++i) {
    Entity& entity = entity_factory.entities[i];
    update_position_inertial(entity);
  }
}


void do_collisions() {
  for (int i = 0; i < entity_factory.nb_entity; ++i) {
    Entity& entity = entity_factory.entities[i];
    check_collision(entity);
  }
}


void do_render() {
  for (int i = 0; i < entity_factory.nb_entity; ++i) {
    Entity& entity = entity_factory.entities[i];
    render(entity);
  }
}


void process_ephemerals() {
  for (int i = 0; i < entity_factory.nb_entity; ++i) {
    Entity& entity = entity_factory.entities[i];
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
  init_entities();
  printf("starting pong\n"); 
  loop();
  printf("stopping pong\n");
  return 0;
}
