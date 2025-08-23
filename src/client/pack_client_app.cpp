#include "pack_client_app.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <cstdint>
#include <string>

#include "../library/pack_library_preprocessor.hpp"

namespace pack {
namespace client {

namespace {

const std::string gsc_windowTitle{"softpack"};
const std::string gsc_viewportTitle{"viewport"};

constexpr std::uint32_t gsc_windowWidth{1280u};
constexpr std::uint32_t gsc_windowHeight{720u};
constexpr std::uint32_t gsc_windowFramerateLimit{60u};

const sf::VideoMode gsc_videoMode{gsc_windowWidth, gsc_windowHeight};

}  // namespace

app::app() noexcept
    : m_window{gsc_videoMode, gsc_windowTitle},
      m_canvas{gsc_windowWidth, gsc_windowHeight} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_window.setFramerateLimit(gsc_windowFramerateLimit);
}

app::~app() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

bool app::start() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  ImGui::SFML::Init(this->m_window);

  ImGuiIO& ioLink = ImGui::GetIO();
  ioLink.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  this->main_loop();

  ImGui::SFML::Shutdown();

  return true;
}

void app::main_loop() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  sf::Clock deltaClock{};

  while (this->m_window.isOpen()) {
    this->poll_events();

    if (!this->m_window.isOpen()) {
      break;
    }

    sf::Time dt = deltaClock.restart();
    ImGui::SFML::Update(this->m_window, dt);

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    this->m_canvas.tick(dt.asSeconds());
    this->m_canvas.draw();

    if (ImGui::Begin(gsc_viewportTitle.c_str())) {
      ImGui::Image(this->m_canvas.get_texture());
    }
    ImGui::End();

    ImGui::SFML::Render(this->m_window);

    this->m_window.display();
  }
}

void app::poll_events() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  sf::Event event{};

  while (this->m_window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(this->m_window, event);

    switch (event.type) {
      case sf::Event::Closed: {
        this->m_window.close();
        break;
      }
    }
  }
}

}  // namespace client
}  // namespace pack
