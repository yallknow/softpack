#include "pack_library_scene_loader.hpp"

#include <box2d/math_functions.h>
#include <box2d/types.h>
#include <json/reader.h>
#include <json/value.h>

#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "abstract/pack_library_abstract_brain.hpp"
#include "pack_library_math.hpp"
#include "pack_library_preprocessor.hpp"
#include "pack_library_wander_brain.hpp"

namespace pack {
namespace library {

namespace {

constexpr std::string_view gsc_entitiesProp{"entities"};
constexpr std::string_view gsc_shapeProp{"shape"};

constexpr std::string_view gsc_radiusProp{"radius"};

constexpr std::string_view gsc_sizeProp{"size"};
constexpr std::string_view gsc_widthProp{"width"};
constexpr std::string_view gsc_heightProp{"height"};

constexpr std::string_view gsc_originProp{"origin"};
constexpr std::string_view gsc_positionProp{"position"};
constexpr std::string_view gsc_xProp{"x"};
constexpr std::string_view gsc_yProp{"y"};

constexpr std::string_view gsc_colorProp{"color"};
constexpr std::string_view gsc_redProp{"red"};
constexpr std::string_view gsc_greenProp{"green"};
constexpr std::string_view gsc_blueProp{"blue"};

constexpr std::string_view gsc_bodyProp{"body"};
constexpr std::string_view gsc_typeProp{"type"};
constexpr std::string_view gsc_linearDampingProp{"linearDamping"};
constexpr std::string_view gsc_angularDampingProp{"angularDamping"};
constexpr std::string_view gsc_densityProp{"density"};
constexpr std::string_view gsc_frictionProp{"friction"};
constexpr std::string_view gsc_restitutionProp{"restitution"};

constexpr std::string_view gsc_brainProp{"brain"};
constexpr std::string_view gsc_velocityProp{"velocity"};

constexpr std::string_view gsc_circleShape{"circle"};
constexpr std::string_view gsc_rectangleShape{"rectangle"};

bool contains_key(const Json::Value& c_value, const std::string_view key) {
  const bool c_result = c_value.isMember(key.data());

  if (!c_result) {
    PACK_LIBRARY_LOG_WARNING(
        "Could not find json property: " + std::string(key) + "!");
  }

  return c_result;
}

bool contains_string(const Json::Value& c_value, const std::string_view key) {
  return contains_key(c_value, key) && c_value[key.data()].isString();
}

bool contains_double(const Json::Value& c_value, const std::string_view key) {
  return contains_key(c_value, key) && c_value[key.data()].isDouble();
}

bool contains_int(const Json::Value& c_value, const std::string_view key) {
  return contains_key(c_value, key) && c_value[key.data()].isInt();
}

std::optional<std::string> get_string(const Json::Value& c_value,
                                      const std::string_view key) {
  return contains_string(c_value, key)
             ? c_value[key.data()].asString()
             : std::optional<std::string>{std::nullopt};
}

std::optional<float> get_float(const Json::Value& c_value,
                               const std::string_view key) {
  return contains_double(c_value, key) ? c_value[key.data()].asFloat()
                                       : std::optional<float>{std::nullopt};
}

std::optional<int> get_int(const Json::Value& c_value,
                           const std::string_view key) {
  return contains_int(c_value, key) ? c_value[key.data()].asInt()
                                    : std::optional<int>{std::nullopt};
}

void load_common(const Json::Value& c_entity, sf::Shape& shapeLink) {
  if (contains_key(c_entity, gsc_originProp)) {
    const Json::Value& c_origin{c_entity[gsc_originProp.data()]};

    auto x = get_float(c_origin, gsc_xProp);
    auto y = get_float(c_origin, gsc_yProp);

    if (x && y) {
      shapeLink.setOrigin(x.value(), y.value());
    }
  }

  if (contains_key(c_entity, gsc_positionProp)) {
    const Json::Value& c_position{c_entity[gsc_positionProp.data()]};

    auto x = get_float(c_position, gsc_xProp);
    auto y = get_float(c_position, gsc_yProp);

    if (x && y) {
      shapeLink.setPosition(x.value(), y.value());
    }
  }

  if (contains_key(c_entity, gsc_colorProp)) {
    const Json::Value& c_color{c_entity[gsc_colorProp.data()]};

    auto red = get_int(c_color, gsc_redProp);
    auto green = get_int(c_color, gsc_greenProp);
    auto blue = get_int(c_color, gsc_blueProp);

    if (red && green && blue) {
      shapeLink.setFillColor(sf::Color{static_cast<sf::Uint8>(red.value()),
                                       static_cast<sf::Uint8>(green.value()),
                                       static_cast<sf::Uint8>(blue.value())});
    }
  }
}

void load_body(const Json::Value& c_body, b2BodyDef& bodyDefLink,
               b2ShapeDef& shapeDefLink) {
  if (auto type = get_int(c_body, gsc_typeProp)) {
    bodyDefLink.type = static_cast<b2BodyType>(type.value());
  }

  if (contains_key(c_body, gsc_positionProp)) {
    const Json::Value& c_position{c_body[gsc_positionProp.data()]};

    const auto x = get_float(c_position, gsc_xProp);
    const auto y = get_float(c_position, gsc_yProp);

    if (x && y) {
      bodyDefLink.position =
          b2Vec2{x.value() / gsc_scale, y.value() / gsc_scale};
    }
  }

  if (const auto linearDamping = get_float(c_body, gsc_linearDampingProp)) {
    bodyDefLink.linearDamping = linearDamping.value();
  }

  if (const auto angularDamping = get_float(c_body, gsc_angularDampingProp)) {
    bodyDefLink.angularDamping = angularDamping.value();
  }

  if (const auto density = get_float(c_body, gsc_densityProp)) {
    shapeDefLink.density = density.value();
  }

  if (const auto friction = get_float(c_body, gsc_frictionProp)) {
    shapeDefLink.material.friction = friction.value();
  }

  if (const auto restitution = get_float(c_body, gsc_restitutionProp)) {
    shapeDefLink.material.restitution = restitution.value();
  }
}

std::unique_ptr<abstract::brain> load_brain(const Json::Value& c_brain) {
  if (const auto type = get_int(c_brain, gsc_typeProp)) {
    if (type == 0) {
      sf::Vector2f initialVelocity{0.0f, 0.0f};

      if (contains_key(c_brain, gsc_velocityProp)) {
        const Json::Value& c_velocity{c_brain[gsc_velocityProp.data()]};

        const auto x = get_float(c_velocity, gsc_xProp);
        const auto y = get_float(c_velocity, gsc_yProp);

        if (x && y) {
          initialVelocity.x = x.value();
          initialVelocity.y = y.value();
        }
      }

      return std::make_unique<wander_brain>(initialVelocity);
    }
  }

  return nullptr;
}

void load_entities(const Json::Value& c_root,
                   std::vector<library::scene_entity>& entitiesLink) {
  if (!contains_key(c_root, gsc_entitiesProp) ||
      !c_root[gsc_entitiesProp.data()].isArray()) {
    return;
  }

  for (const Json::Value& c_entity : c_root[gsc_entitiesProp.data()]) {
    if (auto shape{get_string(c_entity, gsc_shapeProp)}) {
      std::unique_ptr<sf::Shape> shapeUPtr{nullptr};

      if (shape.value() == gsc_circleShape) {
        auto circleUPtr{std::make_unique<sf::CircleShape>()};

        if (auto radius = get_float(c_entity, gsc_radiusProp)) {
          circleUPtr->setRadius(radius.value());
        }

        shapeUPtr = std::move(circleUPtr);
      } else if (shape.value() == gsc_rectangleShape) {
        auto rectangleUPtr{std::make_unique<sf::RectangleShape>()};

        if (contains_key(c_entity, gsc_sizeProp)) {
          const Json::Value& c_size{c_entity[gsc_sizeProp.data()]};

          auto width = get_float(c_size, gsc_widthProp);
          auto height = get_float(c_size, gsc_heightProp);

          if (width && height) {
            rectangleUPtr->setSize(sf::Vector2f{width.value(), height.value()});
          }
        }

        shapeUPtr = std::move(rectangleUPtr);
      }

      load_common(c_entity, *shapeUPtr);

      b2BodyDef bodyDef{b2DefaultBodyDef()};
      b2ShapeDef shapeDef{b2DefaultShapeDef()};

      if (contains_key(c_entity, gsc_bodyProp)) {
        load_body(c_entity[gsc_bodyProp.data()], bodyDef, shapeDef);
      }

      std::unique_ptr<abstract::brain> brainUPtr{nullptr};

      if (contains_key(c_entity, gsc_brainProp)) {
        brainUPtr = load_brain(c_entity[gsc_brainProp.data()]);
      }

      entitiesLink.emplace_back(std::move(shapeUPtr), bodyDef, shapeDef,
                                std::move(brainUPtr));
    }
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
    PACK_LIBRARY_LOG_ERROR(
        "Exception Json::LogicError:" + std::string{c_exception.what()} + "!");

    return false;
  } catch (const Json::RuntimeError& c_exception) {
    PACK_LIBRARY_LOG_ERROR("Exception Json::RuntimeError:" +
                           std::string{c_exception.what()} + "!");

    return false;
  }

  load_entities(root, entitiesLink);

  return true;
}

}  // namespace library
}  // namespace pack
