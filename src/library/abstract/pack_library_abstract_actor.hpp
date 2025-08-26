#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_ACTOR
#define PACK_LIBRARY_ABSTRACT_ACTOR

#include <SFML/Graphics.hpp>

#include <concepts>
#include <type_traits>
#include <utility>
#include <variant>

namespace pack {
namespace library {
namespace abstract {

template <typename T>
concept render_concept = std::is_base_of_v<sf::RenderTarget, T>;

template <typename T>
concept shape_concept = std::is_base_of_v<sf::Drawable, T> &&
                        std::is_base_of_v<sf::Transformable, T>;

using shape_variant = std::variant<sf::RectangleShape>;

class actor {
 public:
  template <render_concept render, shape_concept shape, typename... Args>
  actor(render& renderLink, Args&&... args);
  virtual ~actor() noexcept;

 public:
  explicit actor(const actor& c_other) noexcept = delete;
  explicit actor(actor&& otherRLink) noexcept = delete;

 public:
  actor& operator=(const actor& c_other) noexcept = delete;
  actor& operator=(actor&& otherRLink) noexcept = delete;

 public:
  void draw() const noexcept;

 private:
  sf::RenderTarget& m_renderLink;
  shape_variant m_shape;
};

template <render_concept render, shape_concept shape, typename... Args>
inline actor::actor(render& renderLink, Args&&... args)
    : m_renderLink(renderLink),
      m_shape(std::in_place_type<shape>, std::forward<Args>(args)...) {
  // PACK_LIBRARY_LOG_FUNCTION_CALL();
}

}  // namespace abstract
}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ABSTRACT_ACTOR
