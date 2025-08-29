#include "pack_library_canvas.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

canvas::canvas(const std::uint32_t c_width,
               const std::uint32_t c_height) noexcept
    : m_textureSPtr{std::make_shared<sf::RenderTexture>()} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureSPtr->create(c_width, c_height);

  for (int i = 0; i < 10; ++i) {
    auto rshape =
        std::make_shared<sf::RectangleShape>(sf::Vector2f{50.0f, 50.0f});
    rshape->setPosition(100.0f + i * 20.0f, 100.0f + i * 1.0f);
    rshape->setFillColor(sf::Color{150, sf::Uint8(50 + i * 10), 250});
    rshape->setOutlineThickness(10.0f);
    rshape->setOutlineColor(sf::Color{250, sf::Uint8(150 + i * 10), 100});

    auto cshape = std::make_shared<sf::CircleShape>(20.0f);
    cshape->setPosition(400.0f + i * 20.0f, 400.0f + i * 10.0f);
    cshape->setFillColor(sf::Color{150, sf::Uint8(50 + i * 10), 250});
    cshape->setOutlineThickness(10.0f);
    cshape->setOutlineColor(sf::Color{250, sf::Uint8(150 + i * 10), 100});

    this->m_actors.emplace_back(eternal_actor{this->m_textureSPtr, rshape});
    this->m_actors.emplace_back(eternal_actor{this->m_textureSPtr, cshape});
  }
}

canvas::~canvas() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

const sf::RenderTexture& canvas::get_texture() const {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return *this->m_textureSPtr;
}

void canvas::tick(const float c_dt) const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  for (const auto& actor : this->m_actors) {
    actor.tick(c_dt);
  }
}

void canvas::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureSPtr->clear(sf::Color::Black);

  for (const auto& actor : this->m_actors) {
    actor.draw();
  }
}

}  // namespace library
}  // namespace pack
