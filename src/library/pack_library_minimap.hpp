#pragma once

#ifndef PACK_LIBRARY_MINIMAP
#define PACK_LIBRARY_MINIMAP

#include <SFML/Graphics/RenderTexture.hpp>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <string>
#include <string_view>

namespace pack {
namespace library {

class minimap final : private boost::noncopyable {
 public:
  explicit minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                   const std::string_view c_title) noexcept;
  /* virtual */ ~minimap() noexcept;

 public:
  explicit minimap(minimap&& otherRLink) noexcept = delete;
  minimap& operator=(minimap&& otherRLink) noexcept = delete;

 public:
  void draw(const sf::RenderTexture& c_texture,
            const float c_zoom) const noexcept;

 private:
  const std::uint32_t mc_width;
  const std::uint32_t mc_height;

  const std::string mc_title;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MINIMAP
