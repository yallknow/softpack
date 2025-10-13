#pragma once

#ifndef PACK_LIBRARY_ABSTRACT_WIDGET
#define PACK_LIBRARY_ABSTRACT_WIDGET

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <string>
#include <string_view>

namespace pack {
namespace library {
namespace abstract {

class widget /* final */ : private boost::noncopyable {
 public:
  explicit widget(const std::uint32_t c_width, const std::uint32_t c_height,
                  const std::string_view c_title) noexcept;
  virtual ~widget() noexcept;

 public:
  explicit widget(widget&& otherRLink) noexcept = delete;
  widget& operator=(widget&& otherRLink) noexcept = delete;

 public:
  virtual void draw() noexcept = 0;
  virtual void process_event(const sf::Event& c_event) noexcept = 0;

 protected:
  void fill_image_stats() noexcept;

 protected:
  const std::uint32_t mc_width;
  const std::uint32_t mc_height;

  const std::string mc_title;

 protected:
  bool m_isHovered;
  sf::Vector2f m_imageMin;
  sf::Vector2f m_imageMax;
};

}  // namespace abstract
}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_ABSTRACT_WIDGET
