#pragma once

#ifndef PACK_LIBRARY_CANVAS
#define PACK_LIBRARY_CANVAS

#include <SFML/Graphics.hpp>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <memory>
#include <vector>

#include "pack_library_actor.hpp"

namespace pack {
namespace library {

class canvas final : private boost::noncopyable {
 public:
  explicit canvas(const std::uint32_t c_width,
                  const std::uint32_t c_height) noexcept;
  /* virtual */ ~canvas() noexcept;

 public:
  explicit canvas(canvas&& otherRLink) noexcept = delete;
  canvas& operator=(canvas&& otherRLink) noexcept = delete;

 public:
  const sf::RenderTexture& get_texture() const;

 public:
  void tick(const float c_dt) noexcept;
  void handleCollisions() noexcept;
  void draw() const noexcept;

 private:
  std::shared_ptr<sf::RenderTexture> m_textureSPtr;
  std::vector<actor> m_actors;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_CANVAS
