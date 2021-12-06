#ifndef __SPONZA_RESIZE_WINDOW_EVENT_HPP
#define __SPONZA_RESIZE_WINDOW_EVENT_HPP

#include "../ecs.hpp"

struct ResizeWindowEvent {
  unsigned int width;
  unsigned int height;

  ECS_DECLARE_TYPE
} __attribute__((aligned(8)));

ECS_DEFINE_TYPE(ResizeWindowEvent)

#endif
