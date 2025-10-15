#include "pack_library_scene.hpp"

#include <SFML/Graphics/Color.hpp>
#include <type_traits>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

scene::scene() noexcept : m_actors{} { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

scene::~scene() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void scene::add(std::unique_ptr<sf::Shape>&& shapeUPtrRLink,
                const b2BodyId c_bodyId,
                std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_actors.emplace_back(std::move(shapeUPtrRLink), c_bodyId,
                              std::move(brainUPtrRLink));
}

void scene::tick(const float c_dt) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  for (auto& actorLink : this->m_actors) {
    actorLink.tick(c_dt);
  }
}

void scene::draw(sf::RenderTarget& targetLink) const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  targetLink.clear(sf::Color::Black);

  for (const auto& c_actor : this->m_actors) {
    c_actor.draw(targetLink);
  }
}

}  // namespace library
}  // namespace pack
