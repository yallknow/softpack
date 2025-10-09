#include "pack_library_minimap.hpp"

#include <imgui.h>

#include <SFML/Graphics/Texture.hpp>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

minimap::minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                 const std::string_view c_title) noexcept
    : abstract::widget{c_width, c_height, c_title},
      m_zoom{0.0f},
      m_textureId{0u} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

minimap::~minimap() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void minimap::set_texture_id(const std::uint32_t c_textureId) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureId = c_textureId;
}

void minimap::set_zoom(const float c_zoom) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_zoom = c_zoom;
}

void minimap::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    ImGui::BeginChild(
        this->mc_title.data(),
        ImVec2{static_cast<float>(this->mc_width),
               static_cast<float>(this->mc_height)},
        false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    const ImVec2 c_position = ImGui::GetCursorScreenPos();

    ImGui::Image(static_cast<ImTextureID>(this->m_textureId),
                 ImVec2{static_cast<float>(this->mc_width),
                        static_cast<float>(this->mc_height)},
                 ImVec2{0, 1}, ImVec2{1, 0});

    const ImVec2 c_viewMin{c_position.x, c_position.y};
    const ImVec2 c_viewMax{c_position.x + this->mc_width / this->m_zoom,
                           c_position.y + this->mc_height / this->m_zoom};

    ImGui::GetWindowDrawList()->AddRect(
        c_viewMin, c_viewMax, IM_COL32(255, 0, 0, 255), 0.0f, 0, 1.0f);

    ImGui::EndChild();
  }
  ImGui::End();
}

}  // namespace library
}  // namespace pack
