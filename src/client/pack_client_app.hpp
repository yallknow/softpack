#pragma once

#ifndef PACK_CLIENT_APP
#define PACK_CLIENT_APP

#include <box2d/id.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <boost/core/noncopyable.hpp>

#include "../library/pack_library_minimap.hpp"
#include "../library/pack_library_viewport.hpp"

namespace pack {
namespace client {

class app final : private boost::noncopyable {
 public:
  explicit app() noexcept;
  /* virtual */ ~app() noexcept;

 public:
  explicit app(app&& otherRLink) noexcept = delete;
  app& operator=(app&& otherRLink) noexcept = delete;

 public:
  bool start() noexcept;

 private:
  void load_scene() noexcept;
  void main_loop() noexcept;
  void poll_events() noexcept;

 private:
  b2WorldId m_worldId;
  sf::RenderWindow m_window;
  library::viewport m_viewport;
  library::minimap m_minimap;
};

}  // namespace client
}  // namespace pack

#endif  // !PACK_CLIENT_APP
