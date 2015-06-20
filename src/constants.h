#ifndef _CONSTANSTS_H_
#define _CONSTANSTS_H_

#include <cstddef>

#define WWIDTH 640 // 40 tiles width
#define WHEIGHT 480 // 30 tiles height
#define tile_size 16
#define BPP_DEPTH 16
#define max_entity_nb 10000
#define max_obj_nb 10000

#define PI 3.14159265

#define collision_iteration_nb 10
#define collision_resolve_nb 1

// number of tiles per screen
extern int nb_tiles;

// screen dimensions in number of tiles :
extern int screen_width;
extern int screen_height;

int sgn(int val); // helper function to get the sign of an int

#endif
