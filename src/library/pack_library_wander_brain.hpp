#pragma once

#ifndef PACK_LIBRARY_WANDER_BRAIN
#define PACK_LIBRARY_WANDER_BRAIN

#include <SFML/System/Vector2.hpp>

#include "abstract/pack_library_abstract_brain.hpp"

namespace pack {
namespace library {

class wander_brain final : public abstract::brain {
 public:
  explicit wander_brain(const sf::Vector2f& c_velocity) noexcept;
  /*virtual*/ ~wander_brain() noexcept;

 public:
  explicit wander_brain(wander_brain&& otherRLink) noexcept;
  wander_brain& operator=(wander_brain&& otherRLink) noexcept;

 public:
  void set_jitter_step(const float c_jitterStep) noexcept;
  void set_max_velocity(const sf::Vector2f& c_maxVelocity) noexcept;

 private:
  void tick(const float c_dt) noexcept override;

 private:
  float m_jitterStep;
  sf::Vector2f m_maxVelocity;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_WANDER_BRAIN
