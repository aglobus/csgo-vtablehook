#include "Aimbot.h"
#include <unistd.h>

Aimbot::Aimbot() {
  resetIndex();
}

Aimbot& Aimbot::Instance() {
  static Aimbot instance;
  return instance;
}

void Aimbot::resetIndex() {
  bestIndex = -1;
}

void Aimbot::aimAt() {
  lplayer = Interfaces::EntityList()->getClient(Interfaces::Engine()->getLocalPlayer());

  bestTargetFOV = 2.0f;
  Vector va;

  if (!lplayer)
    return;

  if (!lplayer->IsAlive())
    return;

  // GetBestTarget
  for (int i = 1; i < 32; i++) {
    if (valid(i)) {
      // Grab the target that is closest to 0 and less than our FOV

      Interfaces::Engine()->GetViewAngles(va);
      float fov = getFOV(va, lplayer->GetEyePos(), end);
      if (fov < bestTargetFOV) {
        bestTargetFOV = fov;
        bestIndex = i;
      }
    }
  }

  //Drop Target
  if (!valid(bestIndex))
    bestIndex = -1;

  if (bestIndex != -1) {
    //Do the actual aiming
    Vector direction = end - lplayer->GetEyePos();
    NormalizeVector(direction);
    Vector aim;
    VectorAngles(direction, aim);

    //recoil
    aim -= *lplayer->AimPunch() * 2.0f;

    //smoothing

    float smoothing = 10.0f;
    Vector delta = va - aim;
    AngleNormalize(delta);
    aim = va - delta / smoothing;

    aim.z = 0.0f;

    ClampAngles(aim);

    Interfaces::Engine()->SetViewAngles(aim);
  }
}

bool Aimbot::valid(int index) {
  IClient *ent = Interfaces::EntityList()->getClient(index);

  if (!lplayer || !ent || !ent->IsAlive() || ent->GetHealth() < 1 || ent->isDormant() || ent->GetTeamNum() == lplayer->GetTeamNum())
    return false;

  end = ent->GetBonePosition(6); // 6 = Head

  if (end.IsZero())
    return false;

  //TODO isVisible check

  return true;
}

void MakeVector(const Vector &in, Vector &out) {
  float pitch = DEG2RAD(in.x);
  float yaw = DEG2RAD(in.y);
  float temp = cos(pitch);

  out.x = -temp * -cos(yaw);
  out.y = sin(yaw) * temp;
  out.z = -sin(pitch);
}

float Aimbot::getFOV(const Vector &viewangles, const Vector &start, const Vector &end) {
  Vector ang, aim;

  Vector dir = end - start;
  dir = dir.Normalized();
  VectorAngles(dir, ang);

  MakeVector(viewangles, aim);
  MakeVector(ang, ang);

  return RAD2DEG(acos(aim.Dot(ang)) / aim.LengthSqr());
}
