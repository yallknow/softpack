#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_ACTOR
#define PACK_LIBRARY_ABSTRACT_ACTOR

#include <SFML/Graphics.hpp>

#include <boost/core/noncopyable.hpp>

#include <memory>

namespace pack {
namespace library {
namespace abstract {

class actor : private boost::noncopyable {
 public:
  explicit actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
                 const std::shared_ptr<sf::Shape>& c_shapeSPtr) noexcept;
  virtual ~actor() noexcept;

 public:
  explicit actor(actor&& otherRLink) noexcept;
  actor& operator=(actor&& otherRLink) noexcept;

 public:
  void draw() const noexcept;
  void tick(const float c_dt) const noexcept;

 protected:
  virtual void inner_tick(const float c_dt) const noexcept = 0;

 private:
  std::weak_ptr<sf::RenderTarget> m_renderWPtr;

 protected:
  std::shared_ptr<sf::Shape> m_shapeSPtr;

 protected:
  static sf::Vector2f ms_minPosition;  // TODO: Add setter
  static sf::Vector2f ms_maxPosition;  // TODO: Add setter
};

}  // namespace abstract
}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ABSTRACT_ACTOR
