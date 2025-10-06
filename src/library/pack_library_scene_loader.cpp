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
constexpr std::string_view gsc_maxVelocityProp{"maxVelocity"};
constexpr std::string_view gsc_jitterStepProp{"jitterStep"};

constexpr std::string_view gsc_circleShape{"circle"};
constexpr std::string_view gsc_rectangleShape{"rectangle"};

enum class brain { WANDER = 0 };

bool contains_key(const Json::Value& c_value, const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  const bool c_result = c_value.isMember(key.data());

  if (!c_result) {
    PACK_LIBRARY_LOG_WARNING(
        "Could not find JSON property: " + std::string(key) + "!");
  }

  return c_result;
}

bool contains_string(const Json::Value& c_value, const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_key(c_value, key) && c_value[key.data()].isString();
}

bool contains_double(const Json::Value& c_value, const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_key(c_value, key) && c_value[key.data()].isDouble();
}

bool contains_int(const Json::Value& c_value, const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_key(c_value, key) && c_value[key.data()].isInt();
}

bool contains_array(const Json::Value& c_value, const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_key(c_value, key) && c_value[key.data()].isArray();
}

std::optional<std::string> get_string(const Json::Value& c_value,
                                      const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_string(c_value, key)
             ? c_value[key.data()].asString()
             : std::optional<std::string>{std::nullopt};
}

std::optional<float> get_float(const Json::Value& c_value,
                               const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_double(c_value, key) ? c_value[key.data()].asFloat()
                                       : std::optional<float>{std::nullopt};
}

std::optional<int> get_int(const Json::Value& c_value,
                           const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  return contains_int(c_value, key) ? c_value[key.data()].asInt()
                                    : std::optional<int>{std::nullopt};
}

std::optional<sf::Vector2f> get_vector2f(const Json::Value& c_value,
                                         const std::string_view key) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (contains_key(c_value, key)) {
    const auto c_x = get_float(c_value[key.data()], gsc_xProp);
    const auto c_y = get_float(c_value[key.data()], gsc_yProp);

    if (c_x && c_y) {
      return sf::Vector2f{c_x.value(), c_y.value()};
    }
  }

  return std::nullopt;
}

void load_common(const Json::Value& c_entity, sf::Shape& shapeLink) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (const auto c_origin = get_vector2f(c_entity, gsc_originProp)) {
    shapeLink.setOrigin(c_origin.value());
  }

  if (const auto c_position = get_vector2f(c_entity, gsc_positionProp)) {
    shapeLink.setPosition(c_position.value());
  }

  if (contains_key(c_entity, gsc_colorProp)) {
    const Json::Value& c_color{c_entity[gsc_colorProp.data()]};

    const auto c_red = get_int(c_color, gsc_redProp);
    const auto c_green = get_int(c_color, gsc_greenProp);
    const auto c_blue = get_int(c_color, gsc_blueProp);

    if (c_red && c_green && c_blue) {
      shapeLink.setFillColor(sf::Color{static_cast<sf::Uint8>(c_red.value()),
                                       static_cast<sf::Uint8>(c_green.value()),
                                       static_cast<sf::Uint8>(c_blue.value())});
    }
  }
}

void load_body(const Json::Value& c_body, b2BodyDef& bodyDefLink,
               b2ShapeDef& shapeDefLink) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (const auto c_type = get_int(c_body, gsc_typeProp)) {
    bodyDefLink.type = static_cast<b2BodyType>(c_type.value());
  }

  if (const auto c_position = get_vector2f(c_body, gsc_positionProp)) {
    bodyDefLink.position = b2Vec2{c_position.value().x / gsc_scale,
                                  c_position.value().y / gsc_scale};
  }

  if (const auto c_linearDamping = get_float(c_body, gsc_linearDampingProp)) {
    bodyDefLink.linearDamping = c_linearDamping.value();
  }

  if (const auto c_angularDamping = get_float(c_body, gsc_angularDampingProp)) {
    bodyDefLink.angularDamping = c_angularDamping.value();
  }

  if (const auto c_density = get_float(c_body, gsc_densityProp)) {
    shapeDefLink.density = c_density.value();
  }

  if (const auto c_friction = get_float(c_body, gsc_frictionProp)) {
    shapeDefLink.material.friction = c_friction.value();
  }

  if (const auto c_restitution = get_float(c_body, gsc_restitutionProp)) {
    shapeDefLink.material.restitution = c_restitution.value();
  }
}

std::unique_ptr<abstract::brain> load_brain(const Json::Value& c_brain) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (const auto c_type = get_int(c_brain, gsc_typeProp)) {
    if (static_cast<brain>(c_type.value()) == brain::WANDER) {
      sf::Vector2f velocity{0.0f, 0.0f};
      sf::Vector2f maxVelocity{0.0f, 0.0f};
      float jitterStep{0.0f};

      if (const auto c_velocity = get_vector2f(c_brain, gsc_velocityProp)) {
        velocity = c_velocity.value();
      }

      if (const auto c_maxVelocity =
              get_vector2f(c_brain, gsc_maxVelocityProp)) {
        maxVelocity = c_maxVelocity.value();
      }

      if (const auto c_jitterStep = get_float(c_brain, gsc_jitterStepProp)) {
        jitterStep = c_jitterStep.value();
      }

      return std::make_unique<wander_brain>(velocity, maxVelocity, jitterStep);
    }
  }

  return nullptr;
}

void load_entities(const Json::Value& c_root,
                   std::vector<library::scene_entity>& entitiesLink) {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (!contains_array(c_root, gsc_entitiesProp)) {
    PACK_LIBRARY_LOG_ERROR("Entity array not found");
    return;
  }

  for (const Json::Value& c_entity : c_root[gsc_entitiesProp.data()]) {
    if (const auto c_shape{get_string(c_entity, gsc_shapeProp)}) {
      std::unique_ptr<sf::Shape> shapeUPtr{nullptr};

      if (c_shape.value() == gsc_circleShape) {
        auto circleUPtr{std::make_unique<sf::CircleShape>()};

        if (const auto c_radius = get_float(c_entity, gsc_radiusProp)) {
          circleUPtr->setRadius(c_radius.value());
        }

        shapeUPtr = std::move(circleUPtr);
      } else if (c_shape.value() == gsc_rectangleShape) {
        auto rectangleUPtr{std::make_unique<sf::RectangleShape>()};

        if (const auto c_size = get_vector2f(c_entity, gsc_sizeProp)) {
          rectangleUPtr->setSize(c_size.value());
        }

        shapeUPtr = std::move(rectangleUPtr);
      } else {
        PACK_LIBRARY_LOG_ERROR("Unknown shape property: " + c_shape.value());
      }

      if (shapeUPtr) {
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
}

}  // namespace

bool scene_loader::load(
    const std::string_view c_path,
    std::vector<library::scene_entity>& entitiesLink) noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  if (!std::filesystem::exists(c_path)) {
    PACK_LIBRARY_LOG_ERROR("The JSON file: " + std::string{c_path} +
                           " does not exist");
    return false;
  }

  std::ifstream file{c_path.data(), std::ifstream::binary};

  if (!file.is_open()) {
    PACK_LIBRARY_LOG_ERROR("Failed to open JSON file: " + std::string{c_path});
    return false;
  }

  Json::CharReaderBuilder builder{};
  Json::Value root{};
  std::string error{};

  if (!Json::parseFromStream(builder, file, &root, &error)) {
    PACK_LIBRARY_LOG_ERROR("Failed to parse JSON file: " + error);
    return false;
  }

  load_entities(root, entitiesLink);

  PACK_LIBRARY_LOG_INFO("Successfully loaded " +
                        std::to_string(entitiesLink.size()) +
                        " entities from JSON file");

  return true;
}

}  // namespace library
}  // namespace pack
