#pragma once

#include "Defines.h"
#include "IClientNetworkable.h"
#include "Recv.h"

class ClientClass;

typedef IClientNetworkable *(*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable *(*CreateEventFn)();

class ClientClass {
 public:
  CreateClientClassFn m_pCreateFn;
  CreateEventFn m_pCreateEventfn;
  char *m_pNetworkName;
  RecvTable *m_pRecvTable;
  ClientClass *m_pNext;
  int m_ClassID;
};
