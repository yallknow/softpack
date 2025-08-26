#include "pack_library_abstract_actor.hpp"

#include "../pack_library_preprocessor.hpp"

namespace pack {
namespace library {
namespace abstract {

pack::library::abstract::actor::~actor() noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();
}

void actor::draw() const noexcept {
  PACK_LIBRARY_LOG_FUNCTION_CALL();

  std::visit(
      [this](const auto& shapeLink) -> void {
        this->m_renderLink.draw(shapeLink);
      },
      this->m_shape);
}

}  // namespace abstract
}  // namespace library
}  // namespace pack
