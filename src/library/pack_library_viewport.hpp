#pragma once

#ifndef PACK_LIBRARY_VIEWPORT
#define PACK_LIBRARY_VIEWPORT

#include <box2d/id.h>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

#include "abstract/pack_library_abstract_brain.hpp"
#include "pack_library_canvas.hpp"

namespace pack {
namespace library {

class viewport final : private boost::noncopyable {
 public:
  explicit viewport(const std::uint32_t c_width, const std::uint32_t c_height,
                    const float c_minZoom, const float c_maxZoom,
                    const float c_zoomStep, const std::string_view c_title,
                    const std::uint32_t c_canvasWidth,
                    const std::uint32_t c_canvasHeight) noexcept;
  /* virtual */ ~viewport() noexcept;

 public:
  explicit viewport(viewport&& otherRLink) noexcept = delete;
  viewport& operator=(viewport&& otherRLink) noexcept = delete;

 public:
  const sf::RenderTexture& get_texture() const;

 public:
  float get_zoom() const noexcept;

 public:
  void add(std::unique_ptr<sf::Shape>&& shapeUPtrRLink, const b2BodyId c_bodyId,
           std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept;

  void tick(const float c_dt) noexcept;
  void draw() const noexcept;

  void process_event(const sf::Event& c_event) noexcept;

 private:
  const std::uint32_t mc_width;
  const std::uint32_t mc_height;

  const float mc_minZoom;
  const float mc_maxZoom;
  const float mc_zoomStep;

  const std::string mc_title;

 private:
  float m_zoom;
  library::canvas m_canvas;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_VIEWPORT
