#include "esphome/core/log.h"
#include "levoit_light.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.light";

bool is_transitioning = false;
void LevoitLight::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
    uint8_t brightness_uint = payloadData[15];
    float value = brightness_uint;
    float brightness = value / 100.0f;
      auto call = this->state_->make_call();
       ESP_LOGI(TAG, "Current values: %f", this->state_->current_values.is_on());
       ESP_LOGI(TAG, "remote values: %f", this->state_->remote_values.is_on());
      if (is_transitioning) {
            ESP_LOGD(TAG, "Light is transitioning, ignoring state update");
            return;
        }

      if (brightness == 0) {
        call.set_state(false);
      } else{
        call.set_state(true);
        call.set_brightness(brightness);
      }
      //call.set_publish(true);
      //call.set_brightness(brightness);
      call.perform();
      //this->state_->publish_state();
     });
   }
    

light::LightTraits LevoitLight::get_traits() {
          auto traits = light::LightTraits();
          traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
          return traits;
        }
    

void LevoitLight::dump_config() { ESP_LOGI("", "Levoit Light", this); }

void LevoitLight::setup_state(light::LightState *state) { state_ = state; }

void LevoitLight::write_state(light::LightState *state) {
  float brightness = 0.0f;

 state->current_values_as_brightness(&brightness);
  ESP_LOGI(TAG, " Sent Brightness: %f", brightness*100.0f);

  if (brightness > 0.0f) {
     if (this->state_->current_values.is_on() == true) {
      is_transitioning = true;

      this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_LIGHT_BRIGHTNESS,
                                                .packetType = LevoitPacketType::SEND_MESSAGE,
                                                .payload = {0x00, 0x01, static_cast<uint8_t>(brightness*100)}});
            //break;
    }
  } 
  else {
    is_transitioning = false;
   }
}  // namespace levoit
}  // namespace esphome
}
