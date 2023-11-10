#include "ad_type.h"


#include "Box.hh"


#include <iostream>
#include <sstream>
#include <cmath>


Box::Box (const std::string& name, int indxMat, G4double pX, G4double pY, G4double pZ)
: fName(name),
  fMaterialIndx(indxMat),
  fDx(pX),
  fDy(pY),
  fDz(pZ) {
  fDelta = 0.5*kCarTolerance;
  // check minimum size
  if (pX < 2*kCarTolerance ||
      pY < 2*kCarTolerance ||
      pZ < 2*kCarTolerance)  {
    std::ostringstream message;
    message << "Dimensions too small for Solid: " << GetName() << "!" << std::endl
            << "     hX, hY, hZ = " << pX << ", " << pY << ", " << pZ;
    std::cout << message.str();
  }
}


void Box::SetHalfLength(G4double val, int idx) {
   // limit to thickness of surfaces
  if (val > 2*kCarTolerance) {
    switch (idx) {
      case 0: fDx = val;
            break;
      case 1: fDy = val;
              break;
      case 2: fDz = val;
              break;
    };
  } else {
    std::ostringstream message;
    message << "Dimension too small for solid: " << GetName() << "!"
            << std::endl
            << "      val = " << val << std::endl
            << "      idx = " << idx;
    std::cout << message.str();
  }
}

G4double Box::GetHalfLength(int idx) const {
  switch (idx) {
    case 0: return fDx;
    case 1: return fDy;
    case 2: return fDz;
  };
  return 0;
}


// p should be in local coordinates
// returns zero if p is outside of the box or within tolerance
G4double Box::DistanceToOut(G4double* p, G4double *v) const {
  // Check if point is not inside and traveling away: zero
  // Note: eitehr in surafece or outside
  if ((std::abs(p[0]) - fDx) >= -fDelta && p[0]*v[0] > 0) {
    return 0.0;
  }
  if ((std::abs(p[1]) - fDy) >= -fDelta && p[1]*v[1] > 0) {
    return 0.0;
  }
  if ((std::abs(p[2]) - fDz) >= -fDelta && p[2]*v[2] > 0) {
    return 0.0;
  }
  // Find intersection
  //
  const G4double vx = v[0];
  const G4double tx = (vx == 0) ? 1.0E+20 : (G4double)((std::copysign(fDx,vx) - p[0])/vx);
  //
  const G4double vy = v[1];
  const G4double ty = (vy == 0) ? tx : (G4double)((std::copysign(fDy,vy) - p[1])/vy);
  const G4double txy = std::min(tx,ty);
  //
  const G4double vz = v[2];
  const G4double tz = (vz == 0) ? txy : (G4double)((std::copysign(fDz,vz) - p[2])/vz);
  const G4double tmax = std::min(txy,tz);
  //
  return tmax;
}


G4double Box::DistanceToOut(G4double* p) const {
  G4double dist = std::min( std::min(
                   fDx-std::abs(p[0]),
                   fDy-std::abs(p[1]) ),
                   fDz-std::abs(p[2]) );
  return (dist > 0) ? dist : 0.0;
}


/*
EInside Box::Inside(G4double rx, G4double ry, G4double rz) const {
  G4double dist = std::max ( std::max (
                  std::abs(rx)-fDx,
                  std::abs(ry)-fDy),
                  std::abs(rz)-fDz);
  return (dist > fDelta) ? kOutside : ((dist > -fDelta) ? kSurface : kInside);
}
EInside Box::Inside(G4double* r) const {
  G4double dist = std::max ( std::max (
                  std::abs(r[0])-fDx,
                  std::abs(r[1])-fDy),
                  std::abs(r[2])-fDz);
  return (dist > fDelta) ? kOutside : ((dist > -fDelta) ? kSurface : kInside);
}
*/
