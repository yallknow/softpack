#include "pack_library_wander_brain.hpp"

#include <stdlib.h>

#include <cstdlib>
#include <type_traits>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

wander_brain::wander_brain(const sf::Vector2f& c_velocity,
                           const sf::Vector2f& c_maxVelocity,
                           const float c_jitterStep) noexcept
    : abstract::brain(c_velocity),
      m_maxVelocity{c_maxVelocity},
      m_jitterStep{c_jitterStep} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

wander_brain::~wander_brain() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

wander_brain::wander_brain(wander_brain&& otherRLink) noexcept
    : abstract::brain(std::move(otherRLink)),
      m_maxVelocity{otherRLink.m_maxVelocity},
      m_jitterStep{otherRLink.m_jitterStep} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

wander_brain& wander_brain::operator=(wander_brain&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    abstract::brain::operator=(std::move(otherRLink));
    this->m_maxVelocity = otherRLink.m_maxVelocity;
    this->m_jitterStep = otherRLink.m_jitterStep;
  }

  return *this;
}

void wander_brain::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const float c_newX{this->m_velocity.x +
                     ((std::rand() % 3 - 1) * this->m_jitterStep * c_dt)};
  const float c_newY{this->m_velocity.y +
                     ((std::rand() % 3 - 1) * this->m_jitterStep * c_dt)};

  if (std::abs(c_newX) < this->m_maxVelocity.x) {
    this->m_velocity.x = c_newX;
  }

  if (std::abs(c_newY) < this->m_maxVelocity.y) {
    this->m_velocity.y = c_newY;
  }
}

}  // namespace library
}  // namespace pack
