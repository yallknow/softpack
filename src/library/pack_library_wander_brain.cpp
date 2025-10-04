#include "pack_library_wander_brain.hpp"

#include <cmath>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

wander_brain::wander_brain(const sf::Vector2f& c_velocity) noexcept
    : abstract::brain(c_velocity),
      m_jitterStep{0.0f},
      m_maxVelocity{0.0f, 0.0f} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

wander_brain::~wander_brain() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

wander_brain::wander_brain(wander_brain&& otherRLink) noexcept
    : abstract::brain(std::move(otherRLink)) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

wander_brain& wander_brain::operator=(wander_brain&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    abstract::brain::operator=(std::move(otherRLink));
  }

  return *this;
}

void wander_brain::set_jitter_step(const float c_jitterStep) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_jitterStep = c_jitterStep;
}

void wander_brain::set_max_velocity(
    const sf::Vector2f& c_maxVelocity) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_maxVelocity = c_maxVelocity;
}

void wander_brain::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  // (std::rand() % 3 - 1) -> [-1, 0, 1]
  const float c_newX{this->m_velocity.x +
                     ((std::rand() % 3 - 1) * m_jitterStep * c_dt)};
  const float c_newY{this->m_velocity.y +
                     ((std::rand() % 3 - 1) * m_jitterStep * c_dt)};

  if (std::abs(c_newX) < m_maxVelocity.x) {
    this->m_velocity.x = c_newX;
  }

  if (std::abs(c_newY) < m_maxVelocity.y) {
    this->m_velocity.y = c_newY;
  }
}

}  // namespace library
}  // namespace pack
