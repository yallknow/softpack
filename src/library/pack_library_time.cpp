#include "pack_library_time.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <algorithm>
#include <chrono>

namespace pack {
namespace library {

std::string time::now() noexcept {
  return boost::posix_time::to_iso_extended_string(
      boost::posix_time::microsec_clock::local_time());
}

std::string time::now_underscore() noexcept {
  std::string currentTime{now()};

  std::replace_if(
      currentTime.begin(), currentTime.end(),
      [](const char c_symbol) noexcept -> bool {
        return !std::isdigit(c_symbol);
      },
      '_');

  return currentTime;
}

std::uint64_t time::since_epoch() noexcept {
  return static_cast<std::uint64_t>(
      std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count());
}

}  // namespace library
}  // namespace pack
