#include "pack_library_shape.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

shape::shape(std::weak_ptr<sf::RenderTarget> renderWPtr,
             std::unique_ptr<sf::Shape>&& shapeUPtrRLink) noexcept
    : m_renderWPtr{renderWPtr}, m_shapeUPtr{std::move(shapeUPtrRLink)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

shape::~shape() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

shape::shape(shape&& otherRLink) noexcept
    : m_renderWPtr{otherRLink.m_renderWPtr},
      m_shapeUPtr{std::move(otherRLink.m_shapeUPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

shape& shape::operator=(shape&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_renderWPtr = otherRLink.m_renderWPtr;
    this->m_shapeUPtr = std::move(otherRLink.m_shapeUPtr);
  }

  return *this;
}

void shape::set_position(const sf::Vector2f& c_position) const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shapeUPtr->setPosition(c_position);
}

void shape::set_rotation(const float c_rotation) const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shapeUPtr->setRotation(c_rotation);
}

void shape::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (auto renderSPtr{this->m_renderWPtr.lock()}) {
    renderSPtr->draw(*this->m_shapeUPtr);
  }
}

}  // namespace library
}  // namespace pack
