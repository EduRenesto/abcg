#include "camera_system.hpp"

#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../components/camera_controller_component.hpp"

void CameraSystem::tick(ECS::World *world, float dt) {
  world->each<CameraControllerComponent>([&] (
    ECS::Entity *_e,
    ECS::ComponentHandle<CameraControllerComponent> cam
  ) -> void {
    auto forward{glm::normalize(cam->center - cam->eye)};
    auto right{glm::normalize(glm::cross(forward, cam->up))};

    // Camera translation
    if (this->m_input.is_pressed(InputNames::TRANSLATE_FWD)) {
      cam->eye += dt * this->m_translation_speed * forward;
      cam->center += dt * this->m_translation_speed * forward;
      cam->should_update = true;
    }
    if (this->m_input.is_pressed(InputNames::TRANSLATE_BWD)) {
      cam->eye -= dt * this->m_translation_speed * forward;
      cam->center -= dt * this->m_translation_speed * forward;
      cam->should_update = true;
    }
    if (this->m_input.is_pressed(InputNames::TRANSLATE_LEFT)) {
      cam->eye -= dt * this->m_translation_speed * right;
      cam->center -= dt * this->m_translation_speed * right;
      cam->should_update = true;
    }
    if (this->m_input.is_pressed(InputNames::TRANSLATE_RIGHT)) {
      cam->eye += dt * this->m_translation_speed * right;
      cam->center += dt * this->m_translation_speed * right;
      cam->should_update = true;
    }

    // Camera yaw
    if (this->m_input.is_pressed(InputNames::YAW_CCW)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, dt * this->m_rotation_speed, cam->up)};
      cam->center = cam->eye + v_prime;
      cam->should_update = true;
    }
    if (this->m_input.is_pressed(InputNames::YAW_CW)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, -dt * this->m_rotation_speed, cam->up)};
      cam->center = cam->eye + v_prime;
      cam->should_update = true;
    }

    // Camera pitch
    if (this->m_input.is_pressed(InputNames::PITCH_UP)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, dt * this->m_rotation_speed, right)};
      cam->center = cam->eye + v_prime;
      cam->should_update = true;
    }
    if (this->m_input.is_pressed(InputNames::PITCH_DOWN)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, -dt * this->m_rotation_speed, right)};
      cam->center = cam->eye + v_prime;
      cam->should_update = true;
    }

    if (this->m_input.is_pressed(InputNames::PRINT_CURRENT_POSITION)) {
      fmt::print("Current camera position: {}\n", glm::to_string(cam->center));
    }

    if (cam->should_update) {
      cam->camera->set_eye(cam->eye);
      cam->camera->set_center(cam->center);
      cam->camera->set_up(cam->up);
      cam->should_update = false;
    }
  });
}

void CameraSystem::configure(ECS::World *_world) {
  /* do nothing */
}

void CameraSystem::unconfigure(ECS::World *_world) {
  /* do nothing */
}
