#include "constants.h"
#include <stdio.h>

int nb_tiles = (WWIDTH / tile_size) * (WHEIGHT / tile_size);

int screen_width = WWIDTH / tile_size;
int screen_height = WHEIGHT / tile_size;

int sgn(int val) {
  return (0 < val) - (val < 0);
}

int fsgn(float val) {
  int p = 0.0 < val ? 1 : 0;
  int m = val < 0.0 ? 1 : 0;
  // printf("p-m: %d\n", p-m);
  return p - m;
}
