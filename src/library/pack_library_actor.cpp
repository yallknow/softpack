#include "pack_library_actor.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

actor::actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
             const std::shared_ptr<sf::Shape>& c_shapeSPtr,
             std::unique_ptr<abstract::brain>&& brainUPtr) noexcept
    : m_shape{c_renderSPtr, c_shapeSPtr},
      m_mover{c_shapeSPtr},
      m_brainUPtr(std::move(brainUPtr)) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor::~actor() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

actor::actor(actor&& otherRLink) noexcept
    : m_shape{std::move(otherRLink.m_shape)},
      m_mover{std::move(otherRLink.m_mover)},
      m_brainUPtr{std::move(otherRLink.m_brainUPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor& actor::operator=(actor&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shape = std::move(otherRLink.m_shape);
    this->m_mover = std::move(otherRLink.m_mover);
    this->m_brainUPtr = std::move(otherRLink.m_brainUPtr);
  }

  return *this;
}

const sf::Shape& actor::get_shape() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_shape.get_shape();
}

sf::Vector2f actor::get_velocity() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_brainUPtr->get_velocity();
}

void actor::set_velocity(const sf::Vector2f& c_velocity) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_brainUPtr->set_velocity(c_velocity);
}

void actor::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_brainUPtr->tick();

  this->m_mover.tick(this->m_brainUPtr->get_velocity(), c_dt);
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shape.draw();
}

}  // namespace library
}  // namespace pack
