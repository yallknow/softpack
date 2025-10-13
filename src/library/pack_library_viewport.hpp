#pragma once

#ifndef PACK_LIBRARY_VIEWPORT
#define PACK_LIBRARY_VIEWPORT

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <string_view>

#include "abstract/pack_library_abstract_widget.hpp"
#include "pack_library_canvas.hpp"

namespace pack {
namespace library {

class viewport final : public abstract::widget {
 public:
  explicit viewport(const std::uint32_t c_width, const std::uint32_t c_height,
                    const std::string_view c_title, const float c_maxZoom,
                    const std::uint32_t c_canvasWidth,
                    const std::uint32_t c_canvasHeight) noexcept;
  /* virtual */ ~viewport() noexcept;

 public:
  explicit viewport(viewport&& otherRLink) noexcept = delete;
  viewport& operator=(viewport&& otherRLink) noexcept = delete;

 public:
  canvas& get_canvas() noexcept;

 public:
  void process_event(const sf::Event& c_event) noexcept;

 public:
  void draw() const noexcept override;

 private:
  const float mc_maxZoom;

 private:
  bool m_dragging;
  sf::Vector2i m_lastPosition;

  std::uint64_t m_textureId;
  sf::View m_view;
  canvas m_canvas;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_VIEWPORT
