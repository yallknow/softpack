#include "pack_library_canvas.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

canvas::canvas(const std::uint32_t c_width,
               const std::uint32_t c_height) noexcept
    : m_textureSPtr{std::make_shared<sf::RenderTexture>()} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureSPtr->create(c_width, c_height);
}

canvas::~canvas() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void canvas::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  for (auto& actorLink : this->m_actors) {
    actorLink.tick(c_dt);
  }
}

void canvas::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureSPtr->clear(sf::Color::Black);

  for (const auto& c_actor : this->m_actors) {
    c_actor.draw();
  }
}

const sf::RenderTexture& canvas::get_texture() const {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return *this->m_textureSPtr;
}

}  // namespace library
}  // namespace pack
