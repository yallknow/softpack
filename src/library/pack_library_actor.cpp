#include "pack_library_actor.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

actor::actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
             const std::shared_ptr<sf::Shape>& c_shapeSPtr,
             const sf::Vector2f& c_velocity) noexcept
    : m_shape{c_renderSPtr, c_shapeSPtr}, m_mover{c_shapeSPtr, c_velocity} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor::~actor() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

actor::actor(actor&& otherRLink) noexcept
    : m_shape{std::move(otherRLink.m_shape)},
      m_mover{std::move(otherRLink.m_mover)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor& actor::operator=(actor&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shape = std::move(otherRLink.m_shape);
    this->m_mover = std::move(otherRLink.m_mover);
  }

  return *this;
}

void actor::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_mover.tick(c_dt);
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shape.draw();
}

}  // namespace library
}  // namespace pack
