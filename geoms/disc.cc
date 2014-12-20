#include "disc.h"

geoms::disc::disc(material* m, vec o, vec n, float r)
  : geom(m), radiusSquared(r * r), origin(o), normal(n.normalized()),
    radius(r)
{
  math::coordSystem(normal, &tangent, &binormal);
}

geoms::disc::disc(const geoms::disc& other)
  : geom(other.mat), radiusSquared(other.radiusSquared),
    origin(other.origin), normal(other.normal), radius(other.radius) {}

bool geoms::disc::intersect(const ray& r, intersection* isectOut) const {
  // See Wikipedia:
  // <http://en.wikipedia.org/wiki/Line%E2%80%93disc_intersection>

  float denom = r.direction.dot(normal);
  if (denom != 0.0f) {
    float d = (origin - r.origin).dot(normal) / denom;

    if (math::isPositive(d)) {
      // In the plane, but are we in the disc?
      vec isectPoint = r.at(d);
      if ((isectPoint - origin).squaredNorm() < radiusSquared) {
        // In the disc.
        if (isectOut) {
          *isectOut = intersection(isectPoint, normal, tangent, binormal, d);
        }
        
        return true;
      }
    }
  }

  // Either no isect was found or it was behind us.
  return false;
}

bbox geoms::disc::bounds() const {
  vec tr = tangent * radius;
  vec br = binormal * radius;

  bbox b(origin + tr + br, origin - tr - br);
  b.expand(origin + tr - br);
  b.expand(origin - tr + br);

  return b;
}
