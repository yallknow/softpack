#pragma once

#ifndef PACK_CLIENT_APP
#define PACK_CLIENT_APP

#include <SFML/Graphics.hpp>

#include "pack_client_canvas.hpp"

namespace pack {
namespace client {

class app final {
 public:
  explicit app() noexcept;
  /* virtual */ ~app() noexcept;

 public:
  explicit app(const app& c_other) noexcept = delete;
  explicit app(app&& otherRLink) noexcept = delete;

 public:
  app& operator=(const app& c_other) noexcept = delete;
  app& operator=(app&& otherRLink) noexcept = delete;

 public:
  bool start() noexcept;

 private:
  void main_loop() noexcept;
  void poll_events() noexcept;

 private:
  sf::RenderWindow m_window;
  canvas m_canvas;
};

}  // namespace client
}  // namespace pack

#endif  // !PACK_CLIENT_APP
