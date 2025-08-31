#include "pack_library_mover.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

mover::mover(const std::shared_ptr<sf::Shape>& shapeSPtr,
             const sf::Vector2f& c_velocity) noexcept
    : m_shapeWPtr{shapeSPtr},
      m_velocity{c_velocity},
      m_position{shapeSPtr->getPosition()} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

mover::~mover() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

mover::mover(mover&& otherRLink) noexcept
    : m_shapeWPtr{std::move(otherRLink.m_shapeWPtr)},
      m_position{otherRLink.m_position},
      m_velocity{otherRLink.m_velocity} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

mover& mover::operator=(mover&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shapeWPtr = std::move(otherRLink.m_shapeWPtr);
    this->m_position = otherRLink.m_position;
    this->m_velocity = otherRLink.m_velocity;
  }

  return *this;
}

void mover::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_position.x += this->m_velocity.x * c_dt;
  this->m_position.y += this->m_velocity.y * c_dt;

  if (auto shapePtr = this->m_shapeWPtr.lock(); shapePtr) {
    shapePtr->setPosition(this->m_position);
  }
}

}  // namespace library
}  // namespace pack
