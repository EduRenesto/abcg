#include "material.hpp"

const std::string& Material::get_texture_name() const noexcept {
  return this->m_texture_name;
}
