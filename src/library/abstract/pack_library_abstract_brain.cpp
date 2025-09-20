#include "pack_library_abstract_brain.hpp"

#include "../pack_library_preprocessor.hpp"

namespace pack {
namespace library {
namespace abstract {

brain::brain(const sf::Vector2f& c_velocity) noexcept : m_velocity{c_velocity} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

brain::~brain() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

brain::brain(brain&& otherRLink) noexcept : m_velocity{otherRLink.m_velocity} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

brain& brain::operator=(brain&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_velocity = otherRLink.m_velocity;
  }

  return *this;
}

sf::Vector2f brain::get_velocity() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_velocity;
}

}  // namespace abstract
}  // namespace library
}  // namespace pack
