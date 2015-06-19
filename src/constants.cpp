#include "constants.h"

int nb_tiles = (WWIDTH / tile_size) * (WHEIGHT / tile_size);

int screen_width = WWIDTH / tile_size;
int screen_height = WHEIGHT / tile_size;

int sgn(int val) {
  return (0 < val) - (val < 0);
}
