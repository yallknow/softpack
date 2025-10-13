#include "pack_library_minimap.hpp"

#include <imgui.h>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

minimap::minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                 const std::string_view c_title,
                 const std::uint32_t c_textureId,
                 const sf::Vector2u& c_textureSize) noexcept
    : abstract::widget{c_width, c_height, c_title, c_textureSize.x,
                       c_textureSize.y},
      mc_textureId{c_textureId},
      mc_textureSize{c_textureSize} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

minimap::~minimap() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void minimap::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const ImVec2 c_size{static_cast<float>(this->mc_width),
                      static_cast<float>(this->mc_height)};

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    ImGui::BeginChild(
        this->mc_title.data(), c_size, false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::Image(this->mc_textureId, c_size, ImVec2{0.0f, 1.0f},
                 ImVec2{1.0f, 0.0f});

    this->fill_image_stats();

    ImGui::EndChild();
  }
  ImGui::End();
}

void minimap::process_event(const sf::Event& c_event) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (!this->m_isHovered) {
    return;
  }
}

}  // namespace library
}  // namespace pack
