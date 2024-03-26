#include "esphome/core/log.h"
#include "levoit_number.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.number";

void LevoitNumber::setup() {
    this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
      if (this->purpose_ == LevoitNumberPurpose::HUMIDITY_LEVEL) {
        this->publish_state(payloadData[14]);
      }
  });
}

void LevoitNumber::control(float value) {
    if (this->purpose_ == LevoitNumberPurpose::HUMIDITY_LEVEL) {
      if(this->has_state()){
        uint8_t humidity_level = value;
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDITY_LEVEL,
                                                  .packetType = LevoitPacketType::SEND_MESSAGE,
                                                  .payload = {0x00, 0x00, 0x01, humidity_level}});
    }
    }
}

void LevoitNumber::dump_config() {
    ESP_LOGI("", "Levoit Number", this);
}

} //namespace levoit
} //namespace esphome
