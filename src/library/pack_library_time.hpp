#pragma once

#ifndef PACK_LIBRARY_TIME
#define PACK_LIBRARY_TIME

#include <cstdint>
#include <string>

namespace pack {
namespace library {

class time final {
 public:
  explicit time() noexcept = delete;
  /* virtual */ ~time() noexcept = delete;

 public:
  explicit time(const time& c_other) noexcept = delete;
  explicit time(time&& otherRLink) noexcept = delete;

 public:
  time& operator=(const time& c_other) noexcept = delete;
  time& operator=(time&& otherRLink) noexcept = delete;

 public:
  static std::string now() noexcept;
  static std::string now_underscore() noexcept;

  static std::uint64_t since_epoch() noexcept;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_TIME
