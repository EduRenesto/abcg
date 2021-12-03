#include "texture_asset.hpp"

GLuint TextureAsset::get() const {
  return this->m_handle;
}

std::shared_ptr<Asset> TextureAsset::build(GLuint handle) {
  auto specialized = std::make_shared<TextureAsset>(TextureAsset{handle});

  return std::static_pointer_cast<Asset>(specialized);
}
