#include "pack_client_app.hpp"

#include <box2d/box2d.h>
#include <box2d/collision.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "../library/pack_library_actor.hpp"
#include "../library/pack_library_math.hpp"
#include "../library/pack_library_preprocessor.hpp"
#include "../library/pack_library_scene_entity.hpp"
#include "../library/pack_library_scene_loader.hpp"

namespace pack {
namespace client {

namespace {

constexpr std::uint32_t gsc_worldScale{5u};
constexpr std::uint32_t gsc_borderSize{36u};
constexpr std::uint32_t gsc_iterationsCount{6u};
constexpr std::uint32_t gsc_windowFramerateLimit{60u};

constexpr float gsc_defaultTimestep{1.0f / 600.0f};
constexpr float gsc_maxZoom{10.0f};

constexpr b2Vec2 gsc_gravity{0.0f, 0.0f};

constexpr std::uint32_t gsc_viewportWidth{1'280u};
constexpr std::uint32_t gsc_viewportHeight{720u};
constexpr std::uint32_t gsc_minimapWidth{gsc_viewportWidth / gsc_worldScale};
constexpr std::uint32_t gsc_minimapHeight{gsc_viewportHeight / gsc_worldScale};
constexpr std::uint32_t gsc_textureWidth{gsc_viewportWidth * gsc_worldScale};
constexpr std::uint32_t gsc_textureHeight{gsc_viewportHeight * gsc_worldScale};
constexpr std::uint32_t gsc_sceneManagerWidth{gsc_minimapWidth};
constexpr std::uint32_t gsc_sceneManagerHeight{gsc_minimapHeight -
                                               gsc_borderSize};
constexpr std::uint32_t gsc_windowWidth{gsc_viewportWidth + gsc_minimapWidth +
                                        gsc_borderSize};
constexpr std::uint32_t gsc_windowHeight{gsc_viewportHeight + gsc_borderSize};

constexpr std::string_view gsc_viewportTitle{"viewport"};
constexpr std::string_view gsc_minimapTitle{"minimap"};
constexpr std::string_view gsc_sceneManagerTitle{"scene manager"};
constexpr std::string_view gsc_windowTitle{"softpack"};
constexpr std::string_view gsc_sceneDirectory{"scene/"};

}  // namespace

app::app() noexcept
    : m_worldId{},
      m_window{sf::VideoMode{gsc_windowWidth, gsc_windowHeight},
               gsc_windowTitle.data()},
      m_scene{},
      m_sceneManager{gsc_sceneManagerWidth, gsc_sceneManagerHeight,
                     gsc_sceneManagerTitle, gsc_sceneDirectory},
      m_viewport{gsc_viewportWidth, gsc_viewportHeight, gsc_viewportTitle,
                 m_scene,           gsc_textureWidth,   gsc_textureHeight,
                 gsc_maxZoom},
      m_minimap{gsc_minimapWidth, gsc_minimapHeight, gsc_minimapTitle,
                m_scene,          gsc_textureWidth,  gsc_textureHeight} {
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

  this->main_loop();

  ImGui::SFML::Shutdown();
  PACK_LIBRARY_LOG_INFO("ImGui::SFML shut down");

  return true;
}

void app::load_scene(const std::string_view c_path) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  std::vector<library::scene_entity> entities{};

  if (!library::scene_loader::load(c_path, entities)) {
    return;
  }

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

    library::actor actor{std::move(entity.m_shapeUPtr), c_bodyId,
                         std::move(entity.m_brainUPtr)};

    this->m_scene.add(std::move(actor));
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

    if (this->m_sceneManager.get_state() ==
        library::scene_manager::state::READY) {
      this->m_sceneManager.set_state(library::scene_manager::state::RUNNING);
      this->load_scene(this->m_sceneManager.get_selected_scene());
    }

    const sf::Time c_dt{deltaClock.restart()};
    const float c_dt_seconds{c_dt.asSeconds()};
    timeAccumulator += c_dt_seconds;

    PACK_LIBRARY_LOG_INFO("Delta time: " + std::to_string(c_dt_seconds));

    ImGui::SFML::Update(this->m_window, c_dt);

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    this->m_scene.tick(c_dt_seconds);

    while (timeAccumulator >= gsc_defaultTimestep) {
      b2World_Step(this->m_worldId, gsc_defaultTimestep, gsc_iterationsCount);
      timeAccumulator -= gsc_defaultTimestep;
    }

    this->m_sceneManager.draw();
    this->m_viewport.draw();
    this->m_minimap.draw();

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
        PACK_LIBRARY_LOG_INFO("Event sf::Event::Closed received");

        this->m_window.close();
        return;
      }
    }

    if (this->m_viewport.process_event(event)) {
      this->m_minimap.set_view(this->m_viewport.get_view());
    } else if (this->m_minimap.process_event(event)) {
      this->m_viewport.set_view(this->m_minimap.get_view());
    }
  }
}

}  // namespace client
}  // namespace pack
