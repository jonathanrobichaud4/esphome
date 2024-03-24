#include "esphome/core/log.h"
#include "levoit_light.h"
#include "esphome/components/light/light_state.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.light";

void uint8_to_float(uint8_t *src, float *dst, size_t count) {
    // Iterate over each uint8_t value and convert it to float
    for (size_t i = 0; i < count; ++i) {
        // Assuming each uint8_t represents a single byte of a float
        dst[i] = (float)src[i];
    }
}

void LevoitLight::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
    //uint8_t brightness_uint = 

    uint8_to_float(&payloadData[15], brightness, 1);
    //float value = (float)payloadData[15];
    //brightness = &value;

    ESP_LOGI("", "%f Levoit Light", &brightness);
    this->current_values_as_brightness(brightness);
    this->publish_state();
      
  });
}

void LevoitLight::dump_config() { ESP_LOGI("", "Levoit Fan", this); }

void LevoitLight::write_state(light::LightState *state) {
  float bright;
  //state->current_values_as_brightness(&brightness);
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
