#include "pack_library_mover.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

mover::mover(const std::shared_ptr<sf::Shape>& shapeSPtr) noexcept
    : m_shapeWPtr{shapeSPtr} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

mover::~mover() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

mover::mover(mover&& otherRLink) noexcept
    : m_shapeWPtr{std::move(otherRLink.m_shapeWPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

mover& mover::operator=(mover&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shapeWPtr = std::move(otherRLink.m_shapeWPtr);
  }

  return *this;
}

void mover::tick(const sf::Vector2f& c_velocity, const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (auto shapePtr = this->m_shapeWPtr.lock()) {
    sf::Vector2f position = shapePtr->getPosition();

    position.x += c_velocity.x * c_dt;
    position.y += c_velocity.y * c_dt;

    shapePtr->setPosition(position);
  }
}

}  // namespace library
}  // namespace pack
