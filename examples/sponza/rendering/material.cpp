#include "material.hpp"

const std::string& Material::get_texture_name() const noexcept {
  return this->m_texture_name;
}

float Material::get_shininess() const noexcept {
  return this->m_shininess;
}
