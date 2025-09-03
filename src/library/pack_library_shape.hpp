#pragma once

#ifndef PACK_LIBRARY_SHAPE
#define PACK_LIBRARY_SHAPE

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

namespace pack {
namespace library {

class shape final : private boost::noncopyable {
 public:
  explicit shape(std::weak_ptr<sf::RenderTarget> renderWPtr,
                 std::shared_ptr<sf::Shape>&& shapeSPtr) noexcept;
  /*virtual*/ ~shape() noexcept;

 public:
  explicit shape(shape&& otherRLink) noexcept;
  shape& operator=(shape&& otherRLink) noexcept;

 public:
  void draw() const noexcept;

 private:
  std::weak_ptr<sf::RenderTarget> m_renderWPtr;
  std::shared_ptr<sf::Shape> m_shapeSPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SHAPE
