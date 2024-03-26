#include "esphome/core/log.h"
#include "levoit_float.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.float";

void LevoitFloat::setup() {
   /* this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
      if (this->purpose_ == LevoitFloatPurpose::LIGHT) {
        this->publish_state(payloadData[15]);
      }
  });*/
}

void LevoitFloat::write_state(float value) {
    /*if (this->purpose_ == LevoitFloatPurpose::LIGHT) {
      if(this->s){
        uint8_t light = value;
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_LIGHT_BRIGHTNESS,
                                                  .packetType = LevoitPacketType::SEND_MESSAGE,
                                                  .payload = {0x00, 0x01, light}});
    }
    }*/
}

void LevoitFloat::dump_config() {
    ESP_LOGI("", "Levoit Float", this);
}

} //namespace levoit
} //namespace esphome
