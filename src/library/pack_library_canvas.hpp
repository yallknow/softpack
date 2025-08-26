#pragma once

#ifndef PACK_LIBRARY_CANVAS
#define PACK_LIBRARY_CANVAS

#include <SFML/Graphics.hpp>

#include <vector>

namespace pack {
namespace library {

class canvas final {
 public:
  explicit canvas(const std::uint32_t c_windowWidth,
                  const std::uint32_t c_windowHeight) noexcept;
  /* virtual */ ~canvas() noexcept;

 public:
  explicit canvas(const canvas& c_other) noexcept = delete;
  explicit canvas(canvas&& otherRLink) noexcept = delete;

 public:
  canvas& operator=(const canvas& c_other) noexcept = delete;
  canvas& operator=(canvas&& otherRLink) noexcept = delete;

 public:
  const sf::RenderTexture& get_texture() const;

  void tick(const float c_dt) noexcept;
  void draw() noexcept;

 public:
  sf::RenderTexture m_texture;
  std::vector<sf::RectangleShape> m_shapes;
  std::vector<sf::Vector2f> m_velocities;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_CLIENT_CANVAS
