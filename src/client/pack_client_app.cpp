#include "pack_client_app.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <cstdint>
#include <string>

#include "../library/pack_library_preprocessor.hpp"

namespace pack {
namespace client {

namespace {

const std::string gsc_WindowTitle{"softpack"};
const std::string gsc_ViewportTitle{"viewport"};

constexpr std::uint32_t gsc_WindowWidth{1280u};
constexpr std::uint32_t gsc_WindowHeight{720u};
constexpr std::uint32_t gsc_WindowFramerateLimit{60u};

const sf::VideoMode gsc_VideoMode{gsc_WindowWidth, gsc_WindowHeight};

}  // namespace

app::app() noexcept : m_window{gsc_VideoMode, gsc_WindowTitle}, m_texture{} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_window.setFramerateLimit(gsc_WindowFramerateLimit);
  this->m_texture.create(gsc_WindowWidth, gsc_WindowHeight);
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

    ImGui::SFML::Update(this->m_window, deltaClock.restart());

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    this->handle_viewport();

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

void app::handle_viewport() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_texture.clear(sf::Color::Black);

  this->draw_viewport();

  if (ImGui::Begin(gsc_ViewportTitle.c_str())) {
    ImGui::Image(this->m_texture);
  }
  ImGui::End();
}

void app::draw_viewport() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  sf::CircleShape shape(50.0f);
  shape.setFillColor(sf::Color{150, 50, 250});
  shape.setOutlineThickness(10.0f);
  shape.setOutlineColor(sf::Color{250, 150, 100});

  this->m_texture.draw(shape);
}

}  // namespace client
}  // namespace pack
