#include "pack_library_time.hpp"

#include <algorithm>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>

std::string pack::library::time::msf_now() noexcept {
  return boost::posix_time::to_iso_extended_string(
      boost::posix_time::microsec_clock::local_time());
}

std::string pack::library::time::msf_now_underscore() noexcept {
  std::string lv_TimeNow{msf_now()};

  std::replace_if(
      lv_TimeNow.begin(), lv_TimeNow.end(),
      [](const char pc_Symbol) noexcept -> bool {
        return !std::isdigit(pc_Symbol);
      },
      '_');

  return lv_TimeNow;
}

std::uint64_t pack::library::time::msf_since_epoch() noexcept {
  return std::chrono::duration_cast<std::chrono::microseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}
