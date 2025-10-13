#include "pack_library_viewport.hpp"

#include <imgui.h>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <utility>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

viewport::viewport(const std::uint32_t c_width, const std::uint32_t c_height,
                   const std::string_view c_title, const float c_maxZoom,
                   const std::uint32_t c_textureWidth,
                   const std::uint32_t c_textureHeight) noexcept
    : abstract::widget{c_width, c_height, c_title, c_textureWidth,
                       c_textureHeight},
      mc_maxZoom{c_maxZoom},
      m_dragging{false},
      m_lastPosition{0, 0},
      m_canvas{c_textureWidth, c_textureHeight} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_view.setCenter(c_textureWidth * 0.5f, c_textureHeight * 0.5f);
}

viewport::~viewport() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

canvas& viewport::get_canvas() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_canvas;
}

void viewport::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_canvas.get_texture().setView(this->m_view);
  this->m_canvas.draw();

  const ImVec2 c_size{static_cast<float>(this->mc_width),
                      static_cast<float>(this->mc_height)};

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    ImGui::BeginChild(
        this->mc_title.data(), c_size, false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::Image(this->m_canvas.get_texture().getTexture().getNativeHandle(),
                 ImGui::GetContentRegionAvail(), ImVec2{0.0f, 1.0f},
                 ImVec2{1.0f, 0.0f});

    this->fill_image_stats();

    ImGui::EndChild();
  }
  ImGui::End();
}

void viewport::process_event(const sf::Event& c_event) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (!this->m_isHovered) {
    this->m_dragging = false;
    return;
  }

  switch (c_event.type) {
    case sf::Event::MouseWheelScrolled: {
      if (c_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
        const ImVec2 c_mousePosition{ImGui::GetIO().MousePos};

        if (c_mousePosition.x < this->m_imageMin.x ||
            c_mousePosition.x > this->m_imageMax.x ||
            c_mousePosition.y < this->m_imageMin.y ||
            c_mousePosition.y > this->m_imageMax.y)
          break;

        const sf::Vector2f c_normalizedPosition{
            (c_mousePosition.x - this->m_imageMin.x) /
                (this->m_imageMax.x - this->m_imageMin.x),
            (c_mousePosition.y - this->m_imageMin.y) /
                (this->m_imageMax.y - this->m_imageMin.y)};

        sf::Vector2f viewBefore{
            c_normalizedPosition.x * this->m_view.getSize().x,
            c_normalizedPosition.y * this->m_view.getSize().y};
        sf::Vector2f topLeftBefore{this->m_view.getCenter() -
                                   this->m_view.getSize() * 0.5f};
        viewBefore += topLeftBefore;

        this->m_view.zoom(c_event.mouseWheelScroll.delta > 0 ? 0.9f : 1.1f);

        const sf::Vector2f c_textureSize{
            static_cast<sf::Vector2f>(this->m_canvas.get_texture().getSize())};

        sf::Vector2f viewSize{this->m_view.getSize()};
        viewSize.x = std::min(viewSize.x, c_textureSize.x);
        viewSize.y = std::min(viewSize.y, c_textureSize.y);
        viewSize.x = std::max(viewSize.x, c_textureSize.x / this->mc_maxZoom);
        viewSize.y = std::max(viewSize.y, c_textureSize.y / this->mc_maxZoom);

        this->m_view.setSize(viewSize);

        sf::Vector2f viewAfter{
            c_normalizedPosition.x * this->m_view.getSize().x,
            c_normalizedPosition.y * this->m_view.getSize().y};
        sf::Vector2f topLeftAfter{this->m_view.getCenter() -
                                  this->m_view.getSize() * 0.5f};
        viewAfter += topLeftAfter;

        this->m_view.move(viewBefore - viewAfter);

        const sf::Vector2f c_viewHalf{viewSize * 0.5f};

        sf::Vector2f viewCenter{this->m_view.getCenter()};
        viewCenter.x = std::clamp(viewCenter.x, c_viewHalf.x,
                                  c_textureSize.x - c_viewHalf.x);
        viewCenter.y = std::clamp(viewCenter.y, c_viewHalf.y,
                                  c_textureSize.y - c_viewHalf.y);

        this->m_view.setCenter(viewCenter);
      }
      break;
    }
    case sf::Event::MouseButtonPressed: {
      if (c_event.mouseButton.button == sf::Mouse::Left) {
        this->m_dragging = true;
        this->m_lastPosition = sf::Mouse::getPosition();
      }
      break;
    }
    case sf::Event::MouseButtonReleased: {
      if (c_event.mouseButton.button == sf::Mouse::Left) {
        this->m_dragging = false;
      }
      break;
    }
    case sf::Event::MouseMoved: {
      if (this->m_dragging) {
        const sf::Vector2i c_mousePosition = sf::Mouse::getPosition();

        this->m_view.move(
            static_cast<sf::Vector2f>(this->m_lastPosition - c_mousePosition));

        this->m_lastPosition = c_mousePosition;

        const sf::Vector2f c_viewHalf{this->m_view.getSize() * 0.5f};
        const sf::Vector2f c_textureSize{
            static_cast<sf::Vector2f>(this->m_canvas.get_texture().getSize())};

        sf::Vector2f viewCenter{this->m_view.getCenter()};
        viewCenter.x = std::clamp(viewCenter.x, c_viewHalf.x,
                                  c_textureSize.x - c_viewHalf.x);
        viewCenter.y = std::clamp(viewCenter.y, c_viewHalf.y,
                                  c_textureSize.y - c_viewHalf.y);

        this->m_view.setCenter(viewCenter);
      }
    } break;
  }
}

}  // namespace library
}  // namespace pack
