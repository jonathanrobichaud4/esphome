#include "esphome/core/log.h"
#include "levoit_light.h"

#include "esphome/core/optional.h"

namespace esphome {
namespace levoit {
//TODO: Still need to figure out proper state handling so it doesn't get stuck in a loop
static const char *const TAG = "levoit.light";
bool is_transitioning = false;

void LevoitLight::setup() {
      this->process_command_();
   }

bool LevoitLight::control_dimmer_(const uint8_t brightness) {
 
   //uint8_t set_brightness = remap<uint8_t, uint8_t>(brightness, 0, 100, this->min_value_, this->max_value_);
   this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_LIGHT_BRIGHTNESS,
                                                .packetType = LevoitPacketType::SEND_MESSAGE,
                                                .payload = {0x00, 0x01, brightness}});

  return true;
 }



   void LevoitLight::process_command_() {

    this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
    const uint8_t new_brightness = payloadData[15];
    if (new_brightness != this->last_brightness_) {
      this->publish_state_(new_brightness);
       //this->control_dimmer_(this->last_brightness_);
     }

    

    });
   }
   
    
  void LevoitLight::publish_state_(const uint8_t brightness) {
   if (this->state_) {
     ESP_LOGV(TAG, "Publishing new state: brightness=%d", brightness);
     auto call = this->state_->make_call();
     if (brightness != 0) {
       call.set_state(true);
       call.set_brightness((float) brightness / 100.0f);
     }
     else if (brightness == 0){
        call.set_state(false);
       }
     call.perform();
   }
 }

light::LightTraits LevoitLight::get_traits() {
          auto traits = light::LightTraits();
          traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
          return traits;
        }
    

void LevoitLight::dump_config() { ESP_LOGI("", "Levoit Light", this); }

void LevoitLight::write_state(light::LightState *state) {
  float brightness;
  state->current_values_as_brightness(&brightness);
  const uint8_t calculated_brightness = (uint8_t) roundf(brightness * 100);


  if (calculated_brightness != this->last_brightness_) {
     if (this->control_dimmer_(calculated_brightness)) {
       this->last_brightness_ = calculated_brightness;
     } else {
       // Return to original value if failed to write to the dimmer
       // TODO: Test me, can be tested if high-voltage part is not connected
       ESP_LOGW(TAG, "Failed to update the dimmer, publishing the previous state");
       this->publish_state_(this->last_brightness_);
     }
   }
    



}
  
}  // namespace levoit
}  // namespace esphome
