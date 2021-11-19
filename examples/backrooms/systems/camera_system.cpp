#include "camera_system.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../components/camera_controller_component.hpp"

void CameraSystem::tick(ECS::World *world, float dt) {
  world->each<CameraControllerComponent>([&] (
    ECS::Entity *_e,
    ECS::ComponentHandle<CameraControllerComponent> cam
  ) -> void {
    /*
    cam->eye += glm::vec3{10 * dt, 0, 0};
    */

    //auto right{glm::vec3{0.0, 0.0, 1.0}};
    //auto forward{glm::normalize(glm::cross(cam->up, right))};
    auto forward{glm::normalize(cam->center - cam->eye)};
    auto right{glm::normalize(glm::cross(forward, cam->up))};

    // Camera translation
    if (this->m_input.is_pressed(InputNames::TRANSLATE_FWD)) {
      cam->eye += dt * this->m_translation_speed * forward;
      cam->center += dt * this->m_translation_speed * forward;
    }
    if (this->m_input.is_pressed(InputNames::TRANSLATE_BWD)) {
      cam->eye -= dt * this->m_translation_speed * forward;
      cam->center -= dt * this->m_translation_speed * forward;
    }
    if (this->m_input.is_pressed(InputNames::TRANSLATE_LEFT)) {
      cam->eye -= dt * this->m_translation_speed * right;
      cam->center -= dt * this->m_translation_speed * right;
    }
    if (this->m_input.is_pressed(InputNames::TRANSLATE_RIGHT)) {
      cam->eye += dt * this->m_translation_speed * right;
      cam->center += dt * this->m_translation_speed * right;
    }

    // Camera yaw
    if (this->m_input.is_pressed(InputNames::YAW_CCW)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, dt * this->m_rotation_speed, cam->up)};
      cam->center = cam->eye + v_prime;
    }
    if (this->m_input.is_pressed(InputNames::YAW_CW)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, -dt * this->m_rotation_speed, cam->up)};
      cam->center = cam->eye + v_prime;
    }

    // Camera pitch
    if (this->m_input.is_pressed(InputNames::PITCH_UP)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, dt * this->m_rotation_speed, right)};
      cam->center = cam->eye + v_prime;
    }
    if (this->m_input.is_pressed(InputNames::PITCH_DOWN)) {
      auto v{cam->center - cam->eye};
      auto v_prime{glm::rotate(v, -dt * this->m_rotation_speed, right)};
      cam->center = cam->eye + v_prime;
    }

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
