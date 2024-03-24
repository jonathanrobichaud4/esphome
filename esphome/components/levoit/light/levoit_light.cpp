#include "esphome/core/log.h"
#include "levoit_light.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.light";


void LevoitLight::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
    uint8_t brightness_uint = payloadData[15];
    float value = brightness_uint;
    float brightness = value / 100.0f;
      auto call = this->state_->make_call();

      if (brightness == 0) {
        call.set_state(false);
      } else {
        call.set_state(true);
        call.set_brightness(brightness);
      }
      //call.set_publish(true);
      //call.set_brightness(brightness);
      call.perform();
      this->state_->publish_state();
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

  auto call = this->state_->make_call();
  float brightness = 0.0f;
  //this->current_values_as_brightness(brightness);
  //state->current_values_as_brightness(&brightness);
  //output_->set_level(bright);
  this->state_->current_values_as_brightness(&brightness);

  brightness = this->state_->current_values.get_brightness() * 100;
  ESP_LOGI(TAG, " Sent Brightness: %f", brightness);

  if (brightness > 0.0f) {
     if (this->state_->current_values.is_on() == true) {

        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_LIGHT_BRIGHTNESS,
                                                  .packetType = LevoitPacketType::SEND_MESSAGE,
                                                  .payload = {0x00, static_cast<uint8_t>(brightness)}});
        //break;
       /*auto brightness_int = static_cast<uint32_t>(brightness * this->max_value_);
       brightness_int = std::max(brightness_int, this->min_value_);
 
       this->parent_->set_integer_datapoint_value(*this->dimmer_id_, brightness_int);*/
     }
   }
  /*bool newPowerState = this->state_->current_values_as_binary;

  if (call.get_state().has_value()) {
    newPowerState = state->get_state();

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
    }

    this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MANUAL,
                                              .packetType = LevoitPacketType::SEND_MESSAGE,
                                              .payload = {0x00, 0x00, 0x01, targetSpeed}});
  }
}*/
}  // namespace levoit
}  // namespace esphome
}
