#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "constants.h"


class Component {
public:
  Component() {}
};

template <class T> class ComponentFactory {
public:
  ComponentFactory(): nb_component(0),
                      nb_dead_component(0) {}

  T* create() {
    if(nb_dead_component > 0) {
      // revive a dead component
      T* compo = component_graveyard[nb_dead_component-1];
      *compo = T();
      --nb_dead_component;
      return compo;
    }
    T& compo = components[nb_component];
    ++nb_component;
    return &compo;
  }

  void remove(T* compo) {
    if(nb_component == 0) { return; }
    component_graveyard[nb_dead_component] = compo;
    ++nb_dead_component;
  }

private:
  int nb_component;
  T components[max_entity_nb];
  int nb_dead_component;
  T* component_graveyard[max_entity_nb];
};

#endif
