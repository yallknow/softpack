#include "pack_library_scene_loader.hpp"

#include <json/reader.h>
#include <json/value.h>

#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <filesystem>
#include <fstream>
#include <memory>

#include "pack_library_preprocessor.hpp"

namespace pack {
namespace library {

namespace {

void load_circles(const Json::Value& c_root,
                  std::vector<library::scene_entity>& entitiesLink) {
  if (!c_root.isMember("circles") || !c_root["circles"].isArray()) {
    return;
  }

  for (const Json::Value& c_circle : c_root["circles"]) {
    if (!c_circle.isMember("radius") || !c_circle["radius"].isNumeric()) {
      continue;  // Required
    }

    auto shapeUPtr{
        std::make_unique<sf::CircleShape>(c_circle["radius"].asFloat())};

    if (c_circle.isMember("origin")) {
      const Json::Value& c_origin{c_circle["origin"]};

      if (c_origin.isMember("x") && c_origin["x"].isNumeric() &&
          c_origin.isMember("y") && c_origin["y"].isNumeric()) {
        shapeUPtr->setOrigin(c_origin["x"].asFloat(), c_origin["y"].asFloat());
      }
    }

    if (c_circle.isMember("position")) {
      const Json::Value& c_position{c_circle["position"]};

      if (c_position.isMember("x") && c_position["x"].isNumeric() &&
          c_position.isMember("y") && c_position["y"].isNumeric()) {
        shapeUPtr->setPosition(c_position["x"].asFloat(),
                               c_position["y"].asFloat());
      }
    }

    if (c_circle.isMember("color")) {
      const Json::Value& c_color{c_circle["color"]};

      if (c_color.isMember("r") && c_color["r"].isUInt() &&
          c_color.isMember("g") && c_color["g"].isUInt() &&
          c_color.isMember("b") && c_color["b"].isUInt()) {
        shapeUPtr->setFillColor(
            sf::Color{static_cast<sf::Uint8>(c_color["r"].asUInt()),
                      static_cast<sf::Uint8>(c_color["g"].asUInt()),
                      static_cast<sf::Uint8>(c_color["b"].asUInt())});
      }
    }

    entitiesLink.emplace_back(std::move(shapeUPtr), b2BodyId{}, nullptr);
  }
}

}  // namespace

bool scene_loader::load(
    const std::string_view c_path,
    std::vector<library::scene_entity>& entitiesLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (!std::filesystem::exists(c_path)) {
    PACK_LIBRARY_LOG_ERROR("The scene description file does not exist!");
    return false;
  }

  Json::Value root{};

  try {
    std::ifstream file{c_path.data(), std::ifstream::binary};

    if (!file.is_open()) {
      return false;
    }

    file >> root;
  } catch (const Json::LogicError& c_exception) {
    PACK_LIBRARY_LOG_ERROR("Exception Json::LogicError:" +
                           std::string{c_exception.what()});

    return false;
  } catch (const Json::RuntimeError& c_exception) {
    PACK_LIBRARY_LOG_ERROR("Exception Json::RuntimeError:" +
                           std::string{c_exception.what()});

    return false;
  }

  load_circles(root, entitiesLink);

  return true;
}

}  // namespace library
}  // namespace pack
