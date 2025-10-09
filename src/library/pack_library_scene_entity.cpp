#include "pack_library_scene_entity.hpp"

#include <type_traits>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

scene_entity::scene_entity(
    std::unique_ptr<sf::Shape>&& shapeUPtrRLink, const b2BodyDef c_bodyDef,
    const b2ShapeDef c_shapeDef,
    std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept
    : m_shapeUPtr{std::move(shapeUPtrRLink)},
      m_bodyDef{c_bodyDef},
      m_shapeDef{c_shapeDef},
      m_brainUPtr{std::move(brainUPtrRLink)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

scene_entity::~scene_entity() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

scene_entity::scene_entity(scene_entity&& otherRLink) noexcept
    : m_shapeUPtr{std::move(otherRLink.m_shapeUPtr)},
      m_bodyDef{otherRLink.m_bodyDef},
      m_shapeDef{otherRLink.m_shapeDef},
      m_brainUPtr{std::move(otherRLink.m_brainUPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

scene_entity& scene_entity::operator=(scene_entity&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shapeUPtr = std::move(otherRLink.m_shapeUPtr);
    this->m_bodyDef = otherRLink.m_bodyDef;
    this->m_shapeDef = otherRLink.m_shapeDef;
    this->m_brainUPtr = std::move(otherRLink.m_brainUPtr);
  }

  return *this;
}

}  // namespace library
}  // namespace pack
