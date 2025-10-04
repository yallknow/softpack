#pragma once

#ifndef PACK_LIBRARY_SCENE_LOADER
#define PACK_LIBRARY_SCENE_LOADER

#include <SFML/Graphics/Shape.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>
#include <string_view>
#include <vector>

namespace pack {
namespace library {

class scene_loader final : private boost::noncopyable {
 public:
  explicit scene_loader() noexcept = delete;
  /* virtual */ ~scene_loader() noexcept = delete;

 public:
  explicit scene_loader(scene_loader&& otherRLink) noexcept = delete;
  scene_loader& operator=(scene_loader&& otherRLink) noexcept = delete;

 public:
  static bool load(
      const std::string_view c_path,
      std::vector<std::unique_ptr<sf::Shape>>& shapesLink) noexcept;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCENE_LOADER
