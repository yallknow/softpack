#include "pack_library_body.hpp"

#include <box2d/box2d.h>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

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

void body::tick(const sf::Vector2f& c_velocity) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const b2Vec2 c_power{c_velocity.x, c_velocity.y};
  b2Body_ApplyForceToCenter(this->m_id, c_power, true);
}

}  // namespace library
}  // namespace pack
