#pragma once

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

enum TraceType_t {
    TRACE_EVERYTHING = 0,
    TRACE_WORLD_ONLY,// NOTE: This does *not* test static props!!!
    TRACE_ENTITIES_ONLY,// NOTE: This version will *not* test static props
    TRACE_EVERYTHING_FILTER_PROPS,// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
  };

struct cplane_t
{
  Vector normal;
  float dist;
  char type;
  char signbits;
  char pad[2];
};

struct csurface_t
{
  const char *name;
  short surfaceProps;
  unsigned shortflags;
};

class __attribute__ ((aligned(16))) VectorAligned : public Vector {
 public:
  VectorAligned& operator=(const Vector &vOther) {
    Init(vOther.x, vOther.y, vOther.z);
    return *this;
  }
  float w;
};

struct Ray_t {
  VectorAligned start;
  VectorAligned delta;
  VectorAligned startOffset;
  VectorAligned extents;

  const matrix3x4_t *worldAxisTransform;

  bool isRay;
  bool isSwept;

  Ray_t() : worldAxisTransform(0) {}

  void init(Vector &begin, Vector &end) {
    delta = end - begin;

    isSwept = (delta.LengthSqr() != 0);

    extents.Init();
    worldAxisTransform = 0;
    isRay = true;

    startOffset.Init();
    VectorCopy(begin, start);
  }

  void Init(Vector &begin, Vector &end, Vector &mins, Vector &maxs) {
    delta = end - begin;

    worldAxisTransform = 0;
    isSwept = (delta.LengthSqr() != 0);

    extents = maxs - mins;
    extents *= 0.5f;
    isRay = (extents.LengthSqr() < 1e-6);

    startOffset = maxs + mins;
    startOffset *= 0.5f;
    start = begin + startOffset;
    startOffset *= -1.0f;
  }
};

class ITraceFilter {
 public:
  virtual bool ShouldHitEntity(void *pEntity, int contentMask) = 0;
  virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter {
 public:
  virtual bool ShouldHitEntity(void *pEntity, int contentMask) {
    return !(pEntity == pSkip);
  }

  virtual TraceType_t GetTraceType() const {
    return TRACE_EVERYTHING;
  }

  void *pSkip;
};

class CBaseTrace {
 public:
  bool IsDispSurface(void){ return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
  bool IsDispSurfaceWalkable(void){ return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
  bool IsDispSurfaceBuildable(void){ return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
  bool IsDispSurfaceProp1(void){ return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
  bool IsDispSurfaceProp2(void){ return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

  Vector startpost;
  Vector endpos;
  cplane_t plane;
  float fraction;
  int contents;
  unsigned short dispFlags;
  bool allsolid;
  bool startsolid;

  CBaseTrace() {}
};

class CGameTrace : public CBaseTrace {
 public:
  bool DidHitWorld() const;
  bool DidHitNonWorldEntity() const;
  int GetEntityIndex() const;
  bool DidHit() const {
    return fraction < 1 || allsolid || startsolid;
  }

  float fractionleftsolid;
  csurface_t surface;
  int hitgroup;
  short physicsbones;
  unsigned short worldSurfaceIndex;
  IClient* m_pEnt;
  int hitbox;
  CGameTrace() {}
  CGameTrace(const CGameTrace &other);
};


class IEngineTrace {
 public:
  void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, CGameTrace *pTrace) {
    return callVirtualFunc<void(*)(void *, Ray_t, unsigned int, ITraceFilter *, CGameTrace *)>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
  }
};
