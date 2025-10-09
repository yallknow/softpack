#include "pack_client_app.hpp"

#include <box2d/box2d.h>
#include <box2d/collision.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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

namespace pack {
namespace client {

namespace {

constexpr std::uint32_t gsc_worldScale{5u};

// viewport
constexpr std::uint32_t gsc_viewportWidth{1'280u};
constexpr std::uint32_t gsc_viewportHeight{720u};

constexpr float gsc_minZoom{5.0f};
constexpr float gsc_maxZoom{1.0f};
constexpr float gsc_zoomStep{1.0f};

constexpr std::string_view gsc_viewportTitle{"viewport"};

constexpr std::uint32_t gsc_canvasWidth{gsc_viewportWidth * gsc_worldScale};
constexpr std::uint32_t gsc_canvasHeight{gsc_viewportHeight * gsc_worldScale};
// !viewport

constexpr std::string_view gsc_windowTitle{"softpack"};
constexpr std::string_view gsc_minimapTitle{"minimap"};
constexpr std::string_view gsc_scenePath{"scene/demo.json"};

constexpr std::uint32_t gsc_windowFramerateLimit{60u};

constexpr std::uint32_t gsc_borderSize{36u};
constexpr std::uint32_t gsc_minimapWidth{gsc_viewportWidth / gsc_worldScale};
constexpr std::uint32_t gsc_minimapHeight{gsc_viewportHeight / gsc_worldScale};
constexpr std::uint32_t gsc_windowWidth{gsc_viewportWidth + gsc_minimapWidth +
                                        gsc_borderSize};
constexpr std::uint32_t gsc_windowHeight{gsc_viewportHeight + gsc_borderSize};

constexpr std::int32_t gsc_iterationsCount{6};

constexpr ImVec2 gsc_viewportSize{gsc_viewportWidth, gsc_viewportHeight};
constexpr ImVec2 gsc_minimapSize{gsc_minimapWidth, gsc_minimapHeight};
constexpr ImVec2 gsc_lowerLeft{0, 1};
constexpr ImVec2 gsc_upperRight{1, 0};

constexpr b2Vec2 gsc_gravity{0.0f, 0.0f};

constexpr float gsc_defaultTimestep{1.0f / 600.f};

}  // namespace

app::app() noexcept
    : m_worldId{},
      m_window{sf::VideoMode{gsc_windowWidth, gsc_windowHeight},
               gsc_windowTitle.data()},
      m_viewport{gsc_viewportWidth, gsc_viewportHeight, gsc_minZoom,
                 gsc_maxZoom,       gsc_zoomStep,       gsc_viewportTitle,
                 gsc_canvasWidth,   gsc_canvasHeight} {
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
  PACK_LIBRARY_LOG_INFO("ImGui::SFML initialized");

  ImGuiIO& ioLink{ImGui::GetIO()};
  ioLink.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  this->load_scene();

  this->main_loop();

  ImGui::SFML::Shutdown();
  PACK_LIBRARY_LOG_INFO("ImGui::SFML shut down");

  return true;
}

void app::load_scene() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  std::vector<library::scene_entity> entities{};
  library::scene_loader::load(gsc_scenePath, entities);

  for (auto& entity : entities) {
    const b2BodyId c_bodyId{b2CreateBody(this->m_worldId, &entity.m_bodyDef)};

    if (sf::CircleShape* const circlePtr =
            dynamic_cast<sf::CircleShape*>(entity.m_shapeUPtr.get())) {
      const b2Circle c_circle{b2Vec2{0.0f, 0.0f},
                              circlePtr->getRadius() / library::gsc_scale};

      b2CreateCircleShape(c_bodyId, &entity.m_shapeDef, &c_circle);
    } else if (sf::RectangleShape* const rectanglePtr =
                   dynamic_cast<sf::RectangleShape*>(
                       entity.m_shapeUPtr.get())) {
      const b2Polygon c_polygon{
          b2MakeBox(rectanglePtr->getOrigin().x / library::gsc_scale,
                    rectanglePtr->getOrigin().y / library::gsc_scale)};

      b2CreatePolygonShape(c_bodyId, &entity.m_shapeDef, &c_polygon);
    } else {
      PACK_LIBRARY_LOG_WARNING("Unknown shape");
      continue;
    }

    this->m_viewport.add(std::move(entity.m_shapeUPtr), c_bodyId,
                         std::move(entity.m_brainUPtr));
  }
}

void app::main_loop() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  float timeAccumulator{0.0f};
  sf::Clock deltaClock{};

  while (this->m_window.isOpen()) {
    this->poll_events();

    if (!this->m_window.isOpen()) {
      PACK_LIBRARY_LOG_INFO("The window was closed by an event");
      break;
    }

    const sf::Time c_dt{deltaClock.restart()};
    const float c_dt_seconds{c_dt.asSeconds()};
    timeAccumulator += c_dt_seconds;

    PACK_LIBRARY_LOG_INFO("Delta time: " + std::to_string(c_dt_seconds));

    ImGui::SFML::Update(this->m_window, c_dt);

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    this->m_viewport.tick(c_dt_seconds);

    while (timeAccumulator >= gsc_defaultTimestep) {
      b2World_Step(this->m_worldId, gsc_defaultTimestep, gsc_iterationsCount);
      timeAccumulator -= gsc_defaultTimestep;
    }

    this->m_viewport.draw();

    const ImTextureID c_textureId{static_cast<ImTextureID>(
        this->m_viewport.get_texture().getTexture().getNativeHandle())};

    if (ImGui::Begin(gsc_viewportTitle.data(), nullptr,
                     ImGuiWindowFlags_NoScrollbar |
                         ImGuiWindowFlags_NoScrollWithMouse)) {
      ImGui::BeginChild(
          gsc_viewportTitle.data(), gsc_viewportSize, false,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

      const ImVec2 c_full = ImGui::GetContentRegionAvail();
      const ImVec2 c_zoomed{c_full.x * gs_zoom, c_full.y * gs_zoom};

      ImGui::Image(c_textureId, c_zoomed, gsc_lowerLeft, gsc_upperRight);

      ImGui::EndChild();
    }
    ImGui::End();

    if (ImGui::Begin(gsc_minimapTitle.data(), nullptr,
                     ImGuiWindowFlags_NoScrollbar |
                         ImGuiWindowFlags_NoScrollWithMouse)) {
      ImGui::BeginChild(
          gsc_minimapTitle.data(), gsc_minimapSize, false,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

      const ImVec2 c_position = ImGui::GetCursorScreenPos();

      ImGui::Image(c_textureId, gsc_minimapSize, gsc_lowerLeft, gsc_upperRight);

      const ImVec2 c_viewMin{c_position.x, c_position.y};
      const ImVec2 c_viewMax{c_position.x + gsc_minimapWidth / gs_zoom,
                             c_position.y + gsc_minimapHeight / gs_zoom};

      ImGui::GetWindowDrawList()->AddRect(
          c_viewMin, c_viewMax, IM_COL32(255, 0, 0, 255), 0.0f, 0, 1.0f);

      ImGui::EndChild();
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

    this->m_viewport.process_event(event);

    switch (event.type) {
      case sf::Event::Closed: {
        PACK_LIBRARY_LOG_INFO("Event sf::Event::Closed received");
        this->m_window.close();
        break;
      }
    }
  }
}

}  // namespace client
}  // namespace pack
