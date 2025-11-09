#pragma once

#ifndef PACK_LIBRARY_MATH
#define PACK_LIBRARY_MATH

namespace pack {
namespace library {

namespace {

constexpr float gsc_scale{30.0f};
constexpr float gsc_rad{180.0f};
constexpr float gsc_pi{3.14159265f};

float rad_to_deg(const float c_rad) noexcept {
  return c_rad * gsc_rad / gsc_pi;
}

}  // namespace

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_MATH
