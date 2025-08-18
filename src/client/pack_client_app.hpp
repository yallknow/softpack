#pragma once

#ifndef _PACK_CLIENT_APP_
#define _PACK_CLIENT_APP_

#include <SFML/Graphics.hpp>

namespace pack {
namespace client {

class app {
 public:
  explicit app() noexcept;
  virtual ~app() noexcept;

 public:
  bool mf_start() noexcept;

 private:
  void mf_main_loop() noexcept;
  void mf_poll_events() noexcept;
  void mf_handle_viewport() noexcept;
  void mf_draw_viewport() noexcept;

 private:
  sf::RenderWindow mv_Window;
  sf::RenderTexture mv_Texture;
};

}  // namespace client
}  // namespace pack

#endif  // !_PACK_CLIENT_APP_
