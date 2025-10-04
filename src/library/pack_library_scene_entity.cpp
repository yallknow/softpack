#include "pack_library_scene_entity.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

scene_entity::scene_entity(
    std::unique_ptr<sf::Shape>&& shapeUPtrRLink, const b2BodyId c_bodyId,
    std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept
    : m_shapeUPtr{std::move(shapeUPtrRLink)},
      m_id{},
      m_brainUPtr{std::move(brainUPtrRLink)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

scene_entity::~scene_entity() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

scene_entity::scene_entity(scene_entity&& otherRLink) noexcept
    : m_shapeUPtr{std::move(otherRLink.m_shapeUPtr)},
      m_id{otherRLink.m_id},
      m_brainUPtr{std::move(otherRLink.m_brainUPtr)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

scene_entity& scene_entity::operator=(scene_entity&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_shapeUPtr = std::move(otherRLink.m_shapeUPtr);
    this->m_id = otherRLink.m_id;
    this->m_brainUPtr = std::move(otherRLink.m_brainUPtr);
  }

  return *this;
}

}  // namespace library
}  // namespace pack
