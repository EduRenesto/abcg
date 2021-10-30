#include <iostream>
#include <memory>

#include <fmt/core.h>

#include "abcg.hpp"
#include "abcg_application.hpp"
#include "abcg_exception.hpp"
#include "abcg_openglwindow.hpp"
#include "gl_window.hpp"

int main(int argc, char* argv[]) {
  try {
    abcg::Application app(argc, argv);

    auto window{std::make_unique<dxball::GLWindow>()};

    window->setWindowSettings({
	.width = 1280,
	.height = 720,
	.showFullscreenButton = false,
	.title = "GL-Ball",
    });

    window->setOpenGLSettings({
	.profile = abcg::OpenGLProfile::Core,
	.majorVersion = 4,
	.minorVersion = 1,
	.samples = 4
    });

    app.run(std::move(window));
  } catch (const abcg::Exception &e) {
    fmt::print(stderr, "{}", e.what());
    return -1;
  }

  return 0;
}
