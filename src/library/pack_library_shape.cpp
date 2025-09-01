#include "pack_library_shape.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

shape::shape(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
             const std::shared_ptr<sf::Shape>& c_shapeSPtr) noexcept
    : m_renderWPtr{c_renderSPtr}, m_shapeSPtr{c_shapeSPtr} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

shape::~shape() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

shape::shape(shape&& otherRLink) noexcept
    : m_renderWPtr{std::move(otherRLink.m_renderWPtr)},
      m_shapeSPtr{std::move(otherRLink.m_shapeSPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

shape& shape::operator=(shape&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_renderWPtr = std::move(otherRLink.m_renderWPtr);
    this->m_shapeSPtr = std::move(otherRLink.m_shapeSPtr);
  }

  return *this;
}

const sf::Shape& shape::get_shape() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return *this->m_shapeSPtr;
}

void shape::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (auto renderSPtr = this->m_renderWPtr.lock()) {
    renderSPtr->draw(*this->m_shapeSPtr);
  }
}

}  // namespace library
}  // namespace pack
