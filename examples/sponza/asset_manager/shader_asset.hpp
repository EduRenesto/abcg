#ifndef __SPONZA_SHADER_ASSET_HPP
#define __SPONZA_SHADER_ASSET_HPP

#include <GL/glew.h>
#include <memory>

#include "asset.hpp"

class ShaderAsset : public Asset {
public:
  explicit ShaderAsset(GLuint handle) : m_handle(handle) {}

  [[nodiscard]]
  GLuint get() const;

  static std::shared_ptr<Asset> build(GLuint handle);

private:
  GLuint m_handle;
};

#endif
