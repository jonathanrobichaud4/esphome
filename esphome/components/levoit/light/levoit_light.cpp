#include "esphome/core/log.h"
#include "levoit_light.h"
#include "esphome/components/light/light_state.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.light";
float brightness = 0.0;
void LevoitLight::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
     uint8_t brightness_value = payloadData[15];

        // Assuming you have a reference to your MonochromaticLightOutput instance
        if (output_ != nullptr) {
            float brightness_normalized = static_cast<float>(brightness_value);
            //output_->set_level(brightness_normalized);
            brightness = brightness_normalized;
            this->current_values_as_brightness(&brightness);
            //publish_state();
            //this->publish_state();

        }
        ESP_LOGI("", "%f Levoit Light", brightness);
      this->publish_state();
      
  });
}

void LevoitLight::dump_config() { ESP_LOGI("", "Levoit Fan", this); }

void LevoitLight::write_state(light::LightState *state) {
  float bright;
  
  //output_->set_level(bright);
  //bool newPowerState = this->state;

  /*if (bright==brightness) {
    //newPowerState = state->get_state();

    switch (this->parent_->device_model_) {
      case LevoitDeviceModel::CORE_400S:
        // fan switch controls main power state
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_POWER_STATE,
                                                  .packetType = LevoitPacketType::SEND_MESSAGE,
                                                  .payload = {0x00, newPowerState}});
        break;
      default:
        // fan switch controls auto mode
        if (newPowerState == true) {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x00}});
        } else {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x02}});
        }
    }
  }

  if (call.get_speed().has_value()) {
    uint8_t targetSpeed = *call.get_speed();

    // 400s-specific behavior
    if (this->parent_->device_model_ == LevoitDeviceModel::CORE_400S) {
      // if fan is off, we don't set speed
      if (newPowerState == false) {
        return;
      }

      if (targetSpeed == 0) {
        // fan speed can report as 0-speed (auto mode), but setting to 0-speed results in error
        // set to 1 instead
        targetSpeed = 1;
      }
    }*/

   /* this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MANUAL,
                                              .packetType = LevoitPacketType::SEND_MESSAGE,
                                              .payload = {0x00, 0x00, 0x01, targetSpeed}});
  }*/
}
}  // namespace levoit
}  // namespace esphome
