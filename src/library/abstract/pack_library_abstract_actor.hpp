#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_ACTOR
#define PACK_LIBRARY_ABSTRACT_ACTOR

#include <SFML/Graphics.hpp>

#include <boost/core/noncopyable.hpp>

#include <memory>

namespace pack {
namespace library {
namespace abstract {

class actor final : private boost::noncopyable {
 public:
  explicit actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
                 const std::shared_ptr<sf::Drawable>& c_shapeSPtr) noexcept;
  /* virtual */ ~actor() noexcept;

 public:
  explicit actor(actor&& otherRLink) noexcept;

 public:
  actor& operator=(actor&& otherRLink) noexcept;

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
