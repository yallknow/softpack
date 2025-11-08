#pragma once

#ifndef PACK_LIBRARY_SCENE_MANAGER
#define PACK_LIBRARY_SCENE_MANAGER

#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "abstract/pack_library_abstract_widget.hpp"

namespace pack {
namespace library {

class scene_manager final : public abstract::widget {
 public:
  enum class state : std::uint32_t {
    IDLE = 0,
    SELECTED = 1,
    READY = 2,
    RUNNING = 3
  };

 public:
  explicit scene_manager(const std::uint32_t c_width,
                         const std::uint32_t c_height,
                         const std::string_view c_title,
                         const std::string_view c_path) noexcept;
  /* virtual */ ~scene_manager() noexcept;

 public:
  explicit scene_manager(scene_manager&& otherRLink) noexcept = delete;
  scene_manager& operator=(scene_manager&& otherRLink) noexcept = delete;

 public:  // abstract::widget
  void draw() noexcept override;
  bool process_event(const sf::Event& c_event) noexcept override;

 public:
  state get_state() const noexcept;
  void set_state(const state& c_state) noexcept;

  std::string get_selected_scene() const noexcept;

 private:
  bool load_scenes() noexcept;

 private:
  const std::string mc_path;

 private:
  state m_state;

  std::string m_selectedScene;
  std::vector<std::string> m_scenes;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCENE_MANAGER
