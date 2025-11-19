#include "pack_library_scene_manager.hpp"

#include <imgui.h>

#include <filesystem>

#include "pack_library_preprocessor.hpp"

namespace {

constexpr std::string_view gsc_btnRefresh{"refresh"};
constexpr std::string_view gsc_btnLoad{"load"};
constexpr std::string_view gsc_btnPause{"pause"};
constexpr std::string_view gsc_btnResume{"resume"};
constexpr std::string_view gsc_btnDrop{"drop"};

void draw_button(const std::string_view c_title, const bool c_disable,
                 const std::function<void()> c_onClick) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (c_disable) {
    ImGui::BeginDisabled();
  }

  if (ImGui::Button(c_title.data())) {
    c_onClick();
  }

  if (c_disable) {
    ImGui::EndDisabled();
  }
}

}  // namespace

namespace pack {
namespace library {

scene_manager::scene_manager(const std::uint32_t c_width,
                             const std::uint32_t c_height,
                             const std::string_view c_title,
                             const std::string_view c_path) noexcept
    : abstract::widget{c_width, c_height, c_title},
      mc_path{c_path},
      m_state{state::IDLE},
      m_selectedScene{},
      m_scenes{} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

scene_manager::~scene_manager() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

void scene_manager::draw() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->get_state();  // To log the current state

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    const ImVec2 c_size{static_cast<float>(this->mc_width),
                        static_cast<float>(this->mc_height)};

    // BeginDisabled Selectable
    const bool c_isSelectableDisabled{this->m_state != state::IDLE &&
                                      this->m_state != state::SELECTED};

    if (c_isSelectableDisabled) {
      ImGui::BeginDisabled();
    }

    ImGui::BeginChild(this->mc_title.data(), c_size, false,
                      ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& c_scene : this->m_scenes) {
      if (ImGui::Selectable(c_scene.data(), c_scene == this->m_selectedScene)) {
        this->set_state(state::SELECTED);
        this->m_selectedScene = c_scene;
      }
    }

    ImGui::EndChild();

    if (c_isSelectableDisabled) {
      ImGui::EndDisabled();
    }  // EndDisabled Selectable

    draw_button(
        gsc_btnRefresh,
        this->m_state != state::IDLE && this->m_state != state::SELECTED,
        [this]() -> void {
          PACK_LIBRARY_LOG_FUNCTION_CALL();

          this->set_state(state::IDLE);
          this->refresh();
        });

    ImGui::SameLine();

    draw_button(gsc_btnLoad, this->m_state != state::SELECTED,
                [this]() -> void {
                  PACK_LIBRARY_LOG_FUNCTION_CALL();

                  this->set_state(state::READY);
                });

    ImGui::SameLine();

    draw_button(gsc_btnPause, this->m_state != state::RUNNING,
                [this]() -> void {
                  PACK_LIBRARY_LOG_FUNCTION_CALL();

                  this->set_state(state::PAUSED);
                });

    ImGui::SameLine();

    draw_button(gsc_btnResume, this->m_state != state::PAUSED,
                [this]() -> void {
                  PACK_LIBRARY_LOG_FUNCTION_CALL();

                  this->set_state(state::RUNNING);
                });

    ImGui::SameLine();

    draw_button(gsc_btnDrop, this->m_state != state::PAUSED, [this]() -> void {
      PACK_LIBRARY_LOG_FUNCTION_CALL();

      this->set_state(state::DROPPED);
      this->refresh();
    });
  }
  ImGui::End();
}

bool scene_manager::process_event(const sf::Event& c_event) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return false;
}

scene_manager::state scene_manager::get_state() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  PACK_LIBRARY_LOG_INFO("Current state: " + state_to_string(this->m_state));

  return this->m_state;
}

void scene_manager::set_state(const state c_state) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  PACK_LIBRARY_LOG_INFO("Changing state from " +
                        state_to_string(this->m_state) + " to " +
                        state_to_string(c_state));

  this->m_state = c_state;
}

std::string scene_manager::get_selected_scene() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->mc_path + this->m_selectedScene;
}

bool scene_manager::refresh() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  this->m_selectedScene.clear();
  this->m_scenes.clear();

  if (!std::filesystem::exists(this->mc_path) ||
      !std::filesystem::is_directory(this->mc_path)) {
    PACK_LIBRARY_LOG_ERROR("The directory: " + std::string{this->mc_path} +
                           " does not exist");

    return false;
  }

  for (const std::filesystem::directory_entry& c_entry :
       std::filesystem::directory_iterator(this->mc_path)) {
    if (c_entry.is_regular_file()) {
      this->m_scenes.emplace_back(c_entry.path().filename().string());
    }
  }

  return true;
}

std::string scene_manager::state_to_string(const state c_state) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  switch (c_state) {
    case state::IDLE:
      return std::string{"IDLE"};
    case state::SELECTED:
      return std::string{"SELECTED"};
    case state::READY:
      return std::string{"READY"};
    case state::RUNNING:
      return std::string{"RUNNING"};
    case state::PAUSED:
      return std::string{"PAUSED"};
    case state::DROPPED:
      return std::string{"DROPPED"};
  }

  return std::string{"UNKNOWN"};
}

}  // namespace library
}  // namespace pack
