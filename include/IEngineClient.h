#pragma once

class IEngineClient {
 public:
  inline void GetScreenSize(int &width, int &height)  {
    return callVirtualFunc<void(*)(void *, int &, int &)>(this, 5)(this, width, height);
  }

  inline int getLocalPlayer(void) {
    return callVirtualFunc<int(*)(void *)>(this, 12)(this);
  }

  inline bool con_visible(void) {
    return callVirtualFunc<bool(*)(void *)>(this, 11)(this);
  }

  inline float GetLastTimeStamp(void) {
    return callVirtualFunc<float(*)(void *)>(this, 14)(this);
  }

  inline void GetViewAngles(QAngle &va) {
    return callVirtualFunc<void(*)(void *, QAngle &)>(this, 18)(this, va);
  }

  inline void SetViewAngles(QAngle &va) {
    return callVirtualFunc<void(*)(void *, QAngle &)>(this, 19)(this, va);
  }

  inline VMatrix& WorldToScreenMatrix(void) {
    return callVirtualFunc<VMatrix&(*)(void *)>(this, 37)(this);
  }
};
