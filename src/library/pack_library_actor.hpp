#pragma once

#ifndef PACK_LIBRARY_ACTOR
#define PACK_LIBRARY_ACTOR

#include <SFML/Graphics.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

#include "pack_library_mover.hpp"
#include "pack_library_shape.hpp"

namespace pack {
namespace library {

class actor final : private boost::noncopyable {
 public:
  explicit actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
                 const std::shared_ptr<sf::Shape>& c_shapeSPtr,
                 const sf::Vector2f& c_velocity) noexcept;
  /*virtual*/ ~actor() noexcept;

 public:
  explicit actor(actor&& otherRLink) noexcept;
  actor& operator=(actor&& otherRLink) noexcept;

 public:
  void tick(const float c_dt) noexcept;
  void draw() const noexcept;

 private:
  shape m_shape;
  mover m_mover;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ACTOR
