#pragma once

#ifndef PACK_LIBRARY_SCENE_ENTITY
#define PACK_LIBRARY_SCENE_ENTITY

#include <box2d/id.h>

#include <SFML/Graphics/Shape.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

#include "abstract/pack_library_abstract_brain.hpp"

namespace pack {
namespace library {

class scene_entity final : private boost::noncopyable {
 public:
  explicit scene_entity(
      std::unique_ptr<sf::Shape>&& shapeUPtrRLink, const b2BodyId c_bodyId,
      std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept;
  /* virtual */ ~scene_entity() noexcept;

 public:
  explicit scene_entity(scene_entity&& otherRLink) noexcept;
  scene_entity& operator=(scene_entity&& otherRLink) noexcept;

 public:
  std::unique_ptr<sf::Shape> m_shapeUPtr;
  b2BodyId m_id;
  std::unique_ptr<abstract::brain> m_brainUPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCENE_ENTITY
