#ifndef BUTTON_REGISTRY_H
#define BUTTON_REGISTRY_H

#include <map>
#include <string>
#include <lvgl.h>

class ButtonRegistry
{
public:
  static std::map<std::string, lv_obj_t *> buttons;
  static void register_button(const std::string &id, lv_obj_t *obj)
  {
    buttons[id] = obj;
  }
  static lv_obj_t *get_button(const std::string &id)
  {
    auto it = buttons.find(id);
    return it != buttons.end() ? it->second : nullptr;
  }
};

std::map<std::string, lv_obj_t *> ButtonRegistry::buttons;

#endif // BUTTON_REGISTRY_H