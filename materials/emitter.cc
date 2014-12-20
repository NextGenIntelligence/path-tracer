#include "emitter.h"

materials::emitter::emitter(vec c) : color(c) {}

lightray materials::emitter::propagate(
  const lightray& incoming,
  const intersection& /* isect */,
  randomness& /* rng */
) const {
  return lightray(
    vec(0, 0, 0),
    vec(0, 0, 0),
    incoming.color.cwiseProduct(color)
  );
}
