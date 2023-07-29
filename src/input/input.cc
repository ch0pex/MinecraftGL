#include "input.h"


u16 InputInfo::PressedKeys() const{
  return std::count(keys, keys + 1024, true);
}

bool InputInfo::PressedKeysAreDiag() const {
  return (keys[GLFW_KEY_W] || keys[GLFW_KEY_S]) && (keys[GLFW_KEY_A] || keys[GLFW_KEY_D] || keys[GLFW_KEY_Q] || keys[GLFW_KEY_E]);
}