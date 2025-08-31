#include "pack_library_actor.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

actor::actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
             const std::shared_ptr<sf::Shape>& c_shapeSPtr) noexcept
    : m_renderWPtr{c_renderSPtr}, m_shapeSPtr{c_shapeSPtr} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor::~actor() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

actor::actor(actor&& otherRLink) noexcept
    : m_renderWPtr{std::move(otherRLink.m_renderWPtr)},
      m_shapeSPtr{std::move(otherRLink.m_shapeSPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

actor& actor::operator=(actor&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_renderWPtr = std::move(otherRLink.m_renderWPtr);
    this->m_shapeSPtr = std::move(otherRLink.m_shapeSPtr);
  }

  return *this;
}

const sf::Shape& actor::get_shape() const {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return *this->m_shapeSPtr;
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (auto renderSPtr = this->m_renderWPtr.lock(); renderSPtr) {
    renderSPtr->draw(*this->m_shapeSPtr);
  }
}

}  // namespace library
}  // namespace pack
