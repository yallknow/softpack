#include "pack_library_actor.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

actor::actor(std::weak_ptr<sf::RenderTarget> renderWPtr,
             std::shared_ptr<sf::Shape>&& shapeSPtr, const b2BodyId c_bodyId,
             std::unique_ptr<abstract::brain>&& brainUPtr) noexcept
    : m_shape{renderWPtr, std::move(shapeSPtr)},
      m_body{c_bodyId},
      m_brainUPtr(std::move(brainUPtr)) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor::~actor() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

actor::actor(actor&& otherRLink) noexcept
    : m_shape{std::move(otherRLink.m_shape)},
      m_body{std::move(otherRLink.m_body)},
      m_brainUPtr{std::move(otherRLink.m_brainUPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor& actor::operator=(actor&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shape = std::move(otherRLink.m_shape);
    this->m_body = std::move(otherRLink.m_body);
    this->m_brainUPtr = std::move(otherRLink.m_brainUPtr);
  }

  return *this;
}

void actor::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_brainUPtr->tick();

  this->m_body.tick(this->m_brainUPtr->get_velocity());
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shape.draw();
}

}  // namespace library
}  // namespace pack
