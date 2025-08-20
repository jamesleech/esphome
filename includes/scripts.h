#include <sstream>
#include <string>
#include "esphome.h"
#include "button_registry.h"

inline void log_items(const std::string &input)
{
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        ESP_LOGI("SCRIPTS", "Item: %s", token.c_str());
    }
}

inline void light_visibility(bool show_lights, const std::string &input)
{
    std::stringstream ss(input);
    std::string btn_id;
    while (std::getline(ss, btn_id, ','))
    {
        lv_obj_t *btn = ButtonRegistry::get_button(btn_id);
        if (!btn)
        {
            ESP_LOGE("SCRIPTS", "Button %s not found in ButtonRegistry", btn_id.c_str());
            continue;
        }
        bool is_on = lv_obj_has_flag(btn, LV_OBJ_FLAG_USER_1);
        ESP_LOGI("SCRIPTS", "Button %s is %s", btn_id.c_str(), is_on ? "ON" : "OFF");
        bool is_visible = !lv_obj_has_flag(btn, LV_OBJ_FLAG_HIDDEN);
        ESP_LOGD("SCRIPTS", "Button %s current visibility: %s", btn_id.c_str(), is_visible ? "VISIBLE" : "HIDDEN");

        if (show_lights)
        {
            lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
            ESP_LOGD("SCRIPTS", "Showing button %s", btn_id.c_str());
        }
        else if (!is_on)
        {
            lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
            ESP_LOGD("SCRIPTS", "Hiding button %s", btn_id.c_str());
        }
    }
}
