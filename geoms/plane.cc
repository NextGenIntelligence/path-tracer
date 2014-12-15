#include "plane.h"
#include <memory>

geoms::plane::plane(vec o, vec n, materialptr m)
  : origin(o), normal(glm::normalize(n)), geom(m)
{
  computeTangents();
}

geoms::plane::plane(vec o, vec n)
  : origin(o), normal(glm::normalize(n)), geom()
{
  computeTangents();
}

geoms::plane::plane() : origin(0.0), normal(0.0, 1.0, 0.0) {
  computeTangents();
}

void geoms::plane::computeTangents() {
  math::coordSystem(normal, &tangent, &cotangent);
}

intersection geoms::plane::intersect(const ray& r) const {
  // See Wikipedia:
  // <http://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection>

  float denom = glm::dot(r.unit().direction, normal);
  if (denom != 0.0f) {
    float d = glm::dot(origin - r.origin, normal) / denom;

    if (math::isPositive(d)) {
      return intersection(r.unit().at(d), normal, tangent, cotangent, d);
    }
  }

  // Either no isect was found or it was behind us.
  return intersection();
}

geomptr geoms::plane::make(vec o, vec n, materialptr m) {
  return std::make_shared<plane>(o, n, m);
}

geomptr geoms::plane::make(vec o, vec n) {
  return std::make_shared<plane>(o, n);
}

geomptr geoms::plane::make() {
  return std::make_shared<plane>();
}
