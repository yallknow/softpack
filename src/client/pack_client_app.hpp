#pragma once

#ifndef PACK_CLIENT_APP
#define PACK_CLIENT_APP

#include <box2d/id.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <boost/core/noncopyable.hpp>
#include <string_view>

#include "../library/pack_library_minimap.hpp"
#include "../library/pack_library_scene.hpp"
#include "../library/pack_library_scene_manager.hpp"
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
  void create_world() noexcept;
  void destroy_world() noexcept;

  void load_scene(const std::string_view c_path) noexcept;
  void main_loop() noexcept;
  void poll_events() noexcept;

 private:
  b2WorldId m_worldId;
  sf::RenderWindow m_window;

  library::scene m_scene;
  library::scene_manager m_sceneManager;

  library::viewport m_viewport;
  library::minimap m_minimap;
};

}  // namespace client
}  // namespace pack

#endif  // !PACK_CLIENT_APP
