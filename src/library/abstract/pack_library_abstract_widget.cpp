#include "pack_library_abstract_widget.hpp"

#include <imgui.h>

#include "../pack_library_preprocessor.hpp"

namespace pack {
namespace library {
namespace abstract {

widget::widget(const std::uint32_t c_width, const std::uint32_t c_height,
               const std::string_view c_title) noexcept
    : mc_width{c_width},
      mc_height{c_height},
      mc_title{c_title},
      m_isHovered{false},
      m_imageMin{0.0f, 0.0f},
      m_imageMax{0.0f, 0.0f} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

widget::~widget() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void widget::fill_image_stats() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_isHovered =
      ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);

  const ImVec2 c_imageMin{ImGui::GetItemRectMin()};
  this->m_imageMin = sf::Vector2f{c_imageMin.x, c_imageMin.y};

  const ImVec2 c_imageMax{ImGui::GetItemRectMax()};
  this->m_imageMax = sf::Vector2f{c_imageMax.x, c_imageMax.y};
}

}  // namespace abstract
}  // namespace library
}  // namespace pack
