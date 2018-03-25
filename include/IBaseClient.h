#pragma once

#include "ClientClass.h"

class IBaseClient {
public:

  inline ClientClass* GetAllClasses() {
    typedef ClientClass * (* GetAllClassesFn)(void *);
    return callVirtualFunc<GetAllClassesFn>(this, 8)(this);
    // return callVirtualFunc<ClientClass* (*) (void *)>(this, 8)(this);
  }

  /* virtual ClientClass* GetAllClasses(void) = 0; */
};
