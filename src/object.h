#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "constants.h"
#include <stdio.h>

class Object {
public:
  int id;
  int flags;
  int lifespan;
  Object() : id(0), flags(0), lifespan(-1) {}

};


template <class T> class Factory {
public:

  Factory(): nb_obj(0), next_id(0) {}

  int nb_obj;
  int next_id;
  T objs[max_obj_nb];

  T& create() {
    T& obj = objs[nb_obj];
    obj = T();
    obj.id = next_id;
    printf("adding obj : %d\n", obj.id);
    ++next_id;
    ++nb_obj;
    return obj;
  }

  void remove(T& obj) {
    if(nb_obj <= 0) { return; }
    printf("removing obj : %d\n", obj.id);
    obj.remove();
    obj = objs[nb_obj-1];
    --nb_obj;
  }

};


#endif
