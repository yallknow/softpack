#include "../library/pack_library_log_builder.hpp"
#include "../library/pack_library_logger.hpp"
#include "../library/pack_library_preprocessor.hpp"
#include "../library/pack_library_scope_profiler.hpp"
#include "pack_client_app.hpp"

static int sf_client_main() {
  _PACK_LIBRARY_LOG_FUNCTION_CALL_();

  pack::client::app lv_App{};

  if (!lv_App.mf_start()) {
    _PACK_LIBRARY_LOG_ERROR_("Can't start client!");

    return EXIT_FAILURE;
  }

  _PACK_LIBRARY_LOG_INFO_("Client stopped successfully.");

  return EXIT_SUCCESS;
}

int main() {
  pack::library::logger::msf_set_log_directory("log/client/");
  pack::library::logger::msf_init();

  if (!pack::library::logger::msf_is_initialized()) {
    return EXIT_FAILURE;
  }

  pack::library::scope_profiler::msf_init();
  pack::library::log_builder::msf_init();

  if (!pack::library::scope_profiler::msf_is_initialized() ||
      !pack::library::log_builder::msf_is_initialized()) {
    return EXIT_FAILURE;
  }

  const int lc_ReturnValue{sf_client_main()};

  pack::library::scope_profiler::msf_destroy();
  pack::library::log_builder::msf_destroy();
  pack::library::logger::msf_destroy();

  return lc_ReturnValue;
}
