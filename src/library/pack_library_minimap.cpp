#include "pack_library_minimap.hpp"

#include <imgui.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

minimap::minimap(const std::uint32_t c_width, const std::uint32_t c_height,
                 const std::string_view c_title, const scene& c_scene,
                 const std::uint32_t c_textureWidth,
                 const std::uint32_t c_textureHeight) noexcept
    : abstract::texture_widget{c_width, c_height,       c_title,
                               c_scene, c_textureWidth, c_textureHeight} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

minimap::~minimap() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void minimap::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->mc_scene.draw(this->m_texture);

  sf::RectangleShape cameraView;
  cameraView.setFillColor(sf::Color::Transparent);
  cameraView.setOutlineColor(sf::Color::Red);
  cameraView.setOutlineThickness(this->m_texture.getSize().x / -100.0f);
  cameraView.setSize(this->m_view.getSize());
  cameraView.setPosition(this->m_view.getCenter() -
                         this->m_view.getSize() * 0.5f);

  this->m_texture.draw(cameraView);

  this->m_texture.display();

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

    this->fill_image_fields();

    ImGui::EndChild();
  }
  ImGui::End();
}

bool minimap::process_event(const sf::Event& c_event) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (!this->m_isHovered) {
    return false;
  }

  switch (c_event.type) {
    case sf::Event::MouseButtonPressed: {
      if (c_event.mouseButton.button == sf::Mouse::Left) {
        const ImVec2 c_mousePosition = ImGui::GetIO().MousePos;

        const float c_relativeX{(c_mousePosition.x - this->m_imageMin.x) /
                                (this->m_imageMax.x - this->m_imageMin.x)};
        const float c_relativeY{(c_mousePosition.y - this->m_imageMin.y) /
                                (this->m_imageMax.y - this->m_imageMin.y)};

        const sf::Vector2f c_viewHalf{this->m_view.getSize() * 0.5f};
        const sf::Vector2f c_textureSize{
            static_cast<sf::Vector2f>(this->m_texture.getSize())};

        sf::Vector2f worldPosition{c_relativeX * c_textureSize.x,
                                   c_relativeY * c_textureSize.y};
        worldPosition.x =
            std::clamp(c_relativeX * c_textureSize.x, c_viewHalf.x,
                       c_textureSize.x - c_viewHalf.x);
        worldPosition.y =
            std::clamp(c_relativeY * c_textureSize.y, c_viewHalf.y,
                       c_textureSize.y - c_viewHalf.y);

        this->m_view.setCenter(worldPosition);

        return true;
      }
      break;
    }
  }

  return false;
}

}  // namespace library
}  // namespace pack
