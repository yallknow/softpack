#pragma once

#ifndef PACK_LIBRARY_MINIMAP
#define PACK_LIBRARY_MINIMAP

#include <cstdint>
#include <string_view>

#include "abstract/pack_library_abstract_widget.hpp"

namespace pack {
namespace library {

class minimap final : public abstract::widget {
 public:
  explicit minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                   const std::string_view c_title) noexcept;
  /* virtual */ ~minimap() noexcept;

 public:
  explicit minimap(minimap&& otherRLink) noexcept = delete;
  minimap& operator=(minimap&& otherRLink) noexcept = delete;

 public:
  void set_texture_id(const std::uint32_t c_textureId) noexcept;
  void set_zoom(const float c_zoom) noexcept;

 public:
  void draw() const noexcept override;

 private:
  float m_zoom;
  std::uint64_t m_textureId;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MINIMAP
