#pragma once

#include "Vector.h"
#include "Defines.h"

#include "Debug.h"

/* Consult netvar dump for these values */

#define SPOTTED   0xECD //DT_BaseEntity
#define TEAM_NUM  0x128 //DT_BaseEntity
#define IS_ALIVE  0x293 //DT_BasePlayer
#define HEALTH    0x134 //DT_BasePlayer

#define EYE_ANGLES  0xB30C //DT_CSPlayer

#define VEC_ORIGIN          0x16C
#define VEC_VIEW_OFFSET_0   0x13C

#define VIEW_PUNCH_ANGLE    0x3760
#define AIM_PUNCH_ANGLE     0x376C


#define SETUP_BONES 0xb61f70

class model_t;

class IHandleEntity {
	public:
		virtual ~IHandleEntity() {};
};
 
class IClientUnknown: public IHandleEntity {};

class IClientRenderable {
	public:
		virtual ~IClientRenderable() {};
		bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0) {
			return callVirtualFunc<bool(*)(void*, matrix3x4_t*, int, int, float)>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
		}

  	model_t *GetModel() {
    	return callVirtualFunc<model_t *(*)(void *)>(this, 8)(this);
  	}
};

/*
class IClientNetworkable {
	public:
		virtual ~IClientNetworkable() {};
};
*/

class IClientThinkable {
	public:
		virtual ~IClientThinkable() {};
};

class IClient : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {

  template<class T> inline T GetFieldValue(int offset) {
    return *(T*)((long)this + offset);
  }

  template<class T> T* GetFieldPointer(int offset) {
  	return (T*)((long)this + offset);
  }

public:

	virtual ~IClient() {};

  bool* getspotted() {
    return (bool*)(this + SPOTTED);
  }

  int GetTeamNum() {
    return GetFieldValue<int>(TEAM_NUM);
  }

  bool IsAlive() {
    return GetFieldValue<bool>(IS_ALIVE) == 0;
  }

  int GetHealth() {
    return GetFieldValue<int>(HEALTH);
  }

  Vector GetViewOffset() {
    return GetFieldValue<Vector>(VEC_VIEW_OFFSET_0);
  }

  Vector GetOrigin() {
    return GetFieldValue<Vector>(VEC_ORIGIN);
  }

  Vector GetEyePos() {
    return GetOrigin() + GetViewOffset();
  }

  Vector *ViewPunch() {
    return GetFieldPointer<Vector>(VIEW_PUNCH_ANGLE);
  }

  Vector *AimPunch() {
    return GetFieldPointer<Vector>(AIM_PUNCH_ANGLE);
  }

  Vector GetBonePosition(int bone) {
    matrix3x4_t matrix[128];
    if (this->SetupBones(matrix, 128, 0x100, 0)) {
      return Vector(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);
    }
    else return Vector(0,0,0);
  }
};

class IClientList {
public:
  inline IClient* getClient(int index) {
    return callVirtualFunc<IClient*(*)(void *, int)>(this, 3)(this, index);
  }

  inline IClient* getClientFromHandle(long handle) {
    return callVirtualFunc<IClient*(*)(void *, long)>(this, 4)(this, handle);
  }
};
