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

  if (ImGui::Begin(
          this->mc_title.data(), nullptr,
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
    const ImVec2 c_size{static_cast<float>(this->mc_width),
                        static_cast<float>(this->mc_height)};

    // BeginDisabled gsc_btnRefresh && Selectable
    state currentState = this->m_state;

    if (currentState != state::IDLE && currentState != state::SELECTED) {
      ImGui::BeginDisabled();
    }

    ImGui::BeginChild(this->mc_title.data(), c_size, false,
                      ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& c_scene : this->m_scenes) {
      if (ImGui::Selectable(c_scene.data(), c_scene == this->m_selectedScene)) {
        PACK_LIBRARY_LOG_INFO("Scene loader state changed to SELECTED");

        this->m_state = state::SELECTED;
        this->m_selectedScene = c_scene;
      }
    }

    ImGui::EndChild();

    if (ImGui::Button(gsc_btnRefresh.data())) {
      PACK_LIBRARY_LOG_INFO("Scene loader state changed to IDLE");

      this->m_state = state::IDLE;
      this->refresh();
    }

    if (currentState != state::IDLE && currentState != state::SELECTED) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnRefresh && Selectable

    ImGui::SameLine();

    // BeginDisabled gsc_btnLoad
    currentState = this->m_state;

    if (currentState != state::SELECTED) {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button(gsc_btnLoad.data())) {
      PACK_LIBRARY_LOG_INFO("Scene loader state changed to READY");

      this->m_state = state::READY;
    }

    if (currentState != state::SELECTED) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnLoad

    ImGui::SameLine();

    // BeginDisabled gsc_btnPause
    if (currentState != state::RUNNING) {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button(gsc_btnPause.data())) {
      PACK_LIBRARY_LOG_INFO("Scene loader state changed to PAUSED");

      this->m_state = state::PAUSED;
    }

    if (currentState != state::RUNNING) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnPause

    ImGui::SameLine();

    // BeginDisabled gsc_btnResume
    if (currentState != state::PAUSED) {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button(gsc_btnResume.data())) {
      PACK_LIBRARY_LOG_INFO("Scene loader state changed to RUNNING");

      this->m_state = state::RUNNING;
    }

    if (currentState != state::PAUSED) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnResume

    ImGui::SameLine();

    // BeginDisabled gsc_btnDrop
    if (currentState != state::PAUSED) {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button(gsc_btnDrop.data())) {
      PACK_LIBRARY_LOG_INFO("Scene loader state changed to DROPPED");

      this->m_state = state::DROPPED;
      this->refresh();
    }

    if (currentState != state::PAUSED) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnDrop
  }
  ImGui::End();
}

bool scene_manager::process_event(const sf::Event& c_event) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return false;
}

scene_manager::state scene_manager::get_state() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return this->m_state;
}

void scene_manager::set_state(const state& c_state) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

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

}  // namespace library
}  // namespace pack
