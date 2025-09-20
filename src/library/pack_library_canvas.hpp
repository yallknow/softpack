#pragma once

#ifndef PACK_LIBRARY_CANVAS
#define PACK_LIBRARY_CANVAS

#include <SFML/Graphics/RenderTexture.hpp>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <memory>
#include <vector>

#include "pack_library_actor.hpp"

namespace pack {
namespace library {

class canvas final : private boost::noncopyable {
 public:
  explicit canvas(const std::uint32_t c_width,
                  const std::uint32_t c_height) noexcept;
  /* virtual */ ~canvas() noexcept;

 public:
  explicit canvas(canvas&& otherRLink) noexcept = delete;
  canvas& operator=(canvas&& otherRLink) noexcept = delete;

 public:
  void add(std::unique_ptr<sf::Shape>&& shapeUPtrRLink, const b2BodyId c_bodyId,
           std::unique_ptr<abstract::brain>&& brainUPtrRLink) noexcept;

  void tick(const float c_dt) noexcept;
  void draw() const noexcept;

  const sf::RenderTexture& get_texture() const;

 private:
  std::shared_ptr<sf::RenderTexture> m_textureSPtr;
  std::vector<actor> m_actors;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_CANVAS
