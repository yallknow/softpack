#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_TEXTURE_WIDGET
#define PACK_LIBRARY_ABSTRACT_TEXTURE_WIDGET

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <string_view>

#include "../pack_library_scene.hpp"
#include "pack_library_abstract_widget.hpp"

namespace pack {
namespace library {
namespace abstract {

class texture_widget /* final */ : public widget {
 public:
  explicit texture_widget(const std::uint32_t c_width,
                          const std::uint32_t c_height,
                          const std::string_view c_title, const scene& c_scene,
                          const std::uint32_t c_textureWidth,
                          const std::uint32_t c_textureHeight) noexcept;
  virtual ~texture_widget() noexcept;

 public:
  explicit texture_widget(texture_widget&& otherRLink) noexcept = delete;
  texture_widget& operator=(texture_widget&& otherRLink) noexcept = delete;

 public:
  const sf::View& get_view() const noexcept;
  void set_view(const sf::View& c_view) noexcept;

 protected:
  void fill_image_fields() noexcept;

 protected:
  const scene& mc_scene;

 protected:
  sf::View m_view;
  sf::RenderTexture m_texture;

  bool m_isHovered;
  sf::Vector2f m_imageMin;
  sf::Vector2f m_imageMax;
};

}  // namespace abstract
}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ABSTRACT_TEXTURE_WIDGET
