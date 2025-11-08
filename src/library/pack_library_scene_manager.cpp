#include "pack_library_scene_manager.hpp"

#include <imgui.h>

#include <filesystem>

#include "pack_library_preprocessor.hpp"

namespace {

constexpr std::string_view gsc_btnLoadSceneList{"refresh"};
constexpr std::string_view gsc_btnLoadSelectedScene{"load"};

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

    // BeginDisabled gsc_btnLoadSceneList && Selectable
    state currentState = this->m_state;

    if (currentState != state::IDLE && currentState != state::SELECTED) {
      ImGui::BeginDisabled();
    }

    ImGui::BeginChild(this->mc_title.data(), c_size, false,
                      ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& c_scene : this->m_scenes) {
      if (ImGui::Selectable(c_scene.data(), c_scene == this->m_selectedScene)) {
        this->m_state = state::SELECTED;
        this->m_selectedScene = c_scene;
      }
    }

    ImGui::EndChild();

    if (ImGui::Button(gsc_btnLoadSceneList.data())) {
      this->m_state = state::IDLE;
      this->load_scenes();
    }

    if (currentState != state::IDLE && currentState != state::SELECTED) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnLoadSceneList && Selectable

    ImGui::SameLine();

    // BeginDisabled gsc_btnLoadSelectedScene
    currentState = this->m_state;

    if (currentState != state::SELECTED) {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button(gsc_btnLoadSelectedScene.data())) {
      this->m_state = state::READY;
    }

    if (currentState != state::SELECTED) {
      ImGui::EndDisabled();
    }  // EndDisabled gsc_btnLoadSelectedScene
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

bool scene_manager::load_scenes() noexcept {
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
