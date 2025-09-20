#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_BRAIN
#define PACK_LIBRARY_ABSTRACT_BRAIN

#include <SFML/System/Vector2.hpp>
#include <boost/core/noncopyable.hpp>

namespace pack {
namespace library {
namespace abstract {

class brain /*final*/ : private boost::noncopyable {
 public:
  explicit brain(const sf::Vector2f& c_velocity) noexcept;
  virtual ~brain() noexcept;

 public:
  explicit brain(brain&& otherRLink) noexcept;
  brain& operator=(brain&& otherRLink) noexcept;

 public:
  sf::Vector2f get_velocity() const noexcept;

 public:
  virtual void tick(const float c_dt) noexcept = 0;

 protected:
  sf::Vector2f m_velocity;
};

}  // namespace abstract
}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ABSTRACT_BRAIN
