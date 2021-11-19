#include "shader_asset.hpp"

GLuint ShaderAsset::get() const {
  return this->m_handle;
}

std::shared_ptr<Asset> ShaderAsset::build(GLuint handle) {
  auto specialized = std::make_shared<ShaderAsset>(ShaderAsset{handle});

  return std::static_pointer_cast<Asset>(specialized);
}
