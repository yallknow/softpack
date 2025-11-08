#pragma once

#ifndef PACK_LIBRARY_MINIMAP
#define PACK_LIBRARY_MINIMAP

#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <string_view>

#include "abstract/pack_library_abstract_texture_widget.hpp"
#include "pack_library_scene.hpp"

namespace pack {
namespace library {

class minimap final : public abstract::texture_widget {
 public:
  explicit minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                   const std::string_view c_title, const scene& c_scene,
                   const std::uint32_t c_textureWidth,
                   const std::uint32_t c_textureHeight) noexcept;
  /* virtual */ ~minimap() noexcept;

 public:
  explicit minimap(minimap&& otherRLink) noexcept = delete;
  minimap& operator=(minimap&& otherRLink) noexcept = delete;

 public:  // abstract::widget
  void draw() noexcept override;
  bool process_event(const sf::Event& c_event) noexcept override;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MINIMAP
