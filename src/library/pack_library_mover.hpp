#pragma once

#ifndef PACK_LIBRARY_MOVER
#define PACK_LIBRARY_MOVER

#include <SFML/Graphics.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

namespace pack {
namespace library {

class mover final : private boost::noncopyable {
 public:
  explicit mover(const std::shared_ptr<sf::Shape>& shapeSPtr) noexcept;
  /*virtual*/ ~mover() noexcept;

 public:
  explicit mover(mover&& otherRLink) noexcept;
  mover& operator=(mover&& otherRLink) noexcept;

 public:
  void tick(const sf::Vector2f& c_velocity, const float c_dt) noexcept;

 private:
  std::weak_ptr<sf::Shape> m_shapeWPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MOVER
