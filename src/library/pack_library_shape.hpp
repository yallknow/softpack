#pragma once

#ifndef PACK_LIBRARY_SHAPE
#define PACK_LIBRARY_SHAPE

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>

namespace pack {
namespace library {

class shape final : private boost::noncopyable {
 public:
  explicit shape(std::weak_ptr<sf::RenderTarget> renderWPtr,
                 std::unique_ptr<sf::Shape>&& shapeUPtrRLink) noexcept;
  /*virtual*/ ~shape() noexcept;

 public:
  explicit shape(shape&& otherRLink) noexcept;
  shape& operator=(shape&& otherRLink) noexcept;

 public:
  void set_position(const sf::Vector2f& c_position) const noexcept;
  void set_rotation(const float c_rotation) const noexcept;
  void draw() const noexcept;

 private:
  std::weak_ptr<sf::RenderTarget> m_renderWPtr;
  std::unique_ptr<sf::Shape> m_shapeUPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SHAPE
