#include "camera_system.hpp"

#include "../components/camera_controller_component.hpp"

void CameraSystem::tick(ECS::World *world, float dt) {
  world->each<CameraControllerComponent>([&] (
    ECS::Entity *_e,
    ECS::ComponentHandle<CameraControllerComponent> cam
  ) -> void {
    cam->eye += glm::vec3{0, 0, dt};

    cam->camera->set_eye(cam->eye);
    cam->camera->set_center(cam->center);
    cam->camera->set_up(cam->up);
  });
}

void CameraSystem::configure(ECS::World *_world) {
  /* do nothing */
}

void CameraSystem::unconfigure(ECS::World *_world) {
  /* do nothing */
}
