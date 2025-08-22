#include "pack_client_canvas.hpp"

#include "../library/pack_library_preprocessor.hpp"

namespace pack {
namespace client {

canvas::canvas() noexcept : m_texture{}, m_shape{} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shape.setRadius(50.0f);
  this->m_shape.setFillColor(sf::Color{150, 50, 250});
  this->m_shape.setOutlineThickness(10.0f);
  this->m_shape.setOutlineColor(sf::Color{250, 150, 100});
}

canvas::~canvas() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

sf::RenderTexture& canvas::get_texture() {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_texture;
}

void canvas::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_shape.move(100.0f * c_dt, 0.0f);
}

void canvas::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_texture.clear(sf::Color::Black);
  this->m_texture.draw(this->m_shape);
}

}  // namespace client
}  // namespace pack
