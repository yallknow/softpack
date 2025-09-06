#include "pack_library_body.hpp"

#include <box2d/box2d.h>

#include <cmath>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

namespace {

constexpr float gsc_scale{30.0f};
constexpr float gsc_rad{180.0f};
constexpr float gsc_pi{3.14159265f};

float rad2deg(const float c_rad) { return c_rad * gsc_rad / gsc_pi; }

}  // namespace

body::body(const b2BodyId c_id) noexcept : m_id{c_id} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

body::~body() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

body::body(body&& otherRLink) noexcept : m_id{otherRLink.m_id} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

body& body::operator=(body&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_id = otherRLink.m_id;
  }

  return *this;
}

void body::set_veloticy(const sf::Vector2f& c_velocity) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const b2Vec2 c_power{c_velocity.x, c_velocity.y};
  b2Body_ApplyForceToCenter(this->m_id, c_power, true);
}

sf::Vector2f body::get_position() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const b2Transform c_transform = b2Body_GetTransform(this->m_id);
  return sf::Vector2f{c_transform.p.x * gsc_scale, c_transform.p.y * gsc_scale};
}

float body::get_rotation() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const b2Transform c_transform = b2Body_GetTransform(this->m_id);
  const float c_angle = std::atan2(c_transform.q.s, c_transform.q.c);
  return rad2deg(c_angle);
}

}  // namespace library
}  // namespace pack
