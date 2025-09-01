#include "pack_library_canvas.hpp"

#include "pack_library_preprocessor.hpp"
#include "pack_library_wander_brain.hpp"

namespace pack {
namespace library {

canvas::canvas(const std::uint32_t c_width,
               const std::uint32_t c_height) noexcept
    : m_textureSPtr{std::make_shared<sf::RenderTexture>()} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_textureSPtr->create(c_width, c_height);

  auto rectangleShapeSPtr =
      std::make_shared<sf::RectangleShape>(sf::Vector2f{100.0f, 100.0f});
  rectangleShapeSPtr->setPosition(200.0f, 200.0f);
  rectangleShapeSPtr->setFillColor(sf::Color::White);

  auto rectangle2ShapeSPtr =
      std::make_shared<sf::RectangleShape>(sf::Vector2f{100.0f, 100.0f});
  rectangleShapeSPtr->setPosition(300.0f, 300.0f);
  rectangleShapeSPtr->setFillColor(sf::Color::Green);

  // auto rectangle3ShapeSPtr =
  //     std::make_shared<sf::RectangleShape>(sf::Vector2f{100.0f, 100.0f});
  // rectangleShapeSPtr->setPosition(400.0f, 400.0f);
  // rectangleShapeSPtr->setFillColor(sf::Color::Yellow);

  auto circleShapeSPtr = std::make_shared<sf::CircleShape>(50.0f);
  circleShapeSPtr->setPosition(500.0f, 500.0f);
  circleShapeSPtr->setFillColor(sf::Color::White);

  this->m_actors.emplace_back(actor{this->m_textureSPtr, rectangleShapeSPtr,
                                    std::make_unique<wander_brain>()});
  this->m_actors.emplace_back(actor{this->m_textureSPtr, rectangle2ShapeSPtr,
                                    std::make_unique<wander_brain>()});
  // this->m_actors.emplace_back(actor{this->m_textureSPtr, rectangle3ShapeSPtr,
  //                                   std::make_unique<wander_brain>()});
  this->m_actors.emplace_back(actor{this->m_textureSPtr, circleShapeSPtr,
                                    std::make_unique<wander_brain>()});
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

void canvas::handleCollisions() noexcept {
  for (size_t i = 0; i < m_actors.size(); ++i) {
    auto& a = m_actors[i];
    sf::FloatRect aBounds = a.get_shape().getGlobalBounds();

    for (size_t j = i + 1; j < m_actors.size(); ++j) {
      auto& b = m_actors[j];
      sf::FloatRect bBounds = b.get_shape().getGlobalBounds();

      if (aBounds.intersects(bBounds)) {
        // simple response: swap velocities
        auto vA = a.get_velocity();
        auto vB = b.get_velocity();

        a.set_velocity(vB);
        b.set_velocity(vA);

        // optional: move them apart slightly to prevent sticking
        // e.g., push along x or y by minimal overlap
      }
    }
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
