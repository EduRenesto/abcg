#include "gl_window.hpp"
#include <chrono>
#include "abcg_openglwindow.hpp"

dxball::GLWindow::GLWindow() {
  this->m_world = World{};
  this->m_last_frame = std::chrono::steady_clock::now();
}

void dxball::GLWindow::initializeGL() {
  glEnable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto block_shader = createProgramFromFile(
    getAssetsPath() + "shaders/block.vs.glsl",
    getAssetsPath() + "shaders/block.fs.glsl"
  );

  auto ball_shader = createProgramFromFile(
    getAssetsPath() + "shaders/ball.vs.glsl",
    getAssetsPath() + "shaders/ball.fs.glsl"
  );

  this->m_block_renderer = std::optional{
    BlockRenderer{block_shader, 0.1, 0.1}
  };

  this->m_ball_renderer = std::optional{
    BallRenderer{ball_shader, 0.1, 0.1}
  };
}

void dxball::GLWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);

  auto now = std::chrono::steady_clock::now();

  std::chrono::duration<float> delta = now - this->m_last_frame;

  this->update(delta.count());

  this->render();

  this->m_last_frame = now;
}

void dxball::GLWindow::terminateGL() {
  
}

void dxball::GLWindow::render() {
  this->m_world.render(
    this->m_block_renderer.value(),
    this->m_ball_renderer.value()
  );
}

void dxball::GLWindow::update(float delta) {
  this->m_world.update(0.3 * delta);
}
