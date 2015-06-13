#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "constants.h"


class Entity;

class Component {
public:
  Component(): type(0), entity(NULL) {}
  int type;
  Entity* entity;
  void restore_entity_id(int comp_id);
};


template <class T> class ComponentFactory {
public:
  friend class Component;
  friend class Entity;
  ComponentFactory(int itype): nb_component(0) {
    type = itype;
  }

  int create(Entity& ent) {
    T& compo = components[nb_component];
    compo = T();
    compo.entity = &ent;
    compo.type = type;
    ++nb_component;
    //return nb_component++;
    return nb_component-1;
  }

  void remove(int comp_id) {
    if(nb_component <= 0) { return; }
    T& component = components[comp_id];
    component = components[nb_component-1];
    component.restore_entity_id(comp_id);
    --nb_component;
  }

private:
  int nb_component;
  int type;
  T components[max_entity_nb];
};


#endif
