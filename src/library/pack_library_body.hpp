#pragma once

#ifndef PACK_LIBRARY_BODY
#define PACK_LIBRARY_BODY

#include <box2d/id.h>

#include <SFML/System/Vector2.hpp>
#include <boost/core/noncopyable.hpp>

namespace pack {
namespace library {

class body final : private boost::noncopyable {
 public:
  explicit body(const b2BodyId c_id) noexcept;
  /*virtual*/ ~body() noexcept;

 public:
  explicit body(body&& otherRLink) noexcept;
  body& operator=(body&& otherRLink) noexcept;

 public:
  sf::Vector2f get_position() const noexcept;
  float get_rotation() const noexcept;

 public:
  void set_veloticy(const sf::Vector2f& c_velocity) noexcept;

 private:
  b2BodyId m_id;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_BODY
