#include "pack_library_log_builder.hpp"

#include "pack_library_logger.hpp"
#include "pack_library_time.hpp"

namespace pack {
namespace library {

std::atomic<bool> log_builder::msv_IsInitialized{false};
std::atomic<bool> log_builder::msv_IsNextSectionClosed{false};

log_builder::log_builder(const std::string_view pc_FuncSig) noexcept
    : mc_StartTime{std::chrono::high_resolution_clock::now()} {
  const std::string lc_Header{"{ \"time\": \"" + time::msf_now() +
                              "\", \"pid\":\"" + logger::msf_get_pid() +
                              "\", \"name\": \"" + pc_FuncSig.data() +
                              "\", \"next\": [ "};

  if (msv_IsNextSectionClosed) {
    logger::msf_log(", " + lc_Header);
  } else {
    logger::msf_log(lc_Header);
  }

  msv_IsNextSectionClosed = false;
}

log_builder::~log_builder() noexcept {
  const std::chrono::nanoseconds lc_Took{
      std::chrono::high_resolution_clock::now() - this->mc_StartTime};

  const std::string lc_Footer{
      " ], \"took(ns)\": " + std::to_string(lc_Took.count()) + " }"};

  logger::msf_log(lc_Footer);

  msv_IsNextSectionClosed = true;
}

void log_builder::msf_init() noexcept {
  if (msf_is_initialized() || !logger::msf_is_initialized()) {
    return;
  }

  logger::msf_log("[ ");
  logger::msf_async_log("[ {}");

  msv_IsInitialized = true;
}

void log_builder::msf_destroy() noexcept {
  if (!msf_is_initialized() || !logger::msf_is_initialized()) {
    return;
  }

  logger::msf_log(" ]");
  logger::msf_async_log(" ]");

  msv_IsInitialized = false;
}

bool log_builder::msf_is_initialized() noexcept { return msv_IsInitialized; }

void log_builder::msf_log(
    const std::string_view pc_Tag, const std::string_view pc_Message,
    const boost::system::error_code pc_ErrorCode) noexcept {
  const std::string lc_Body{msf_create_body(pc_Tag, pc_Message, pc_ErrorCode)};

  if (msv_IsNextSectionClosed) {
    logger::msf_log(", " + lc_Body);
  } else {
    logger::msf_log(lc_Body);
  }

  msv_IsNextSectionClosed = true;
}

void log_builder::msf_async_log(
    const std::string_view pc_Tag, const std::string_view pc_Message,
    const boost::system::error_code pc_ErrorCode) noexcept {
  const std::string lc_PID{
      std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()))};

  std::string lv_Record{", { \"time\": \"" + time::msf_now() +
                        "\", \"pid\": \"" + lc_PID.c_str() + "\", \"tag\": \"" +
                        pc_Tag.data() + "\", \"value\": \"" +
                        pc_Message.data()};

  if (pc_ErrorCode) {
    lv_Record +=
        " (" + pc_ErrorCode.to_string() + " : " + pc_ErrorCode.message() + ')';
  }

  logger::msf_async_log(lv_Record + "\" }");
}

std::string log_builder::msf_create_body(
    const std::string_view pc_Tag, const std::string_view pc_Message,
    const boost::system::error_code pc_ErrorCode) noexcept {
  std::string lv_Body{};

  lv_Body += "{ \"";
  lv_Body += pc_Tag;
  lv_Body += "\": \"";
  lv_Body += pc_Message;

  if (pc_ErrorCode) {
    lv_Body +=
        " (" + pc_ErrorCode.to_string() + " : " + pc_ErrorCode.message() + ')';
  }

  lv_Body += "\" }";

  return lv_Body;
}

}  // namespace library
}  // namespace pack
