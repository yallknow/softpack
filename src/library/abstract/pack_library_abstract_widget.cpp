#include "pack_library_abstract_widget.hpp"

#include "../pack_library_preprocessor.hpp"

namespace pack {
namespace library {
namespace abstract {

widget::widget(const std::uint32_t c_width, const std::uint32_t c_height,
               const std::string_view c_title) noexcept
    : mc_width{c_width}, mc_height{c_height}, mc_title{c_title} {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

widget::~widget() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }

}  // namespace abstract
}  // namespace library
}  // namespace pack
