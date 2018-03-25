#include "SDK.h"

// ~/.steam/steam/steamapps/common/Counter-Strike Global Offensive/
#define CLIENT_PATH "csgo/bin/linux64/client_client.so"
#define ENGINE_PATH "bin/linux64/engine_client.so"

IBaseClient *Interfaces::m_pClient = nullptr;
IClientMode *Interfaces::m_pClientMode = nullptr;
IClientList *Interfaces::m_pEntityList = nullptr;
IEngineClient *Interfaces::m_pEngine = nullptr;

IBaseClient *Interfaces::Client() {
  if (!m_pClient) {
    CreateInterface clientFactory = (CreateInterface)dlsym(dlopen(CLIENT_PATH, RTLD_LAZY), "CreateInterface");
    m_pClient = (IBaseClient *)clientFactory("VClient017", nullptr);
  }
  return m_pClient;
}

IClientList *Interfaces::EntityList() {
  if (!m_pEntityList) {
    CreateInterface clientFactory = (CreateInterface)dlsym(dlopen(CLIENT_PATH, RTLD_LAZY), "CreateInterface");
    m_pEntityList = (IClientList *)clientFactory("VClientEntityList003", nullptr);
  }
  return m_pEntityList;
}

IEngineClient *Interfaces::Engine() {
  if (!m_pEngine) {
    CreateInterface engineFactory = (CreateInterface)dlsym(dlopen(ENGINE_PATH, RTLD_LAZY), "CreateInterface");
    m_pEngine = (IEngineClient *)engineFactory("VEngineClient014", nullptr);
  }
  return m_pEngine;
}
