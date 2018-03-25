#include "SDK.h"

class Aimbot {
 public:
  Aimbot();
  static Aimbot &Instance();
  void aimAt();
  void resetIndex();
 private:
  bool valid(int);
  float getFOV(const Vector &, const Vector &, const Vector &);
  IClient *lplayer;
  float bestTargetFOV;
  Vector end;
  int bestIndex;
};
