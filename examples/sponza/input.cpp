#include "input.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"

/*
 * This map contains both Dvorak and QWERTY mappings.
 */
const std::map<SDL_Keycode, InputNames> Input::m_input_map{
  { SDLK_w, TRANSLATE_FWD },
  { SDLK_COMMA, TRANSLATE_FWD },

  { SDLK_s, TRANSLATE_BWD },
  { SDLK_o, TRANSLATE_BWD },

  { SDLK_a, TRANSLATE_LEFT },

  { SDLK_d, TRANSLATE_RIGHT },
  { SDLK_e, TRANSLATE_RIGHT },

  { SDLK_LEFT, YAW_CCW },
  { SDLK_RIGHT, YAW_CW },

  { SDLK_UP, PITCH_DOWN },
  { SDLK_DOWN, PITCH_UP },

  { SDLK_p, PRINT_CURRENT_POSITION },
};

bool Input::is_pressed(InputNames input) const {
  return this->m_keys.at(input);
}

void Input::update(SDL_Event &evt) {
  if (!Input::m_input_map.contains(evt.key.keysym.sym)) return;

  auto key{Input::m_input_map.at(evt.key.keysym.sym)};
  this->m_keys.at(key) = evt.type == SDL_KEYDOWN;
}
