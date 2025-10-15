#include "pack_library_minimap.hpp"

#include <imgui.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

minimap::minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                 const std::string_view c_title, const scene& c_scene,
                 const std::uint32_t c_textureWidth,
                 const std::uint32_t c_textureHeight) noexcept
    : abstract::widget{c_width, c_height,       c_title,
                       c_scene, c_textureWidth, c_textureHeight} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

minimap::~minimap() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void minimap::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_texture.setView(this->m_view);
  this->mc_scene.draw(this->m_texture);

  const ImVec2 c_size{static_cast<float>(this->mc_width),
                      static_cast<float>(this->mc_height)};

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    ImGui::BeginChild(
        this->mc_title.data(), c_size, false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::Image(this->m_texture.getTexture().getNativeHandle(), c_size,
                 ImVec2{0.0f, 1.0f}, ImVec2{1.0f, 0.0f});

    this->fill_widget_fields();

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
