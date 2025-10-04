#include "pack_client_app.hpp"

#include <box2d/box2d.h>
#include <box2d/collision.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

#include "../library/pack_library_math.hpp"
#include "../library/pack_library_preprocessor.hpp"
#include "../library/pack_library_scene_entity.hpp"
#include "../library/pack_library_scene_loader.hpp"
#include "../library/pack_library_wander_brain.hpp"

namespace pack {
namespace client {

namespace {

constexpr std::string_view gsc_windowTitle{"softpack"};
constexpr std::string_view gsc_viewportTitle{"viewport"};
constexpr std::string_view gsc_minimapTitle{"minimap"};
constexpr std::string_view gsc_scenePath{"scene/demo.json"};

constexpr std::uint32_t gsc_windowFramerateLimit{60u};
constexpr std::uint32_t gsc_borderHeight{35u};
constexpr std::uint32_t gsc_windowWidth{1'280u};
constexpr std::uint32_t gsc_windowHeight{720u};
constexpr std::uint32_t gsc_minimapWidth{200u};
constexpr std::uint32_t gsc_minimapHeight{150u};
constexpr std::uint32_t gsc_viewportWidth{gsc_windowWidth - gsc_minimapWidth};
constexpr std::uint32_t gsc_viewportHeight{gsc_windowHeight - gsc_borderHeight};

constexpr std::int32_t gsc_iterationsCount{6};

constexpr ImVec2 gsc_minimapSize{gsc_minimapWidth, gsc_minimapHeight};
constexpr ImVec2 gsc_minmapLowerLeft{0, 1};
constexpr ImVec2 gsc_minmapUpperRight{1, 0};

const sf::VideoMode gsc_windowVideoMode{gsc_windowWidth, gsc_windowHeight};

constexpr b2Vec2 gsc_gravity{0.0f, 0.0f};

constexpr float gsc_defaultTimestep{1.0f / 600.f};

}  // namespace

app::app() noexcept
    : m_worldId{},
      m_window{gsc_windowVideoMode, gsc_windowTitle.data()},
      m_viewport{gsc_viewportWidth, gsc_viewportHeight} {
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

  this->fill_viewport();

  this->main_loop();

  ImGui::SFML::Shutdown();
  PACK_LIBRARY_LOG_INFO("ImGui::SFML shut down.");

  return true;
}

void app::fill_viewport() noexcept {
  std::vector<library::scene_entity> entities{};
  library::scene_loader::load(gsc_scenePath, entities);

  for (auto& entity : entities) {
    b2BodyId bodyId{b2CreateBody(this->m_worldId, &entity.m_bodyDef)};

    if (sf::CircleShape* const circlePtr =
            dynamic_cast<sf::CircleShape*>(entity.m_shapeUPtr.get())) {
      b2Circle circle{};
      circle.center = {0.0f, 0.0f};
      circle.radius = circlePtr->getRadius() / library::gsc_scale;

      b2CreateCircleShape(bodyId, &entity.m_shapeDef, &circle);
    }

    auto brainUPtr{
        std::make_unique<library::wander_brain>(sf::Vector2f{0.0f, 0.0f})};

    this->m_viewport.add(std::move(entity.m_shapeUPtr), bodyId,
                         std::move(brainUPtr));
  }
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

    if (ImGui::Begin(gsc_minimapTitle.data())) {
      const ImTextureID c_textureId{static_cast<ImTextureID>(
          this->m_viewport.get_texture().getTexture().getNativeHandle())};

      ImGui::Image(c_textureId, gsc_minimapSize, gsc_minmapLowerLeft,
                   gsc_minmapUpperRight);
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
