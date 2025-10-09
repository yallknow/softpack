#include "pack_library_minimap.hpp"

#include <imgui.h>

#include <SFML/Graphics/Texture.hpp>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

minimap::minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                 const std::string_view c_title) noexcept
    : mc_width{c_width}, mc_height{c_height}, mc_title{c_title} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

minimap::~minimap() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void minimap::draw(const sf::RenderTexture& c_texture,
                   const float c_zoom) const noexcept {
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

    const ImTextureID c_textureId{
        static_cast<ImTextureID>(c_texture.getTexture().getNativeHandle())};

    ImGui::Image(c_textureId,
                 ImVec2{static_cast<float>(this->mc_width),
                        static_cast<float>(this->mc_height)},
                 ImVec2{0, 1}, ImVec2{1, 0});

    const ImVec2 c_viewMin{c_position.x, c_position.y};
    const ImVec2 c_viewMax{c_position.x + this->mc_width / c_zoom,
                           c_position.y + this->mc_height / c_zoom};

    ImGui::GetWindowDrawList()->AddRect(
        c_viewMin, c_viewMax, IM_COL32(255, 0, 0, 255), 0.0f, 0, 1.0f);

    ImGui::EndChild();
  }
  ImGui::End();
}

}  // namespace library
}  // namespace pack
