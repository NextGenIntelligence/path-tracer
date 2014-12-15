#pragma once
#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfArray.h>
#include <cmath>
#include <limits>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "randomness.h"

typedef glm::vec3 vec;
typedef glm::dvec3 dvec;

namespace math {

  inline float clamp(float x) {
    return x < 0 ? 0 : (x > 1 ? 1 : x);
  }

  /**
   * Taken from page 63 of Pharr & Humphreys' Physically-Based Rendering.
   */
  inline void coordSystem(const vec& v1, vec* v2, vec* v3) {
    if (fabsf(v1.x) > fabsf(v1.y)) {
      float invLen = 1.0f / sqrtf(v1.x * v1.x + v1.z * v1.z);
      *v2 = vec(-v1.z * invLen, 0.0f, v1.x * invLen);
    } else {
      float invLen = 1.0f / sqrtf(v1.y * v1.y + v1.z * v1.z);
      *v2 = vec(0.0f, v1.z * invLen, -v1.y * invLen);
    }
    *v3 = glm::cross(v1, *v2);
  }

  inline void copyData(int w, int h,
    const std::vector<std::vector<dvec>>& data,
    Imf::Array2D<Imf::Rgba>& exrData) {
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        Imf::Rgba& rgba = exrData[y][x];
        const dvec &p = data[y][x];
        rgba.r = p.x;
        rgba.g = p.y;
        rgba.b = p.z;
        rgba.a = 1.0;
      }
    }
  }

  inline bool isNearlyZero(float x) {
    return fabsf(x) < std::numeric_limits<float>::epsilon();
  }

  inline bool isPositive(float x) {
    return x > std::numeric_limits<float>::epsilon();
  }

  inline vec uniformSampleHemisphere(const vec normal, randomness& rng) {
    // Generate random ray in hemisphere of normal.
    // See <http://mathworld.wolfram.com/SpherePointPicking.html>
    float x1 = rng.nextNormalFloat();
    float x2 = rng.nextNormalFloat();
    float x3 = rng.nextNormalFloat();

    float denom = 1.0f / sqrt(x1 * x1 + x2 * x2 + x3 * x3);
    float y1 = fabsf(x1 * denom);
    float y2 = x2 * denom;
    float y3 = x3 * denom;

    const vec v1 = normal;
    vec v2;
    vec v3;
    coordSystem(v1, &v2, &v3);
    return (v1 * y1) + (v2 * y2) + (v3 * y3);
  }

}

struct ray {
  vec origin;
  vec direction;

  ray(vec o, vec d) : origin(o), direction(d) {}
  ray() : origin(0.0), direction(0.0) {}

  ray unit() const { return ray(origin, glm::normalize(direction)); }
  vec at(float d) const { return origin + direction * d; }
};

struct lightray : public ray {
  vec color;

  lightray(vec o, vec d, vec c) : ray(o, d), color(c) {}
  lightray(vec o, vec d) : ray(o, d), color(1) {}
  lightray() : ray(vec(0), vec(0)), color(1) {}

  bool isBlack() const {
    return math::isNearlyZero(glm::length(color));
  }

  float energy() const {
    return std::max(std::max(color.x, color.y), color.z);
  }

  bool isZeroLength() const {
    return math::isNearlyZero(glm::length(direction));
  }

  void kill() {
    origin = vec(0);
    direction = vec(0);
    color = vec(0);
  }
};

struct intersection {
  vec position;
  vec normal;
  float distance;

  intersection() : position(0), normal(0), distance(0.0f) {}
  intersection(vec p, vec n, float d)
    : position(p), normal(glm::normalize(n)), distance(d) {}
  bool hit() const { return distance > 0.0f; }
};
