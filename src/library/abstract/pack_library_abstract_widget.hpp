#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_WIDGET
#define PACK_LIBRARY_ABSTRACT_WIDGET

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <string>
#include <string_view>

#include "../pack_library_scene.hpp"

namespace pack {
namespace library {
namespace abstract {

class widget /* final */ : private boost::noncopyable {
 public:
  explicit widget(const std::uint32_t c_width, const std::uint32_t c_height,
                  const std::string_view c_title, const scene& c_scene,
                  const std::uint32_t c_textureWidth,
                  const std::uint32_t c_textureHeight) noexcept;
  virtual ~widget() noexcept;

 public:
  explicit widget(widget&& otherRLink) noexcept = delete;
  widget& operator=(widget&& otherRLink) noexcept = delete;

 public:
  virtual void draw() noexcept = 0;
  virtual bool process_event(const sf::Event& c_event) noexcept = 0;

 public:
  const sf::View& get_view() const noexcept;
  void set_view(const sf::View& c_view) noexcept;

 protected:
  void fill_widget_fields() noexcept;

 protected:
  const std::uint32_t mc_width;
  const std::uint32_t mc_height;

  const std::string mc_title;

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

#endif  // !PACK_LIBRARY_ABSTRACT_WIDGET
