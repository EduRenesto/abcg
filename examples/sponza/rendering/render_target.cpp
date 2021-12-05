#include "render_target.hpp"
#include "abcg_exception.hpp"

#include <fmt/format.h>

RenderTarget::RenderTarget(
  unsigned int width,
  unsigned int height,
  bool use_depth_texture,
  std::vector<std::pair<GLuint, GLuint>> color_attachment_formats
) {
  fmt::print("RenderTarget::RenderTarget({}, {})\n", width, height);

  glGenFramebuffers(1, &this->m_handle);
  glBindFramebuffer(GL_FRAMEBUFFER, this->m_handle);

  unsigned int total_color_attachments = color_attachment_formats.size();

  this->m_textures.resize(total_color_attachments);

  std::vector<GLenum> draw_buffers{};

  glGenTextures(total_color_attachments, this->m_textures.data());

  for (unsigned int i = 0; i < total_color_attachments; i++) {
    auto formats{color_attachment_formats[i]};
    glBindTexture(GL_TEXTURE_2D, this->m_textures[i]);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      formats.first,
      width,
      height,
      0,
      formats.second,
      GL_FLOAT,
      nullptr
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
      GL_FRAMEBUFFER,
      GL_COLOR_ATTACHMENT0 + i,
      GL_TEXTURE_2D,
      this->m_textures[i],
      0
    );

    draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
  }

  glDrawBuffers(draw_buffers.size(), draw_buffers.data());

  if (use_depth_texture) {
    glGenTextures(1, &this->m_depth_attachment);
    glBindTexture(GL_TEXTURE_2D, this->m_depth_attachment);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_DEPTH_COMPONENT,
      width,
      height,
      0,
      GL_DEPTH_COMPONENT,
      GL_FLOAT,
      nullptr
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
      GL_FRAMEBUFFER,
      GL_DEPTH_ATTACHMENT,
      GL_TEXTURE_2D,
      this->m_depth_attachment,
      0
    );
  } else {
    glGenRenderbuffers(1, &this->m_depth_attachment);
    glBindRenderbuffer(GL_RENDERBUFFER, this->m_depth_attachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(
      GL_FRAMEBUFFER,
      GL_DEPTH_ATTACHMENT,
      GL_RENDERBUFFER,
      this->m_depth_attachment
    );
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTarget::get_color_attachment(unsigned int idx) const {
  return this->m_textures[idx];
}

GLuint RenderTarget::get_depth_attachment() const {
  return this->m_depth_attachment;
}

void RenderTarget::use() const {
  glBindFramebuffer(GL_FRAMEBUFFER, this->m_handle);

  auto status{glCheckFramebufferStatus(GL_FRAMEBUFFER)};

  if (status != GL_FRAMEBUFFER_COMPLETE) {
    throw abcg::Exception{abcg::Exception::Runtime("Tried to use an incomplete framebuffer")};
  }
}
