#pragma once

#ifndef PACK_LIBRARY_SCENE_LOADER
#define PACK_LIBRARY_SCENE_LOADER

#include <boost/core/noncopyable.hpp>
#include <string_view>
#include <vector>

#include "pack_library_scene_entity.hpp"

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
  static bool load(const std::string_view c_path,
                   std::vector<library::scene_entity>& entitiesLink) noexcept;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCENE_LOADER
