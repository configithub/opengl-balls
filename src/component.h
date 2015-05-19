#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "constants.h"

class Entity;

class Component {
public:
  Entity* entity;
  Component(): entity(NULL) {}
};

template <class T> class ComponentFactory {
public:
  ComponentFactory(): nb_component(0) {}
  T* create() {
    T& compo = components[nb_component];
    ++nb_component;
    return &compo;
  }
private:
  int nb_component;
  T components[max_entity_nb];
};

#endif
