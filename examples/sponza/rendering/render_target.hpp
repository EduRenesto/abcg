#ifndef __SPONZA_RENDER_TARGET
#define __SPONZA_RENDER_TARGET

#include <vector>

#include <GL/glew.h>

/*
 * Since my demo doesn't do much stuff interactively,
 * I will focus on getting it /beautiful/.
 *
 * The RenderTarget encapsulates an OpenGL FBO with its
 * associated texture objects. This will then be used
 * in a GBuffer class in order to do cool deferred rendering.
 */
class RenderTarget {
public:
  RenderTarget(
    unsigned int width,
    unsigned int height,
    bool use_depth_texture,
    std::vector<std::pair<GLuint, GLuint>> color_attachment_formats
  );

  [[nodiscard]]
  GLuint get_color_attachment(unsigned int idx) const;

  [[nodiscard]]
  GLuint get_depth_attachment() const;

  void use() const;

private:
  GLuint m_handle{};

  std::vector<GLuint> m_textures{};

  GLuint m_depth_attachment{};
};

#endif
