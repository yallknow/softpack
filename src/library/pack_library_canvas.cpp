#include "pack_library_canvas.hpp"

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

canvas::canvas(const std::uint32_t c_width,
               const std::uint32_t c_height) noexcept
    : m_textureSPtr{std::make_shared<sf::RenderTexture>()} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureSPtr->create(c_width, c_height);

  auto rectangleShapeSPtr =
      std::make_shared<sf::RectangleShape>(sf::Vector2f{50.0f, 50.0f});
  rectangleShapeSPtr->setPosition(100.0f, 100.0f);
  rectangleShapeSPtr->setFillColor(sf::Color::White);

  auto circleShapeSPtr = std::make_shared<sf::CircleShape>(25.0f);
  circleShapeSPtr->setPosition(300.0f, 300.0f);
  circleShapeSPtr->setFillColor(sf::Color::White);

  const sf::Vector2f c_velocity1{100.0f, 10.0f};
  const sf::Vector2f c_velocity2{10.0f, -100.0f};

  this->m_actors.emplace_back(
      actor{this->m_textureSPtr, rectangleShapeSPtr, c_velocity1});
  this->m_actors.emplace_back(
      actor{this->m_textureSPtr, circleShapeSPtr, c_velocity2});
}

canvas::~canvas() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

const sf::RenderTexture& canvas::get_texture() const {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return *this->m_textureSPtr;
}

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

}  // namespace library
}  // namespace pack
