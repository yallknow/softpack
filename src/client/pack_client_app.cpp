#include "pack_client_app.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include "../library/pack_library_preprocessor.hpp"

namespace {

const std::string gsc_WindowTitle{"softpack"};
const std::string gsc_ViewportTitle{"viewport"};

constexpr std::uint32_t gsc_WindowWidth{1280u};
constexpr std::uint32_t gsc_WindowHeight{720u};
constexpr std::uint32_t gsc_WindowFramerateLimit{60u};

const sf::VideoMode gsc_VideoMode{gsc_WindowWidth, gsc_WindowHeight};

}  // namespace

namespace pack {
namespace client {

app::app() noexcept : mv_Window{gsc_VideoMode, gsc_WindowTitle}, mv_Texture{} {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Window.setFramerateLimit(gsc_WindowFramerateLimit);
  this->mv_Texture.create(gsc_WindowWidth, gsc_WindowHeight);
}

app::~app() noexcept { _PACK_LIBRARY_LOG_FUNCTION_CALL_(); }

bool app::mf_start() noexcept {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  ImGui::SFML::Init(this->mv_Window);

  ImGuiIO& ll_IO = ImGui::GetIO();
  ll_IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  this->mf_main_loop();

  ImGui::SFML::Shutdown();

  return true;
}

void app::mf_main_loop() noexcept {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  sf::Clock lv_DeltaClock{};

  while (this->mv_Window.isOpen()) {
    this->mf_poll_events();

    if (!this->mv_Window.isOpen()) {
      break;
    }

    ImGui::SFML::Update(this->mv_Window, lv_DeltaClock.restart());

    ImGui::DockSpaceOverViewport();
    ImGui::ShowDemoWindow();

    this->mf_handle_viewport();

    ImGui::SFML::Render(this->mv_Window);

    this->mv_Window.display();
  }
}

void app::mf_poll_events() noexcept {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  sf::Event lv_Event{};

  while (this->mv_Window.pollEvent(lv_Event)) {
    ImGui::SFML::ProcessEvent(this->mv_Window, lv_Event);

    switch (lv_Event.type) {
      case sf::Event::Closed: {
        this->mv_Window.close();
        break;
      }
    }
  }
}

void app::mf_handle_viewport() noexcept {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Texture.clear(sf::Color::Black);

  this->mf_draw_viewport();

  if (ImGui::Begin(gsc_ViewportTitle.c_str())) {
    ImGui::Image(this->mv_Texture);
  }
  ImGui::End();
}

void app::mf_draw_viewport() noexcept {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  sf::CircleShape shape(50.0f);
  shape.setFillColor(sf::Color{150, 50, 250});
  shape.setOutlineThickness(10.0f);
  shape.setOutlineColor(sf::Color{250, 150, 100});

  this->mv_Texture.draw(shape);
}

}  // namespace client
}  // namespace pack
