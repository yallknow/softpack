#pragma once

#ifndef PACK_LIBRARY_SCENE
#define PACK_LIBRARY_SCENE

#include <box2d/id.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>
#include <vector>

#include "abstract/pack_library_abstract_brain.hpp"
#include "pack_library_actor.hpp"

namespace pack {
namespace library {

class scene final : private boost::noncopyable {
 public:
  explicit scene() noexcept;
  /* virtual */ ~scene() noexcept;

 public:
  explicit scene(scene&& otherRLink) noexcept = delete;
  scene& operator=(scene&& otherRLink) noexcept = delete;

 public:
  void add(std::unique_ptr<sf::Shape>&& shapeUPtrRLink, const b2BodyId c_bodyId,
           std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept;

  void tick(const float c_dt) noexcept;
  void draw(sf::RenderTarget& targetLink) const noexcept;

 private:
  std::vector<actor> m_actors;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCENE
