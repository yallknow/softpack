#pragma once

#ifndef PACK_LIBRARY_MINIMAP
#define PACK_LIBRARY_MINIMAP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <string_view>

#include "abstract/pack_library_abstract_widget.hpp"

namespace pack {
namespace library {

class minimap final : public abstract::widget {
 public:
  explicit minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                   const std::string_view c_title,
                   const std::uint32_t c_textureId,
                   const sf::Vector2u& c_textureSize) noexcept;
  /* virtual */ ~minimap() noexcept;

 public:
  explicit minimap(minimap&& otherRLink) noexcept = delete;
  minimap& operator=(minimap&& otherRLink) noexcept = delete;

 public:  // abstract::widget
  void draw() noexcept override;
  void process_event(const sf::Event& c_event) noexcept override;

 private:
  const std::uint64_t mc_textureId;
  const sf::Vector2u mc_textureSize;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MINIMAP
