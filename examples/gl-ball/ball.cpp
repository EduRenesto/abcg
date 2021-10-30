#include "ball.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

glball::Ball::Ball(glm::vec2 initial_position, float radius, glm::vec2 initial_velocity) {
  this->position = initial_position;
  this->radius = radius;
  this->velocity = initial_velocity;
}

glm::vec2 & glball::Ball::get_position() {
  return this->position;
}

glm::vec2 & glball::Ball::get_velocity() {
  return this->velocity;
}

float & glball::Ball::get_radius() {
  return this->radius;
}

void glball::Ball::set_velocity(glm::vec2 velocity) {
  //std::cout << "Ball::set_velocity " << glm::to_string(velocity) << std::endl;
  this->velocity = velocity;
}

void glball::Ball::update(float delta) {
  this->position += this->velocity * delta * 3.0f;
}
