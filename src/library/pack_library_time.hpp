#pragma once

#ifndef _PACK_LIBRARY_TIME_
#define _PACK_LIBRARY_TIME_

#include <cstdint>
#include <string>

namespace pack {
namespace library {

class time final {
 public:
  static std::string msf_now() noexcept;
  static std::string msf_now_underscore() noexcept;

  static std::uint64_t msf_since_epoch() noexcept;

 public:
  explicit time() noexcept = delete;
  /* virtual */ ~time() noexcept = delete;

 public:
  explicit time(const time& pcl_Other) noexcept = delete;
  explicit time(time&& pr_Other) noexcept = delete;

 public:
  time& operator=(const time& pcl_Other) noexcept = delete;
  time& operator=(time&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace pack

#endif  // !_PACK_LIBRARY_TIME_
