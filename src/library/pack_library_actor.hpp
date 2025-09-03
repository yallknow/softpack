#pragma once

#ifndef PACK_LIBRARY_ACTOR
#define PACK_LIBRARY_ACTOR

#include <box2d/id.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

#include "abstract/pack_library_abstract_brain.hpp"
#include "pack_library_body.hpp"
#include "pack_library_shape.hpp"

namespace pack {
namespace library {

class actor final : private boost::noncopyable {
 public:
  explicit actor(std::weak_ptr<sf::RenderTarget> renderWPtr,
                 std::shared_ptr<sf::Shape>&& shapeSPtr,
                 const b2BodyId c_bodyId,
                 std::unique_ptr<abstract::brain>&& brainUPtr) noexcept;
  /*virtual*/ ~actor() noexcept;

 public:
  explicit actor(actor&& otherRLink) noexcept;
  actor& operator=(actor&& otherRLink) noexcept;

 public:
  void tick(const float c_dt) noexcept;
  void draw() const noexcept;

 private:
  shape m_shape;
  body m_body;
  std::unique_ptr<abstract::brain> m_brainUPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ACTOR
