#pragma once

#include "Defines.h"
#include "IBaseClient.h"
#include "IClientList.h"
#include "IEngineClient.h"
#include "IClientMode.h"

#include "Debug.h"


class Interfaces {
public:
  static IBaseClient *Client();
  static IClientMode *ClientMode();
  static IClientList *EntityList();
  static IEngineClient *Engine();

private:
  static IBaseClient *m_pClient;
  static IClientMode *m_pClientMode;
  static IClientList *m_pEntityList;
  static IEngineClient *m_pEngine;
};
