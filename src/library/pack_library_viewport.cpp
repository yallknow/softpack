#include "pack_library_viewport.hpp"

#include <imgui.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <type_traits>
#include <utility>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

viewport::viewport(const std::uint32_t c_width, const std::uint32_t c_height,
                   const std::string_view c_title, const float c_minZoom,
                   const float c_maxZoom, const float c_zoomStep,
                   const std::uint32_t c_canvasWidth,
                   const std::uint32_t c_canvasHeight) noexcept
    : abstract::widget{c_width, c_height, c_title},
      mc_minZoom{c_minZoom},
      mc_maxZoom{c_maxZoom},
      mc_zoomStep{c_zoomStep},
      m_zoom{c_maxZoom},
      m_canvas{c_canvasWidth, c_canvasHeight} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

viewport::~viewport() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

const sf::RenderTexture& viewport::get_texture() const {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_canvas.get_texture();
}

float viewport::get_zoom() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_zoom;
}

void viewport::add(std::unique_ptr<sf::Shape>&& shapeUPtrRLink,
                   const b2BodyId c_bodyId,
                   std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_canvas.add(std::move(shapeUPtrRLink), c_bodyId,
                     std::move(brainUPtrRLink));
}

void viewport::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_canvas.tick(c_dt);
}

void viewport::process_event(const sf::Event& c_event) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  switch (c_event.type) {
    case sf::Event::MouseWheelScrolled: {
      if (c_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
          if (c_event.mouseWheelScroll.delta > 0)
            this->m_zoom =
                std::min(this->m_zoom * this->mc_zoomStep, this->mc_minZoom);
          else {
            this->m_zoom =
                std::max(this->m_zoom / this->mc_zoomStep, this->mc_maxZoom);
          }
        }
      }
      break;
    }
  }
}

void viewport::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_canvas.draw();

  const ImTextureID c_textureId{static_cast<ImTextureID>(
      this->m_canvas.get_texture().getTexture().getNativeHandle())};

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    ImGui::BeginChild(
        this->mc_title.data(),
        ImVec2{static_cast<float>(this->mc_width),
               static_cast<float>(this->mc_height)},
        false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    const ImVec2 c_full = ImGui::GetContentRegionAvail();
    const ImVec2 c_zoomed{c_full.x * this->m_zoom, c_full.y * this->m_zoom};

    ImGui::Image(c_textureId, c_zoomed, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::EndChild();
  }
  ImGui::End();
}

}  // namespace library
}  // namespace pack
