#include <string_view>

#include "../library/pack_library_log_builder.hpp"
#include "../library/pack_library_logger.hpp"
#include "../library/pack_library_preprocessor.hpp"
#include "../library/pack_library_scope_profiler.hpp"
#include "pack_client_app.hpp"

namespace pack {
namespace client {

namespace {

constexpr std::string_view gsc_logDirectory{"log/client/"};

}  // namespace

int main() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  app app{};

  if (!app.start()) {
    PACK_LIBRARY_LOG_ERROR("Can not start client");

    return EXIT_FAILURE;
  }

  PACK_LIBRARY_LOG_INFO("Client stopped successfully");

  return EXIT_SUCCESS;
}

}  // namespace client
}  // namespace pack

int main() noexcept {
  pack::library::logger::init(pack::client::gsc_logDirectory);

  if (!pack::library::logger::is_initialized()) {
    return EXIT_FAILURE;
  }

  pack::library::scope_profiler::init();
  pack::library::log_builder::init();

  if (!pack::library::scope_profiler::is_initialized() ||
      !pack::library::log_builder::is_initialized()) {
    return EXIT_FAILURE;
  }

  const int c_result{pack::client::main()};

  pack::library::scope_profiler::destroy();
  pack::library::log_builder::destroy();
  pack::library::logger::destroy();

  return c_result;
}
