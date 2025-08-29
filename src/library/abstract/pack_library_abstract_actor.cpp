#include "pack_library_abstract_actor.hpp"

#include "../pack_library_preprocessor.hpp"

namespace pack {
namespace library {
namespace abstract {

sf::Vector2f actor::ms_minPosition{0.0f, 0.0f};
sf::Vector2f actor::ms_maxPosition{
    1280.0f, 720.0f};  // TODO: Use default values 0.0f, 0.0f

actor::actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
             const std::shared_ptr<sf::Shape>& c_shapeSPtr) noexcept
    : m_renderWPtr{c_renderSPtr}, m_shapeSPtr{c_shapeSPtr} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor::~actor() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

actor::actor(actor&& otherRLink) noexcept
    : m_renderWPtr(std::move(otherRLink.m_renderWPtr)),
      m_shapeSPtr(std::move(otherRLink.m_shapeSPtr)) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  otherRLink.m_renderWPtr.reset();
  otherRLink.m_shapeSPtr.reset();
}

actor& actor::operator=(actor&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_renderWPtr = std::move(otherRLink.m_renderWPtr);
    this->m_shapeSPtr = std::move(otherRLink.m_shapeSPtr);

    otherRLink.m_renderWPtr.reset();
    otherRLink.m_shapeSPtr.reset();
  }

  return *this;
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (auto renderSPtr = this->m_renderWPtr.lock(); renderSPtr) {
    renderSPtr->draw(*this->m_shapeSPtr);
  }
}

void actor::tick(const float c_dt) const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const sf::Vector2f c_old{this->m_shapeSPtr->getPosition()};

  this->m_shapeSPtr->setPosition(
      c_old.x + 100.0f * c_dt,
      c_old.y + 100.0f * c_dt);  // TODO: Add velocity

  this->inner_tick(c_dt);
}

}  // namespace abstract
}  // namespace library
}  // namespace pack
