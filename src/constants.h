#ifndef _CONSTANSTS_H_
#define _CONSTANSTS_H_

#include <cstddef>

#define WWIDTH 800
#define WHEIGHT 600
#define BPP_DEPTH 16
#define max_entity_nb 10000
#define max_node_nb 10000

#define PI 3.14159265

// component types
typedef enum {
  POSITION = 0,
  SPEED,
  SHAPE,
  ACCEL,
  MASK,
  MAX_COMPONENT_TYPE
} EN_Component_type;

// entity flags (bitset)
typedef enum {
  DEAD =  2,
  GHOST = 4,
  GRAVITY_BOUND = 8,
  EPHEMERAL = 16
} EN_Flag;


#endif
