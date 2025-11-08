#pragma once

#ifndef PACK_LIBRARY_SCENE
#define PACK_LIBRARY_SCENE

#include <SFML/Graphics/RenderTarget.hpp>
#include <boost/core/noncopyable.hpp>
#include <vector>

#include "pack_library_actor.hpp"

namespace pack {
namespace library {

class scene final : private boost::noncopyable {
 public:
  explicit scene() noexcept;
  /* virtual */ ~scene() noexcept;

 public:
  explicit scene(scene&& otherRLink) noexcept;
  scene& operator=(scene&& otherRLink) noexcept;

 public:
  void add(actor&& actorRLink) noexcept;
  void clear() noexcept;

  void tick(const float c_dt) noexcept;
  void draw(sf::RenderTarget& targetLink) const noexcept;

 private:
  std::vector<actor> m_actors;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCENE
