#pragma once

#ifndef PACK_LIBRARY_TIME
#define PACK_LIBRARY_TIME

#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <string>

namespace pack {
namespace library {

class time final : private boost::noncopyable {
 public:
  explicit time() noexcept = delete;
  /* virtual */ ~time() noexcept = delete;

 public:
  explicit time(time&& otherRLink) noexcept = delete;
  time& operator=(time&& otherRLink) noexcept = delete;

 public:
  static std::string now() noexcept;
  static std::string now_underscore() noexcept;

  static std::uint64_t since_epoch() noexcept;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_TIME
