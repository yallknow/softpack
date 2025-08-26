#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_ACTOR
#define PACK_LIBRARY_ABSTRACT_ACTOR

#include <SFML/Graphics.hpp>

#include <memory>

namespace pack {
namespace library {
namespace abstract {

class actor final {
 public:
  explicit actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
                 const std::shared_ptr<sf::Drawable>& c_shapeSPtr) noexcept;
  /* virtual */ ~actor() noexcept;

 public:
  explicit actor(const actor& c_other) noexcept = delete;
  explicit actor(actor&& otherRLink) noexcept = default;  // default

 public:
  actor& operator=(const actor& c_other) noexcept = delete;
  actor& operator=(actor&& otherRLink) noexcept = delete;

 public:
  void draw() const noexcept;

 private:
  std::weak_ptr<sf::RenderTarget> m_renderWPtr;
  std::shared_ptr<sf::Drawable> m_shapeSPtr;
};

}  // namespace abstract
}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ABSTRACT_ACTOR
