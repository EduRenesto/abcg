#include "gl_window.hpp"
#include "abcg_openglwindow.hpp"

void dxball::GLWindow::initializeGL() {
  glEnable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto block_shader = createProgramFromFile(
    getAssetsPath() + "shaders/block.vs.glsl",
    getAssetsPath() + "shaders/block.fs.glsl"
  );

  this->m_block_renderer = std::optional{
    BlockRenderer(block_shader, 0.01, 0.01)
  };
}

void dxball::GLWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);

  Block b{};
  b.position = glm::ivec2(0.0, 0.0);

  this->m_block_renderer.value().render(b);
}

void dxball::GLWindow::terminateGL() {
  
}
