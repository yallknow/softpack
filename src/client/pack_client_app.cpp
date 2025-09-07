#include "pack_client_app.hpp"

#include <box2d/box2d.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>
#include <string_view>

#include "../library/pack_library_preprocessor.hpp"

namespace pack {
namespace client {

namespace {

constexpr std::string_view gsc_windowTitle{"softpack"};
constexpr std::string_view gsc_viewportTitle{"viewport"};

constexpr std::uint32_t gsc_windowWidth{1280u};
constexpr std::uint32_t gsc_windowHeight{720u};
constexpr std::uint32_t gsc_windowFramerateLimit{60u};

const sf::VideoMode gsc_videoMode{gsc_windowWidth, gsc_windowHeight};

constexpr b2Vec2 gsc_gravity{0.0f, 0.0f};
constexpr float gsc_defaultTimestep{1.0f / 60.f};
constexpr std::int32_t gsc_iterationsCount{6};

}  // namespace

app::app() noexcept
    : m_worldId{},
      m_window{gsc_videoMode, gsc_windowTitle.data()},
      m_viewport{gsc_windowWidth, gsc_windowHeight} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  b2WorldDef worldDef{b2DefaultWorldDef()};
  worldDef.gravity = gsc_gravity;
  this->m_worldId = b2CreateWorld(&worldDef);

  this->m_window.setFramerateLimit(gsc_windowFramerateLimit);
}

app::~app() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  b2DestroyWorld(this->m_worldId);
}

bool app::start() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  ImGui::SFML::Init(this->m_window);
  PACK_LIBRARY_LOG_INFO("ImGui::SFML initialized.");

  ImGuiIO& ioLink{ImGui::GetIO()};
  ioLink.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // TODO: Add canvas filling.

  this->main_loop();

  ImGui::SFML::Shutdown();
  PACK_LIBRARY_LOG_INFO("ImGui::SFML shut down.");

  return true;
}

void app::main_loop() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  float timeAccumulator{0.0f};
  sf::Clock deltaClock{};

  while (this->m_window.isOpen()) {
    this->poll_events();

    if (!this->m_window.isOpen()) {
      PACK_LIBRARY_LOG_INFO("The window was closed by an event.");
      break;
    }

    const sf::Time c_dt{deltaClock.restart()};
    const float c_dt_seconds{c_dt.asSeconds()};
    timeAccumulator += c_dt_seconds;

    PACK_LIBRARY_LOG_INFO("Delta time =" + std::to_string(c_dt_seconds) + ".");

    ImGui::SFML::Update(this->m_window, c_dt);

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    this->m_viewport.tick(c_dt_seconds);

    while (timeAccumulator >= gsc_defaultTimestep) {
      b2World_Step(this->m_worldId, gsc_defaultTimestep, gsc_iterationsCount);
      timeAccumulator -= gsc_defaultTimestep;
    }

    this->m_viewport.draw();

    if (ImGui::Begin(gsc_viewportTitle.data())) {
      ImGui::Image(this->m_viewport.get_texture());
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
        PACK_LIBRARY_LOG_INFO("Event sf::Event::Closed received.");
        this->m_window.close();
        break;
      }
    }
  }
}

}  // namespace client
}  // namespace pack
