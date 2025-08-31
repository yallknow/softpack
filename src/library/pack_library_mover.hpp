#pragma once

#ifndef PACK_LIBRARY_MOVER
#define PACK_LIBRARY_MOVER

#include <SFML/Graphics.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

namespace pack {
namespace library {

class mover final : private boost::noncopyable {
 protected:
  explicit mover(const std::shared_ptr<sf::Shape>& shapeSPtr,
                 const sf::Vector2f& c_position,
                 const sf::Vector2f& c_velocity) noexcept;

 public:
  /*virtual*/ ~mover() noexcept;

 public:
  explicit mover(mover&& otherRLink) noexcept;
  mover& operator=(mover&& otherRLink) noexcept;

 public:
  void tick(const float c_dt) noexcept;

 private:
  std::weak_ptr<sf::Shape> m_shapeWPtr;

  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MOVER
