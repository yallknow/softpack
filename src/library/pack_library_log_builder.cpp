#include "pack_library_log_builder.hpp"

#include "pack_library_logger.hpp"
#include "pack_library_time.hpp"

namespace pack {
namespace library {

std::atomic<bool> log_builder::ms_isInitialized{false};
std::atomic<bool> log_builder::ms_isNextSectionClosed{false};

log_builder::log_builder(const std::string_view c_funcsig) noexcept
    : mc_startTime{std::chrono::high_resolution_clock::now()} {
  const std::string c_header{"{ \"time\": \"" + time::now() + "\", \"pid\":\"" +
                             logger::get_pid() + "\", \"name\": \"" +
                             c_funcsig.data() + "\", \"next\": [ "};

  logger::log(ms_isNextSectionClosed ? ", " + c_header : c_header);

  ms_isNextSectionClosed = false;
}

log_builder::~log_builder() noexcept {
  const std::chrono::nanoseconds c_took{
      std::chrono::high_resolution_clock::now() - this->mc_startTime};

  const std::string c_footer{
      " ], \"took(ns)\": " + std::to_string(c_took.count()) + " }"};

  logger::log(c_footer);

  ms_isNextSectionClosed = true;
}

void log_builder::init() noexcept {
  if (is_initialized() || !logger::is_initialized()) {
    return;
  }

  logger::log("[ ");
  logger::async("[ {}");

  ms_isInitialized = true;
}

void log_builder::destroy() noexcept {
  if (!is_initialized() || !logger::is_initialized()) {
    return;
  }

  logger::log(" ]");
  logger::async(" ]");

  ms_isInitialized = false;
}

bool log_builder::is_initialized() noexcept { return ms_isInitialized; }

void log_builder::log(const std::string_view c_tag,
                      const std::string_view c_message,
                      const boost::system::error_code c_errorCode) noexcept {
  const std::string c_body{create_body(c_tag, c_message, c_errorCode)};

  logger::log(ms_isNextSectionClosed ? ", " + c_body : c_body);

  ms_isNextSectionClosed = true;
}

void log_builder::async(const std::string_view c_tag,
                        const std::string_view c_message,
                        const boost::system::error_code c_errorCode) noexcept {
  const std::string c_pid{
      std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()))};

  std::string record{", { \"time\": \"" + time::now() + "\", \"pid\": \"" +
                     c_pid.c_str() + "\", \"tag\": \"" + c_tag.data() +
                     "\", \"value\": \"" + c_message.data()};

  if (c_errorCode) {
    record +=
        " (" + c_errorCode.to_string() + " : " + c_errorCode.message() + ')';
  }

  logger::async(record + "\" }");
}

std::string log_builder::create_body(
    const std::string_view c_tag, const std::string_view c_message,
    const boost::system::error_code c_errorCode) noexcept {
  std::string body{};

  body += "{ \"";
  body += c_tag;
  body += "\": \"";
  body += c_message;

  if (c_errorCode) {
    body +=
        " (" + c_errorCode.to_string() + " : " + c_errorCode.message() + ')';
  }

  body += "\" }";

  return body;
}

}  // namespace library
}  // namespace pack
