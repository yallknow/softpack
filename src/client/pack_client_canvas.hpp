#pragma once

#ifndef PACK_CLIENT_CANVAS
#define PACK_CLIENT_CANVAS

#include <SFML/Graphics.hpp>

namespace pack {
namespace client {

class canvas final {
 public:
  explicit canvas() noexcept;
  /* virtual */ ~canvas() noexcept;

 public:
  explicit canvas(const canvas& c_other) noexcept = delete;
  explicit canvas(canvas&& otherRLink) noexcept = delete;

 public:
  canvas& operator=(const canvas& c_other) noexcept = delete;
  canvas& operator=(canvas&& otherRLink) noexcept = delete;

 public:
  sf::RenderTexture& get_texture();

  void tick(const float c_dt) noexcept;
  void draw() noexcept;

 public:
  sf::RenderTexture m_texture;
  sf::CircleShape m_shape;
};

}  // namespace client
}  // namespace pack

#endif  // !PACK_CLIENT_CANVAS
