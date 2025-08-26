#include "pack_library_canvas.hpp"

#include <cstdint>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

canvas::canvas(const std::uint32_t c_windowWidth,
               const std::uint32_t c_windowHeight) noexcept
    : m_texture{} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_texture.create(c_windowWidth / 2, c_windowHeight);

  for (int i = 0; i < 2; ++i) {
    sf::RectangleShape shape{{50, 50}};
    shape.setPosition(100.0f + i * 200.0f, 100.0f + i * 200.0f);
    shape.setFillColor(sf::Color{150, sf::Uint8(50 + i * 10), 250});
    shape.setOutlineThickness(10.0f);
    shape.setOutlineColor(sf::Color{250, sf::Uint8(150 + i * 10), 100});

    this->m_shapes.emplace_back(shape);
    this->m_velocities.emplace_back(200.0f + i * 50.0f, 150.0f - i * 50.0f);
  }
}

canvas::~canvas() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

const sf::RenderTexture& canvas::get_texture() const {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_texture;
}

void canvas::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  for (int i = 0; i < 2; ++i) {
    auto& rect = this->m_shapes[i];
    auto& velocity = this->m_velocities[i];
    auto& window = this->m_texture;

    rect.move(velocity * c_dt * 2.0f);

    sf::Vector2f pos = rect.getPosition();
    sf::Vector2f size = rect.getSize();
    float winW = static_cast<float>(window.getSize().x);
    float winH = static_cast<float>(window.getSize().y);

    // Left edge
    if (pos.x < 0.f) {
      velocity.x = std::abs(velocity.x);  // go right
      rect.setPosition(0.f, pos.y);
    }
    // Right edge
    else if (pos.x + size.x > winW) {
      velocity.x = -std::abs(velocity.x);  // go left
      rect.setPosition(winW - size.x, pos.y);
    }

    // Top edge
    if (pos.y < 0.f) {
      velocity.y = std::abs(velocity.y);  // go down
      rect.setPosition(pos.x, 0.f);
    }
    // Bottom edge
    else if (pos.y + size.y > winH) {
      velocity.y = -std::abs(velocity.y);  // go up
      rect.setPosition(pos.x, winH - size.y);
    }
  }

  // Handle rectangle vs rectangle collision
  if (this->m_shapes[0].getGlobalBounds().intersects(
          this->m_shapes[1].getGlobalBounds())) {
    // Simple response: swap velocities (like an elastic bounce)
    std::swap(this->m_velocities[0], this->m_velocities[1]);
  }
}

void canvas::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_texture.clear(sf::Color::Black);

  for (sf::RectangleShape& shapeLink : this->m_shapes) {
    this->m_texture.draw(shapeLink);
  }
}

}  // namespace library
}  // namespace pack
