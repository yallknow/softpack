#pragma once

#ifndef PACK_LIBRARY_ACTOR
#define PACK_LIBRARY_ACTOR

#include <SFML/Graphics.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

namespace pack {
namespace library {

class actor final : private boost::noncopyable {
 public:
  explicit actor(const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
                 std::unique_ptr<sf::Shape>&& shapeUPtr) noexcept;
  /*virtual*/ ~actor() noexcept;

 public:
  explicit actor(actor&& otherRLink) noexcept;
  actor& operator=(actor&& otherRLink) noexcept;

 public:
  const sf::Shape& get_shape() const;

 public:
  void draw() const noexcept;

 private:
  std::weak_ptr<sf::RenderTarget> m_renderWPtr;
  std::unique_ptr<sf::Shape> m_shapeUPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ACTOR
