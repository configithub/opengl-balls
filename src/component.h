#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "constants.h"

class Entity;

class Component {
public:
  Entity* entity;
  Component(): entity(NULL) {}
};


#endif
