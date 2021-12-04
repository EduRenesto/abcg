#ifndef __SPONZA_TEXTURE_ASSET_HPP
#define __SPONZA_TEXTURE_ASSET_HPP

#include <GL/glew.h>
#include <memory>

#include "asset.hpp"

class TextureAsset : public Asset {
public:
  explicit TextureAsset(GLuint handle) : m_handle(handle) {}

  [[nodiscard]]
  GLuint get() const;

  static std::shared_ptr<Asset> build(GLuint handle);

private:
  GLuint m_handle;
};

#endif
