#pragma once

#ifndef PACK_LIBRARY_ETERNAL_ACTOR
#define PACK_LIBRARY_ETERNAL_ACTOR

#include <SFML/Graphics.hpp>

#include <memory>

#include "abstract/pack_library_abstract_actor.hpp"

namespace pack {
namespace library {

class eternal_actor final : public abstract::actor {
 public:
  explicit eternal_actor(
      const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
      const std::shared_ptr<sf::Shape>& c_shapeSPtr) noexcept;
  /*virtual*/ ~eternal_actor() noexcept;

 public:
  explicit eternal_actor(eternal_actor&& otherRLink) noexcept;
  eternal_actor& operator=(eternal_actor&& otherRLink) noexcept;

 public:
  void inner_tick(const float c_dt) const noexcept override;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ETERNAL_ACTOR
