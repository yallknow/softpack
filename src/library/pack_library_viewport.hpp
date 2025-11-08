#pragma once

#ifndef PACK_LIBRARY_VIEWPORT
#define PACK_LIBRARY_VIEWPORT

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <string_view>

#include "abstract/pack_library_abstract_texture_widget.hpp"
#include "pack_library_scene.hpp"

namespace pack {
namespace library {

class viewport final : public abstract::texture_widget {
 public:
  explicit viewport(const std::uint32_t c_width, const std::uint32_t c_height,
                    const std::string_view c_title, const scene& c_scene,
                    const std::uint32_t c_textureWidth,
                    const std::uint32_t c_textureHeight,
                    const float c_maxZoom) noexcept;
  /* virtual */ ~viewport() noexcept;

 public:
  explicit viewport(viewport&& otherRLink) noexcept = delete;
  viewport& operator=(viewport&& otherRLink) noexcept = delete;

 public:  // abstract::widget
  void draw() noexcept override;
  bool process_event(const sf::Event& c_event) noexcept override;

 private:
  const float mc_maxZoom;

 private:
  bool m_dragging;
  sf::Vector2i m_lastPosition;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_VIEWPORT
