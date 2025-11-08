#include "pack_library_scene.hpp"

#include <SFML/Graphics/Color.hpp>
#include <type_traits>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

scene::scene() noexcept : m_actors{} { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

scene::~scene() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

scene::scene(scene&& otherRLink) noexcept
    : m_actors{std::move(otherRLink.m_actors)} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

scene& scene::operator=(scene&& otherRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (this != &otherRLink) {
    this->m_actors = std::move(otherRLink.m_actors);
  }

  return *this;
}

void scene::add(actor&& actorRLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_actors.emplace_back(std::move(actorRLink));
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
