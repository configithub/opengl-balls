#ifndef _ANGLE_H_
#define _ANGLE_H_

#include "component.h"

class Angle : public Component {
public:
  float theta;
  Angle(): theta(0.0) {}
};

#endif
