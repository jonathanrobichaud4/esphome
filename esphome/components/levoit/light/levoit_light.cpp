#include "esphome/core/log.h"
#include "levoit_light.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.light";


void LevoitLight::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
    uint8_t brightness_uint = payloadData[15];
    float value = brightness_uint;
    brightness = &value;
    float value_range = value / 100.0f;

    if (this->current_values != this->remote_values) {
         ESP_LOGD(TAG, "Light is transitioning, datapoint change ignored");
         return;
       }
 
      auto call = this->make_call();
       //call.set_brightness(float(datapoint.value_uint) / this->max_value_);
      call.set_publish(true);
      call.set_brightness(value_range);
      call.perform();
      //this->publish_state();
     });
   }
    
//void LevoitLight::setup_state(light::LightState *state) { state_ = state; }
/*
  if (value_range == 0.0f) {
    //this->current_values.set_brightness(value_range);
    this->current_values.set_state(false);
    this->turn_on();
    ESP_LOGI("", "Levoit Light on if statement");
  } else {
    this->current_values.set_state(true);
    this->turn_on();
    ESP_LOGI("", "Levoit Light off if statement");
  }
    ESP_LOGI("", "%f Levoit Light brightnessr", this->current_values.get_brightness());

    //ESP_LOGI("", "%f Levoit Light", );
    if(this->current_values.is_on()){
      ESP_LOGI("", "Levoit Light on");
    }
    else{
      ESP_LOGI("", "Levoit Light off");
    }
    
    //this->current_values_as_brightness(brightness);
    
    //this->current_values.set_brightness(value_range);

    this->publish_state();
    dump_config();
    //this->write_state(this);*/ 
    //this->write_state(this);

light::LightTraits LevoitLight::get_traits() {
          auto traits = light::LightTraits();
          traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
          return traits;
        }
    

void LevoitLight::dump_config() { ESP_LOGI("", "Levoit Light", this); }



void LevoitLight::write_state(light::LightState *state) {
  //float bright;
  //this->current_values_as_brightness(brightness);
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
