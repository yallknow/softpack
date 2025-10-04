#include "pack_library_actor.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

actor::actor(std::weak_ptr<sf::RenderTarget> renderWPtr,
             std::unique_ptr<sf::Shape>&& shapeUPtrRLink,
             const b2BodyId c_bodyId,
             std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept
    : m_shape{renderWPtr, std::move(shapeUPtrRLink)},
      m_body{c_bodyId},
      m_brainUPtr{std::move(brainUPtrRLink)} {
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

  if (this->m_brainUPtr) {
    this->m_brainUPtr->tick(c_dt);

    this->m_body.set_veloticy(this->m_brainUPtr->get_velocity());
  }

  this->m_shape.set_position(this->m_body.get_position());
  this->m_shape.set_rotation(this->m_body.get_rotation());
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shape.draw();
}

}  // namespace library
}  // namespace pack
