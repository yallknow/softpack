#include "pack_library_wander_brain.hpp"

#include <cmath>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

namespace {

constexpr float gsc_jitterStep{10.0f};

const sf::Vector2f gsc_maxVelocity{100.0f, 100.0f};
const sf::Vector2f gsc_defaultVelocity{0.0f, 0.0f};

inline float jitter() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  // (std::rand() % 3 - 1) -> [-1, 0, 1]
  return (std::rand() % 3 - 1) * gsc_jitterStep;
}

}  // namespace

wander_brain::wander_brain() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

wander_brain::~wander_brain() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

wander_brain::wander_brain(wander_brain&& otherRLink) noexcept
    : abstract::brain(std::move(otherRLink)) {}

wander_brain& wander_brain::operator=(wander_brain&& otherRLink) noexcept {
  if (this != &otherRLink) {
    abstract::brain::operator=(std::move(otherRLink));
  }

  return *this;
}

void wander_brain::tick() noexcept {
  const float c_newX = this->m_velocity.x + jitter();
  const float c_newY = this->m_velocity.y + jitter();

  if (std::abs(c_newX) < gsc_maxVelocity.x) {
    this->m_velocity.x = c_newX;
  } else {
    this->m_velocity.x = gsc_defaultVelocity.x;
  }

  if (std::abs(c_newY) < gsc_maxVelocity.y) {
    this->m_velocity.y = c_newY;
  } else {
    this->m_velocity.y = gsc_defaultVelocity.y;
  }
}

}  // namespace library
}  // namespace pack
