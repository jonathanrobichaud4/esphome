#include "esphome/core/log.h"
#include "levoit_light.h"
#include "esphome/core/helpers.h"
#include "esphome/core/optional.h"

namespace esphome {
namespace levoit {
//TODO: Still need to figure out proper state handling so it doesn't get stuck in a loop
static const char *const TAG = "levoit.light";
bool is_transitioning = false;
void LevoitLight::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
    uint8_t brightness_uint = payloadData[15];
    float value = brightness_uint;
    float brightness = value / 100.0f;
      
      if (this->state_->current_values != this->state_->remote_values) {
        ESP_LOGD(TAG, "Light is transitioning, datapoint change ignored");
        is_transitioning = true;

      }
      else{
        is_transitioning = false;
      auto call = this->state_->make_call();
      // if (brightness == 0) {
      //   call.set_state(false);
      //   call.perform();
      // } else{
        //call.set_state(true);
        call.set_brightness(brightness);
        call.perform();
      //}
      //}
      //call.set_publish(true);
      //call.set_brightness(brightness);
      
      //this->state_->publish_state();
      }
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
  brightness = state->remote_values.get_brightness();;

  ESP_LOGI(TAG, " Sent Brightness: %f", brightness*100.0f);

  //auto values = this->state_->current_values();
  //if (state_->current_values().get_brightness()) 
  auto call = this->state_->make_call();
  
  ESP_LOGI(TAG, "Current values: %f", state->current_values.get_brightness());
  ESP_LOGI(TAG, "remote values: %f", state->remote_values.get_brightness());
  
  //if (this->state_->current_values != this->state_->remote_values) {
      //float target_brightness = brightness;
      //is_transitioning = true;

   /*if (this->state_->current_values != this->state_->remote_values) {
        ESP_LOGD(TAG, "Light is transitioning, datapoint change ignored");
        is_transitioning = true;
        return;
      }*/
      //float test = this->state_->current_values.get_brightness();
      //bool test2 = test->has_value();
  if(is_transitioning == true){
      this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_LIGHT_BRIGHTNESS,
                                                .packetType = LevoitPacketType::SEND_MESSAGE,
                                                .payload = {0x00, 0x01, static_cast<uint8_t>(brightness*100)}});

   }      //break;
}
   
  
 // } 
  
}  // namespace levoit
}  // namespace esphome
