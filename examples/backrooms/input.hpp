#ifndef __BACKROOMS_INPUT_HPP
#define __BACKROOMS_INPUT_HPP

#include <array>
#include <map>
#include "SDL_events.h"

enum InputNames : size_t {
  TRANSLATE_FWD = 0,
  TRANSLATE_BWD,
  TRANSLATE_LEFT,
  TRANSLATE_RIGHT,
  YAW_CCW,
  YAW_CW,
  PITCH_UP,
  PITCH_DOWN,
  TOTAL_INPUT_NAMES, // not an actual input, just used as a size
};

class Input {
public:
  [[nodiscard]]
  bool is_pressed(InputNames input) const;

  void update(SDL_Event &evt);

private:
  std::array<bool, TOTAL_INPUT_NAMES> m_keys{false};

  static const std::map<SDL_Keycode, InputNames> m_input_map;
};

#endif
