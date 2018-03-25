#pragma once

#include "Defines.h"

class model_t;

class IModelInfoClient {
 public:
  model_t *GetModel(int index) {
    return callVirtualFunc<model_t* (*)(void *, int)>(this, 1)(this, index);
  }
};
